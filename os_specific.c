#include"os_specific.h"
#if defined(_WIN32)||defined(_WIN64)
#	include<stdio.h>
#	include<stdlib.h>
#	include<windows.h>
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
#	include<stdio.h>
#	include<stdlib.h>
#	include<unistd.h>
#endif

int clear(void){
#if defined(_WIN32)||defined(_WIN64)
	system("cls");
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	system("clear");
#endif
	return 0;
}

int color_background(int color){
#if defined(_WIN32)||defined(_WIN64)
	printf("\e[4%d",color);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(color&COLOR_RED==COLOR_RED?BACKGROUND_RED:0)|
		(color&COLOR_GREEN==COLOR_GREEN?BACKGROUND_GREEN:0)|
		(color&COLOR_BLUE==COLOR_BLUE?BACKGROUND_BLUE:0));
#endif
	return 0;
}

int color_foreground(int color){
#if defined(_WIN32)||defined(_WIN64)
	printf("\e[3%d",color);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(color&COLOR_RED==COLOR_RED?FOREGROUND_RED:0)|
		(color&COLOR_GREEN==COLOR_GREEN?FOREGROUND_GREEN:0)|
		(color&COLOR_BLUE==COLOR_BLUE?FOREGROUND_BLUE:0));
#endif
	return 0;
}

int get_term_col(void){
#if defined(_WIN32)||defined(_WIN64)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
	return csbi.srWindow.Right-csbi.srWindow.Left+1;
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	struct winsize ws;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws);
	return ws.ws_col;
#endif
}

int get_term_row(void){
#if defined(_WIN32)||defined(_WIN64)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
	return csbi.srWindow.Bottom-csbi.srWindow.Top+1;
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	struct winsize ws;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws);
	return ws.ws_row;
#endif
}

int hide_carret(void){
#if defined(_WIN32)||defined(_WIN64)
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
	cci.bVisible=0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	printf("\e[?25l");
	fflush(stdout);
#endif
	return 0;
}

int set_canonical(void){
#if defined(_WIN32)||defined(_WIN64)
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
	mode|=(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	struct termios tio;
	tcgetattr(STDIN_FILENO,&tio);
	tio.c_lflag|=(ICANON|ECHO);
	tcsetattr(STDIN_FILENO,&tio);
#endif
	return 0;
}

int set_noncanonical(void){
#if defined(_WIN32)||defined(_WIN64)
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
	mode&=~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	struct termios tio;
	tcgetattr(STDIN_FILENO,&tio);
	tio.c_lflag&=~(ICANON|ECHO);
	tcsetattr(STDIN_FILENO,&tio);
#endif
	return 0;
}

int show_carret(void){
#if defined(_WIN32)||defined(_WIN64)
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
	cci.bVisible=1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	printf("\e[?25h");
	fflush(stdout);
#endif
	return 0;
}
