#include<stdio.h>

int main(){
	int areas[]={10,12,13,14,20};
	char name[]="Zed";
	char full_name[]={'Z','e','d',' ','A','.',' ','S','h','a','w','\0'};

	printf("The size of an int: %ld\n", sizeof(int));//int大小是4个字节
	printf("The size of areas (int[]): %ld\n", sizeof(areas));//areas中有五个整数，所以用20个字节存储
	printf("The number of ints in areas: %ld\n", sizeof(areas)/sizeof(int));
	printf("The first area is %d, the 2nd %d.\n", areas[0],areas[1]);


	printf("The size of a char: %ld\n", sizeof(char));//char大小是1个字节
	printf("The size of name (char[]): %ld\n",sizeof(name));//三个字符打出Zed，还有一个空字符
    	printf("The number of chars: %ld\n",sizeof(name) / sizeof(char));
	

	printf("The size of full_name (char[]): %ld\n",sizeof(full_name));
    	printf("The number of chars: %ld\n",sizeof(full_name) / sizeof(char));
    	printf("name=\"%s\" and full_name=\"%s\"\n",name, full_name);
	



	return 0;
}
