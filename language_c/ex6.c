#include<stdio.h>

int main(){

	int distance = 100;//整数，int声明，%d打印
	float power = 2.345f;//浮点数，float或double声明，%f打印
	double super_power = 56789.4532;
	char initial = 'A';//字符，char声明，单个字符‘’表示，%c打印
	char first_name[] = "Zed";//字符串（字符数组）char[]声明，""表示，%s打印
	char last_name[] = "shaw";

	printf("You are %d miles away.\n", distance);
    	printf("You have %f levels of power.\n", power);
    	printf("You have %f awesome super powers.\n", super_power);
    	printf("I have an initial %c.\n", initial);
    	printf("I have a first name %s.\n", first_name);
    	printf("I have a last name %s.\n", last_name);
    	printf("My whole name is %s %c. %s.\n",first_name, initial, last_name);

	return 0;
}
