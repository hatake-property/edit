#ifndef EDIT_OS_SPECIFIC
#define EDIT_OS_SPECIFIC

#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_BLUE 4

int clear(void);
int color_background(int color);
int color_foreground(int color);
int get_term_col(void);
int get_term_row(void);
int hide_carret(void);
int set_canonical(void);
int set_italic(void);
int set_noncanonical(void);
int show_carret(void);

#endif // EDIT_OS_SPECIFIC
