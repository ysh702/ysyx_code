#include<stdio.h>

int main(int argc, char *argv[]){
	int i = 0;
	for(i = 1; i<argc; i++){
		printf("arg %d:%s\n", i,argv[i]);
	}

	char *states[]={"California","Oregon","washington","Texas"};
	int num_states=4;

	for(i=0;i<num_states;i++){
		printf("state %d:%s\n",i,states[i]);
	}

	return 0;
}

