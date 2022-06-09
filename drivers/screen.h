#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDR 0xb8000 
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void print_char(char character, int col, int row, char attribute_byte);
int get_screen_offset(int col, int row);
int get_cursor();
void set_cursor(int offset);
void print_at(char* message, int col, int row);
void print(char* message);
void clear_screen();
int handle_scrolling(int cursor_offset);

void move_right(int amt);
void move_left(int amt); 
void readln();

void write_string_no_offset(char* string, int color);

void clear_screen_linear();

#endif
