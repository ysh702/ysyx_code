#include<stdio.h>

int main(){
	puts("hello world.");
	puts("hello,ysyx.");
	puts("today is monday.");
	return 0;//删除；后，error: expected ‘;’ before ‘}’ token
}
//阅读后发现，fputc是将一个字符写入文件，fputs是将一个字符串写入文件（但不能换行），puts自动换行
