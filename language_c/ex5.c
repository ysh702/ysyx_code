#include<stdio.h>

int main(int argc, char *argv[]){//argc表示程序运行时通过命令行传入的参数个数，包括程序名本身。
//argv[]存储所有的命令行参数的具体值，argv[0]：程序本身的名字（./ex5），argv[1]：第一个真实参数
	int distance = 100;

	printf("You are %d miles away.\n", distance);

	return 0;
}
