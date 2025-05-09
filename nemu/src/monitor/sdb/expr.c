/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

word_t eval(int p, int q);

enum {
  TK_NOTYPE = 256, TK_EQ, TK_NEQ, TK_AND,
  TK_ADD, TK_MINUS, TK_MULT, TK_DIV,
  TK_DNUM, TK_HNUM, TK_LP, TK_RP,
  TK_NEG, TK_DEREF, TK_REG
  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"==", TK_EQ},        // equal
  {"!=", TK_NEQ},       // not equal
  {"&&", TK_AND},       // and
  {"\\+", TK_ADD},      // plus，+在正则中是量词，匹配一次或多次，所以要转义
  {"-", TK_MINUS},      // minus
  {"\\*", TK_MULT},     // mult，*在正则中是量词，匹配0次或多次，转义
  {"/", TK_DIV},        // div
  {"0x[a-f,A-F,0-9]+", TK_HNUM},    //hex num
  {"[0-9]+", TK_DNUM},    //dex num
  {"\\(", TK_LP},       //left parentheses，正则中是分组符号
  {"\\)",TK_RP},        //right parentheses，正则中是分组结束符号
  {"\\$[a-z,0-9]+", TK_REG},        //registers，$在正则中匹配行尾
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {//NR_REGEX表示rules数组长度，有多少条正则表达式规则
    //regcomp()将字符串形式的正则表达式，如（"\\d+")编译成regex_t结构(re是一个全局的regex_t数组)，优化匹配效率。若编译失败，返回非零错误码
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);//rules[i].regex表示第i条规则的正则表达式字符串，re[i]表示存储编译后的正则表达式，REG_EXTENDED编译标志
    //检查是否编译成功
    if (ret != 0) {//若regcomp()失败（返回非0值）
      regerror(ret, &re[i], error_msg, 128);//将错误码ret转换为可读的错误信息，存入error_msg
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);//panic()终止程序并输出错误信息
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {//e 字符串
  int position = 0;//当前扫描位置
  int i;
  regmatch_t pmatch;//存储匹配结果（起始位置和结束位置）pmatch.rm_so起始位置，pmatch.rm_eo结束位置

  nr_token = 0;//记录已识别的token数量

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {//遍历所有正则规则
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        //从position开始尝试匹配re[i]
        //pmatch.rm_so==0确保匹配从当前位置开始
        char *substr_start = e + position;//匹配到的子串的起始指针
        int substr_len = pmatch.rm_eo;//匹配到的子串长度
        //匹配成功后处理
        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;//更新扫描位置e+position

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case TK_NOTYPE:
            break;
          case TK_EQ: case TK_NEQ: case TK_AND:
          case TK_ADD: case TK_MINUS: case TK_MULT:
          case TK_DIV: case TK_DNUM: case TK_HNUM:
          case TK_LP: case TK_RP: case TK_REG:
            tokens[nr_token].type = rules[i].token_type;//将匹配到的标记类型赋值给tokens[nr_token].type
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            //使用strncpy将匹配的字符串(substr_start到substr_len长度的部分)复制到tokens[nr_token].str
            tokens[nr_token++].str[substr_len] = '\0';//在每个字符串末尾添加空字符\0，确保字符串以空字符结尾
            //nr_token自增，表示处理完一个标记
            break;
          
          default:
            Log("Unknown token\n");
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  Log("Final position: %d, string length: %d, nr_token: %d", position, (int)strlen(e), nr_token);
  return true;
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  for(int i = 0; i< nr_token; i++){
    if(tokens[i].type == TK_MULT && (i==0||(tokens[i-1].type != TK_DNUM &&tokens[i-1].type != TK_REG
    && tokens[i-1].type != TK_HNUM && tokens[i-1].type != TK_RP))){
      tokens[i].type = TK_DEREF;
    }
  }
    
  *success = true;
  return eval(0, nr_token-1);
  
}

//检查从p-q的子表达式是否被一对匹配的括号完全包裹，是（true），否（false）
bool check_parentheses(int p, int q){//p和q表示tokens数组的起始和结束索引
  int nr_p = 0;//记录未匹配的（

  for(int i = p; i<=q; i++){//遍历tokens[p....q]
    if(tokens[i].type == TK_LP){//若遇到（
      nr_p += 1;//增加未匹配的左括号计数
    }else if(tokens[i].type == TK_RP){//若遇到）
      if(nr_p > 0){//如果有未匹配的（
        nr_p -= 1;//减少未匹配的左括号计数
      }else{//否则括号不匹配
        printf("bad experssion at %s(%d)\n", tokens[i].str, i);
        assert(0);//报错并终止程序
      }

    }
    if(nr_p == 0 && i < q){//如果括号匹配完了，但是还没到q
      return false;//说明最外层括号没有包裹整个表达式
    }
  }
  //最终检查
  if(nr_p == 0 && tokens[p].type == TK_LP && tokens[q].type == TK_RP){
    return true;
  }else if(nr_p == 0){
    return false;
  }else{
    assert(0);
  }
}


//接着找主运算符(优先级最低的,最后计算)
int get_primary_op(int p, int q){
  int temp = -1;
  int operator_priority = 0;//记录优先级，数值越小，优先级越高
  for(int i = p; i <= q; i++){
    //跳过括号内的运算符，因为嵌套中的运算符肯定不是主运算符
    if(tokens[i].type == TK_LP){
      int nr_p = 1;
      while(i <= q){
        if(tokens[++i].type == TK_LP){
          nr_p++;
        }else if(tokens[i].type == TK_RP){
          nr_p--;
        }
        if(nr_p == 0){
          break;
        }
      }
      //检查运算符，并更新主运算符
    }else if((tokens[i].type == TK_ADD || tokens[i].type == TK_MINUS) && operator_priority <= 2){
      temp = i;
      operator_priority = 2;
    }else if((tokens[i].type == TK_MULT || tokens[i].type == TK_DIV) && operator_priority <= 1){
      temp = i;
      operator_priority = 1;
    }else if((tokens[i].type == TK_EQ || tokens[i].type == TK_NEQ) && operator_priority <= 3){
      temp = i;
      operator_priority = 3;
    }else if(tokens[i].type == TK_AND && operator_priority <= 4){
      temp = i;
      operator_priority = 4;
    }
  }
  if(temp == -1){//如果没找到，返回到起始位置p
    return p;
  }
  return temp;//最后这个函数返回主运算符的位置
}


word_t eval(int p, int q){
  if(p>q){//错误表达
    assert(0);
  }
  else if(p == q){//单字符情况,直接返回值
    if(tokens[p].type == TK_DNUM){
      return atoi(tokens[p].str);//十进制，atoi转换字符串为整数
    }else if(tokens[p].type == TK_HNUM){
      char *temp_ptr;
      return strtol(tokens[p].str, &temp_ptr, 16);//十六进制，用strtol按16进制解析
    }else if(tokens[p].type == TK_REG){//寄存器
      bool flag=true;
      word_t res = isa_reg_str2val(tokens[p].str, &flag);//调用isa_reg_str2val获取寄存器值
      if(!flag){
        return res;
      }else{
        assert(0);
      }
    }else{
      assert(0);
    }
  }

  else if(check_parentheses(p,q) == true){
    return eval(p+1, q-1);//去掉最外层括号后继续递归求值
  }else{//找主运算符
    int main_operator = get_primary_op(p,q);
    word_t left_value = 0;
    word_t right_value = 0;
//处理单目运算符（-或解引用*）
    if(tokens[main_operator+1].type == TK_NEG || tokens[main_operator].type == TK_DEREF){
      left_value = eval(main_operator+1,q);//计算右侧表达式
    }
    else{//处理双目运算符
      left_value = eval(p,main_operator-1);//计算左侧子表达式
      right_value = eval(main_operator+1, q);//计算右侧子表达式
    }
    //根据运算符类型计算结果
    switch(tokens[main_operator].type){
      case TK_ADD: return left_value + right_value;
      case TK_MINUS: return left_value - right_value;
      case TK_MULT: return left_value * right_value;
      case TK_DIV: return left_value / right_value;
      case TK_NEG: return -left_value;
      case TK_EQ: return left_value == right_value;
      case TK_NEQ: return left_value != right_value;
      case TK_AND: return left_value && right_value;
      case TK_DEREF: return *((word_t *)(uint64_t)left_value);
      default: assert(0);
    }
  }
}

