#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cmd.h"
#include"os_specific.h"

int main(void){
	char cmd[10];

	hide_carret();
	while(1){
		clear();
		set_noncanonical();
		cmd[strlen(cmd)+1]='\0';
		cmd[strlen(cmd)]=getchar();
		set_canonical();
		if(exe_cmd(cmd)==EXIT_FAILURE){
			break;
		}
	}
	show_carret();
	return 0;
}
