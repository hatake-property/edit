#include<stdio.h>
#include"os_specific.h"

int main(void){
	int c;

	hide_carret();
	while(1){
		clear();
		set_noncanonical();
		c=getchar();
		set_canonical();
		if(c=='q'){
			break;
		}
	}
	show_carret();
	return 0;
}
