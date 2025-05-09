#include<stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person{//定义Person结构体
	char *name;
	int age;
	int height;
	int weight;
};
//person_create函数，动态创建一个结构体实例
struct Person *Person_create(char *name, int *age, int height, int weight){
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);

	who->name = strdup(name);
    	who->age = age;//将参数 age 的值赋给 who 指针所指向的 Person 结构体的 age
    	who->height = height;
    	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who){
	assert(who!= NULL);//检查指针的有效性

	free(who->name);//先释放name字符串的内存（单独分配的）
	free(who);//再释放Person结构体本身的内存
}

void Person_print(struct Person *who){
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
    	printf("\tHeight: %d\n", who->height);
    	printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[]){
	struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
	struct Person *frank = Person_create( "Frank Blank", 20, 72, 180);
	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);
	printf("Frank is at memory location %p:\n", frank);
	Person_print(frank);
	joe->age += 20;
    	joe->height -= 2;
    	joe->weight += 40;
    	Person_print(joe);

    	frank->age += 20;
    	frank->weight += 20;
    	Person_print(frank);

	Person_destroy(joe);
	Person_destroy(frank);

	return 0;
}
