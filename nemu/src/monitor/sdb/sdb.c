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
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <memory/vaddr.h>
#include "watchpoint.h"

void set_wp(char *arg, word_t value);
void delete_wp(int n);


static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  nemu_state.state = NEMU_QUIT;//在键入q时，设置state为quit。
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args){
  char *arg = strtok(NULL," ");//strtok(NULL, "")将之前输入的字符串按空格分成一个个部分
  (void)arg;//arg在这个函数里没用到，所以需要声明
  int steps = 1;

  if(args != NULL){
    char *endptr;
    steps=strtol(args, &endptr, 10);//strtol将字符串转化为整数
    if(*endptr != '\0' || steps <= 0){
      printf("Invalid step count (must be positive integer)\n");
      return -1;
    }
  }
  cpu_exec(steps);//执行指令，steps是执行次数
  return 0;
}

static int cmd_info(char *args){
  char *arg = strtok(NULL, " ");
  if(arg == NULL){
    printf("Usage: info r|w\n");
    return -1;
  }/*有问题，寄存器值都为0*/
  if(strcmp(arg, "r")==0){//打印寄存器值
    isa_reg_display();
  }else if(strcmp(arg, "w")==0){//打印监视点值
    display_wp();
  }
  else{
    printf("Unknown info subcommand '%s'\n",arg);
    printf("Supported subcommands: r, w\n");
    return -1;
  }
  return 0;
}

static int cmd_x(char *args){
  char *arg = strtok(NULL," ");//分割第一个参数
  int N;
  if(arg != NULL){
    sscanf(arg,"%d",&N);
  }
  else{
    printf("arg1 need num\n");
    return 0;
  }
  char *arg2 = strtok(NULL, " ");//分割第二个参数
  if(arg2 == NULL){
    printf("Need addr\n");
    return 0;
  }
  if(isxdigit(arg2[0])){

  }
  else{
    printf("EXPR need 16\n");
    return 0;
  }
  int addr;
  sscanf(arg2,"%x",&addr);
  char *arg3 = strtok(NULL," ");//分割第三个参数
  if(arg3 !=NULL){
    printf("Too much args\n"); 
  }
  else if(arg!=NULL && arg2 !=NULL){
    printf("addr=%x\n", addr+N*4);
    printf("%u\n", vaddr_read(addr+N*4,4));
  }
  return 0;
}

static int cmd_p(char *args){
  bool success;
  word_t res = expr(args, &success);
  if(!success){
    puts("Invalid experssion");
  }else{
    printf("%u\n", res);
  }
  return 0;
}

static int cmd_w(char *args)
{
  if(args == NULL)
  {
    printf("Unknown input, the standard format is 'w EXPR'\n");
    return 0;
  }
  bool success;
  word_t res = expr(args, &success);
  if(!success)
    printf("The expression is problematic\n");
  else 
    set_wp(args, res);
  
  return 0;
}

static int cmd_d(char *args)
{
  if(args == NULL)
  {
    printf("Unknown input, the standard format is 'd N'\n");
    return 0;
  }
  char *arg = strtok(NULL, " ");
  int n = strtol(arg, NULL, 10);
  delete_wp(n);
  return 0;
}



static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },

  /* TODO: Add more commands */
  {"si","单步执行",cmd_si},
  {"info", "The 'r' key prints the register status. The 'w' key prints the watchpoint information.", cmd_info},
  {"x", "Scan memory", cmd_x},
  {"p", "Usage: p EXPR. Calculate the experssion, e.g. p $eax +1", cmd_p},
  {"w","Usage: w EXPR. Watch for the variation of the result of EXPR, pause at variation point", cmd_w},
  {"d", "Usage: d N. Delete watchpoint of wp.NO=N", cmd_d },
};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}



/** 
TestMyExpr：读取文件中的表达式和预期结果，测试表达式计算的正确性。
打开文件，读取每行的表达式和预期结果。
调用 expr 函数计算表达式的结果。
比较计算结果和预期结果，如果不一致则断言失败。
关闭文件，释放资源。

//  /home/liuyongzhe/ysyx-workbench/nemu/tools/gen-expr/input
// 去除字符串中的多余空格和换行符
// 去除字符串中的多余空格和换行符
void trim_whitespace(char *str) {
    char *src = str;
    char *dst = str;
    while (*src) {
        if (!isspace(*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}
void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}
 
int TestMyExpr() {
    int right_ans = 0;
    const char *path = "./tools/gen-expr/input";  // 相对路径
    FILE *input_file = fopen(path, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }
 
    char record[102400];
    int real_val; // 修改为 int 类型
    char buf[102400];
 
    // 循环读取每一条记录
    for (int i = 0; i < 100; i++) {
        // 读取一行记录
        if (fgets(record, sizeof(record), input_file) == NULL) {
            perror("Error reading input file");
            break;
        }
 
        // 使用 sscanf 解析数值
        if (sscanf(record, "%d", &real_val) != 1) {
            printf("Invalid record format\n");
            continue;
        }
 
        // 处理表达式部分，可能跨越多行
        strcpy(buf, ""); // 清空buf
        char *token = strtok(record, " ");
        if (token == NULL) {
            printf("Invalid record format\n");
            continue;
        }
 
        // 跳过第一个数值部分
        token = strtok(NULL, " ");
        while (token != NULL) {
            // 检查 buf 是否有足够的空间
            if (strlen(buf) + strlen(token) + 1 >= sizeof(buf)) {
                printf("Expression too long, skipping...\n");
                break;
            }
            strcat(buf, token);
            strcat(buf, " "); // 拼接换行后的部分，注意添加空格以分隔多行内容
            token = strtok(NULL, " ");
        }
 
        // 如果 buf 被截断，跳过当前记录
        if (strlen(buf) + 1 >= sizeof(buf)) {
            continue;
        }
 
        // 去除多余空格和换行符
        trim_whitespace(buf);
        trim(buf);
 
        // 输出结果
        bool flag = false;
        int res = expr(buf, &flag); // 修改为 int 类型
        printf("Real Value: %d, Expression: %s\n", real_val, buf);
        printf("TestMyExpr the value:%d\n", res);
        if (res == real_val) {
            right_ans++;
        }
    }
 
    printf("Test 100 expressions, the accuracy is %d/100\n", right_ans);
    fclose(input_file);
    return 0;
}
  **/



