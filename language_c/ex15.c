#include<stdio.h>

int main(){
	int ages[]={23,43,12,89,2};
	char *names[]={"Alan", "Frank","Mary", "John", "Lisa"};

	int count = sizeof(ages)/sizeof(int);
	int i=0;
	for(i=0;i<count;i++){
		printf("%s has %d years alive.\n", names[i],ages[i]);
	}
	printf("---\n");
	
	int *cur_age=ages;//int *创建指向整数的指针，char *创建指向字符的指针
	char **cur_name=names;//创建了指向names的指针，char*已经是指向char的指针，char**就是指向字符指针的指针

	for(i=0;i<count;i++){
		printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
	}//*(cur_name+i)和name[i]是一样的，读作cur_name指针加i的值
	printf("---\n");
	
	for(i=0;i<count;i++){
		printf("%s is %d years old again.\n", cur_name[i],cur_age[i]);
	}

	printf("---\n");

	for(cur_name = names, cur_age = ages;(cur_age-ages)<count;cur_name++,cur_age++){
		printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	}

	return 0;
}



//开辟内存，将ages这个名字指向他的起始位置，通过选取ages作为基址，并获取位置为i的元素，对内存块进行索引。
//
