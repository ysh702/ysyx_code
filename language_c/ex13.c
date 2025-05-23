#include<stdio.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("ERROR: You need one argument.\n");
		 return 1;//返回1是为了提示操作系统程序出错，可以在脚本中测试
	}

	int i=0;
	for(i=0;argv[1][i] != '\0';i++){//输入""后，指令就相当于一个字符串
		char letter = argv[1][i];

		switch(letter){
			case 'a':
			case 'A':
				printf("%d: 'A'\n",i);
				break;
			case 'e':
			case 'E':
				printf("%d: 'E'\n", i);
				break;
			case 'i':
            		case 'I':
                		printf("%d: 'I'\n", i);
                		break;

            		case 'o':
            		case 'O':
                		printf("%d: 'O'\n", i);
                		break;

            		case 'u':
            		case 'U':
                		printf("%d: 'U'\n", i);
                		break;

            		case 'y':
            		case 'Y':
				if(i<2){
					printf("%d: 'Y'\n", i);
				}
				break;

			default:
				printf("%d: %c is not a vowel\n", i, letter);
		}
	}

	return 0;
}	
