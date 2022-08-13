#include "screen.h"
#include "../kernel/util.h"
#include "../kernel/low_level.h"

#include <stdbool.h>
 
 
 // TO DO: MOVE END OF SENTENCE (EOS) AND \B HANDLING TO KEYBOARD DRIVER 
void print_char(char character, int col, int row, char attribute_byte){
	unsigned char *vidmem = (unsigned char *) VIDEO_ADDR;
	
	if(!attribute_byte){
		attribute_byte = WHITE_ON_BLACK;
	}
	
	int offset; 
	bool EOS = false; 
	
	if(col >= 0 && row >=0){
		offset = get_screen_offset(col, row);	
	}
	else{
		offset = get_cursor();
	}
	
	int rows = offset / (2 * MAX_COLS);
	int cols = offset / 2 - rows * MAX_COLS;
	if(cols == MAX_COLS - 1){
		EOS = true; 
	}
	
	if(character == '\n'){
		int rows = offset / (2 * MAX_COLS);
		offset = get_screen_offset(0, rows + 1);
	}
	else if(character == '\b'){
		int rows = offset / (2 * MAX_COLS);
		int cols = offset / 2 - rows * MAX_COLS;
		if(cols == 0 && rows == 1 || cols == 0){
		
		}
		else{
			offset = get_screen_offset(cols - 1, rows);
			vidmem[offset] = ' ';
		}
	}
	else{
		if(!EOS){
			vidmem[offset] = character; 
			vidmem[offset + 1] = attribute_byte;
			offset += 2; 
		}
	}
	
	offset = handle_scrolling(offset);
		
	set_cursor(offset);
	
}

int get_screen_offset(int col, int row){
	return ((row * MAX_COLS) + col) * 2;
}

int get_cursor(){
	port_byte_out(REG_SCREEN_CTRL, 14); 
	int offset = port_byte_in(REG_SCREEN_DATA) << 8; 
	port_byte_out(REG_SCREEN_CTRL, 15); 
	offset += port_byte_in(REG_SCREEN_DATA); 
	
	return offset * 2; 
}

void set_cursor(int offset){
	offset /= 2; 
	
	port_byte_out(REG_SCREEN_CTRL, 14); 
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, offset);
}

void print_at(char* message, int col, int row){
	if(col >= 0 && row >= 0){
		set_cursor(get_screen_offset(col, row));
	}
	
	int i = 0;
	while(message[i] != 0) {
		print_char(message[i], col, row, WHITE_ON_BLACK);
		i++;
	}
}

void print(char* message){
	print_at(message, -1, -1);
}

void clear_screen() { 
	unsigned char* video_mem = (unsigned char*)VIDEO_ADDR; 

	for(int row = 0; row < MAX_ROWS; row++){
		for(int col = 0; col < MAX_COLS; col++){
			print_char(' ', col, row, WHITE_ON_BLACK); 
		}
	}
	
	set_cursor(get_screen_offset(0, 0));
}

int handle_scrolling(int cursor_offset){
	if(cursor_offset < MAX_ROWS * MAX_COLS * 2){
		return cursor_offset;
	}
	
	// copy down all values for rows greater than 0 only 
	for(int i = 1; i < MAX_ROWS; i++){
		memory_copy(get_screen_offset(0, i) + VIDEO_ADDR, 
			get_screen_offset(0, i-1) + VIDEO_ADDR,
			MAX_COLS * 2
		);
	}
	
	char* last_line = get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDR; 
	for(int i = 0; i < MAX_COLS * 2; i++){
		last_line[i] = 0;
	}
	
	cursor_offset -= 2 * MAX_COLS;
	
	return cursor_offset; 
}

void move_right(int amt){
	int offset = get_cursor();
	
	int rows = offset / (2 * MAX_COLS);
	int cols = offset / 2 - rows * MAX_COLS;
	
	offset = get_screen_offset(cols+=amt, rows);
	set_cursor(offset);
}

void move_left(int amt){
	int offset = get_cursor();
		
	int rows = offset / (2 * MAX_COLS);
	int cols = offset / 2 - rows * MAX_COLS;
	
	offset = get_screen_offset(cols-=amt, rows);
	set_cursor(offset);
}

void readln(){
	unsigned char* vidmem = (unsigned char*) VIDEO_ADDR; 
	int offset = get_cursor();
	int rows = offset / (2 * MAX_COLS);
	offset = get_screen_offset(0, rows-1);
	char message_buffer[MAX_COLS];
	char c = ' ';
	char* verr = "version\0";
	char* cls = "cls\0";
	char* echo = "echo\0";
	char* name_c = "name\0";
	for(int i = 0; i < MAX_COLS; i++){
		c = vidmem[offset];
		offset+=2; 
		message_buffer[i] = c;
		if(message_buffer[i] == ' '){
			message_buffer[i] = '\0';
			if(str_eq(message_buffer,  verr)){
				print("SimiOS, Version 0.0.1.\n");
			} 
			else if(str_eq(message_buffer, cls)){
				clear_screen();
			}
			else if(str_eq(message_buffer, name_c)){
				print("My name is Didus.\n");
			}
			else if(str_eq(message_buffer, echo)){
				for(int j = i; j < MAX_COLS; j++){
					c = vidmem[offset]; 
					offset+=2;
					message_buffer[j - i] = c; 
					if(message_buffer[j - i] == ' '){
						message_buffer[j - i] = '\0';
						print(message_buffer);
						print("\n");
						break;
					}
				}
			}
			// add from 44 -> 53
			else if(is_number(message_buffer[0])){
				int final_result = 0;
				
				int current_number = 0; // leave it un-inited.
				bool is_op = false;
				char* current_op = ' ';
				// 1 + 1
				
				bool op_done = false; 
				
				for(int i = 0; message_buffer[i] != ' '; i++){
					
					// add from 44 -> 53
					if(is_number(message_buffer[i])){
						current_number *= 10; 
						current_number += message_buffer[i] - 48;
					}
					
					else if(message_buffer[i] == '+'){
						if(current_op == ' '){
							final_result = current_number; 
						}
						else if(current_op == '+'){
							final_result += current_number; 
						}
						else if(current_op == '-'){
							final_result -= current_number; 
						}
						else if(current_op == '*'){
							final_result *= current_number; 
						}
						else if(current_op == '/'){
							final_result /= current_number; 
						}
						current_op = '+';
						
						current_number = 0;
					}
					else if(message_buffer[i] == '-'){
					
						if(current_op == ' '){
							final_result = current_number; 
						}
						else if(current_op == '+'){
							final_result += current_number; 
						}
						else if(current_op == '-'){
							final_result -= current_number; 
						}
						else if(current_op == '*'){
							final_result *= current_number; 
						}
						else if(current_op == '/'){
							final_result /= current_number; 
						}
						current_op = '-';
						
						current_number = 0;
					}
					else if(message_buffer[i] == '*'){
					
						if(current_op == ' '){
							final_result = current_number; 
						}
						else if(current_op == '+'){
							final_result += current_number; 
						}
						else if(current_op == '-'){
							final_result -= current_number; 
						}
						else if(current_op == '*'){
							final_result *= current_number; 
						}
						else if(current_op == '/'){
							final_result /= current_number; 
						}
						current_op = '*';
						
						current_number = 0;
					}
					else if(message_buffer[i] == '/'){
					
						if(current_op == ' '){
							final_result = current_number; 
						}
						else if(current_op == '+'){
							final_result += current_number; 
						}
						else if(current_op == '-'){
							final_result -= current_number; 
						}
						else if(current_op == '*'){
							final_result *= current_number; 
						}
						else if(current_op == '/'){
							final_result /= current_number; 
						}
						current_op = '/';
						
						current_number = 0;
					}
					
					//else{
					//	print("Mathematical operations only support +, -, *, and /.");
					//	break;
					//}	
				}
				// the last op will always be missed
				if(current_op == '+'){
					final_result += current_number; 
				}
				if(current_op == '-'){
					final_result -= current_number; 
				}
				else if(current_op == '*'){
					final_result *= current_number; 
				}
				else if(current_op == '/'){
					final_result /= current_number; 
				}
				int a = final_result; 
				int b = 0; 
				
				int c; 
				if(current_op == ' '){
					print("Calc: Expected an operand!");
					print("\n");
					break;
				}
				if(a == 0) { 
					print("0");
					print("\n");
					break;
				}
				while(a != 0){
					c = a % 10; 
					b *= 10; 
					b += c; 
					a /= 10;
				}
				
				a = b; 
				b = 0;
				while(a != 0){
					c = a % 10; 
					b *= 10; 
					b += c; 
					a /= 10;
					
					print_char(c+48, -1, -1, WHITE_ON_BLACK); 
				}
					
				while(final_result % 10 == 0){
					final_result /= 10; 
					print_char(48, -1, -1, WHITE_ON_BLACK); 
				}
				print("\n");
			}
			else{
				print("No such command \"");
				print(message_buffer);
				print("\"\n");
			}
			break;
		}
	}

}

void write_string(char* string, int color){
	unsigned char *video_memory = (unsigned char*) VIDEO_ADDR;
	int i = 0;
	while(*string != 0){
		*video_memory = *string;
		*video_memory++; 
		*video_memory = color; 
		video_memory++;
		string++;
	}
	
}

void clear_screen_linear(){
	unsigned char *video_mem = (unsigned char*) VIDEO_ADDR; 
	const int NET_OFFSET =  2 * MAX_ROWS * MAX_COLS; 
	for(int i = 0; i < NET_OFFSET; i+=2){
		video_mem[i] = ' '; 
		video_mem[i+1] = 0;
	}
}
