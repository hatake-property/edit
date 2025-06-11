#include"os_specific.h"
#if defined(_WIN32)||defined(_WIN64)
#	include<stdlib.h>
#	include<windows.h>
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
#	include<stdio.h>
#	include<stdlib.h>
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

int color_background(int color){
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
	struct winsize ws;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws);
	return ws.ws_col;
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
	return csbi.srWindow.Right-csbi.srWindow.Left+1;
#endif
}

int get_term_row(void){
#if defined(_WIN32)||defined(_WIN64)
	struct winsize ws;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws);
	return ws.ws_row;
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
	return csbi.srWindow.Bottom-csbi.srWindow.Top+1;
#endif
}

int hide_carret(void){
#if defined(_WIN32)||defined(_WIN64)
	printf("\e[?25l");
	fflush(stdout);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
	cci.bVisible=0;
	SetConsoleCurosrInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
#endif
	return 0;
}

int set_caconical(void){
#if defined(_WIN32)||defined(_WIN64)
	struct termios tio;
	tcgetattr(STDIN_FILENO,&tio);
	tio.c_lflag|=(ICANON|ECHO);
	tcsetattr(STDIN_FILENO,&tio);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
	mode|=(ENABLE_LINE_INPUT|ENABLE_NCHO_INPUT);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
#endif
	return 0;
}

int set_noncanonical(void){
#if defined(_WIN32)||defined(_WIN64)
	struct termios tio;
	tcgetattr(STDIN_FILENO,&tio);
	tio.c_lflag&=~(ICANON|ECHO);
	tcsetattr(STDIN_FILENO,&tio);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
	mode&=~(ENABLE_LINE_INPUT|ENABLE_NCHO_INPUT);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
#endif
	return 0;
}

int show_carret(void){
#if defined(_WIN32)||defined(_WIN64)
	printf("\e[?25h");
	fflush(stdout);
#elif defined(_linux)||(defined(__APPLE__)&&defined(__MACH__))
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
	cci.bVisible=1;
	SetConsoleCurosrInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
#endif
	return 0;
}
