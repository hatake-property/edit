#include<stdlib.h>
#include<string.h>

int exe_cmd(char*cmd){
	switch(cmd[0]){
	case'q':
		return EXIT_FAILURE;
	default:
		cmd[0]='\0';
	}
	return EXIT_SUCCESS;
}