#include "keyboard.h"

#include "../cpu/irqc.h"
#include "screen.h"
#include <stdbool.h>

// relevant key flags
bool shift = false; 
bool caps_lock = false; 
bool control = false; 

// arrowpad flags
int text_col; 
int in_text_col = true; 


void keyboard_handler(struct regs *r){
	unsigned char scan_code = port_byte_in(0x60);
	scan_code_handler(scan_code);
	
}

void scan_code_handler(unsigned char scan_code){
	switch (scan_code){
		case 0x36: // right shift pressed
		case 0x2A: // left shift pressed
			shift = true; 
			break;
		case 0xB6: // right shift released
		case 0xAA: // left shift released
			shift = false; 
			break;
		case 0x1D: // right or left control pressed
			control = true; 
			break;
		case 0x9D: // right or left control released
			control = false; 
			break;
		case 0x3A: // CAPS state editor
			caps_lock = !caps_lock; 
			break;
		case 0x1E:
			if(caps_lock || shift) {
				print("A");
				text_col_handler();
				break;
			}
			print("a");
			text_col_handler();
			break; 
		case 0x30: 
			if(caps_lock || shift) {
				print("B");
				text_col_handler();
				break;
			}
			print("b");
			text_col_handler();
			break;  
		case 0x2E:
			if(caps_lock || shift) {
				print("C");
				text_col_handler();
				break;
			}
			print("c");
			text_col_handler();
			break;
		case 0x20:
			if(caps_lock || shift) {
				print("D");
				text_col_handler();
				break;
			}
			print("d");
			text_col_handler();
			break; 
		case 0x12:
			if(caps_lock || shift) {
				print("E");
				text_col_handler();
				break;
			}
			print("e");
			text_col_handler();
			break;
		case 0x21:
			if(caps_lock || shift) {
				print("F");
				text_col_handler();
				break;
			}
			print("f");
			text_col_handler();
			break;
		case 0x22:
			if(caps_lock || shift) {
				print("G");
				text_col_handler();
				break;
			}
			print("g");
			text_col_handler();
			break;
		case 0x23:
			if(caps_lock || shift) {
				print("H");
				text_col_handler();
				break;
			}
			print("h");
			text_col_handler();
			break;
		case 0x17:
			if(caps_lock || shift) {
				print("I");
				text_col_handler();
				break;
			}
			print("i");
			text_col_handler();
			break;
		case 0x24:
			if(caps_lock || shift) {
				print("J");
				text_col_handler();
				break;
			}
			print("j");
			text_col_handler();
			break;
		case 0x25:
			if(caps_lock || shift) {
				print("K");
				text_col_handler();
				break;
			}
			print("k");
			text_col_handler();
			break;
		case 0x26:
			if(caps_lock || shift) {
				print("L");
				text_col_handler();
				break;
			}
			print("l");
			text_col_handler();
			break;
		case 0x32:
			if(caps_lock || shift) {
				print("M");
				text_col_handler();
				break;
			}
			print("m");
			text_col_handler();
			break;
		case 0x31:	
			if(caps_lock || shift) {
				print("N");
				text_col_handler();
				break;
			}
			print("n");
			text_col_handler();
			break;
		case 0x18:
			if(caps_lock || shift) {
				print("O");
				text_col_handler();
				break;
			}
			print("o");
			text_col_handler();
			break;
		case 0x19:
			if(caps_lock || shift) {
				print("P");
				text_col_handler();
				break;
			}
			print("p");
			text_col_handler();
			break;
		case 0x10:
			if(caps_lock || shift) {
				print("Q");
				text_col_handler();
				break;
			}
			print("q");
			text_col_handler();
			break;
		case 0x13:
			if(caps_lock || shift) {
				print("R");
				text_col_handler();
				break;
			}
			print("r");
			text_col_handler();
			break;
		case 0x1F:
			if(caps_lock || shift) {
				print("S");
				text_col_handler();
				break;
			}
			print("s");
			text_col_handler();
			break;
		case 0x14:
			if(caps_lock || shift) {
				print("T");
				text_col_handler();
				break;
			}
			print("t");
			text_col_handler();
			break;
		case 0x16:
			if(caps_lock || shift) {
				print("U");
				text_col_handler();
				break;
			}
			print("u");
			text_col_handler();
			break;
		case 0x2F:
			if(caps_lock || shift) {
				print("V");
				text_col_handler();
				break;
			}
			print("v");
			text_col_handler();
			break;
		case 0x11:
			if(caps_lock || shift) {
				print("W");
				text_col_handler();
				break;
			}
			print("w");
			text_col_handler();
			break;
		case 0x2D:
			if(caps_lock || shift) {
				print("X");
				text_col_handler();
				break;
			}
			print("x");
			text_col_handler();
			break;
		case 0x15:
			if(caps_lock || shift) {
				print("Y");
				text_col_handler();
				break;
			}
			print("y");
			text_col_handler();
			break;
		case 0x2C: 
			if(caps_lock || shift) {
				print("Z");
				text_col_handler();
				break;
			}
			print("z");
			text_col_handler();
			break;
		case 0x29:
			if(shift){
				print("~");
				text_col_handler();
				break;
			}
			print("`");
			text_col_handler();
			break;
		case 0x02:
			if(shift){
				print("!");
				text_col_handler();
				break;
			}
			print("1");
			text_col_handler();
			break;
		case 0x03:
			if(shift){
				print("@");
				text_col_handler();
				break;
			}
			print("2");
			text_col_handler();
			break;
		case 0x04:
			if(shift){
				print("#");
				text_col_handler();
				break;
			}
			print("3");
			text_col_handler();
			break;
		case 0x05:
			if(shift){
				print("$");
				text_col_handler();
				break;
			}
			print("4");
			text_col_handler();
			break;
		case 0x06:
			if(shift){
				print("%");
				text_col_handler();
				break;
			}
			print("5");
			text_col_handler();
			break;
		case 0x07:
			if(shift){
				print("^");
				text_col_handler();
				break;
			}
			print("6");
			text_col_handler();
			break;
		case 0x08:
			if(shift){
				print("&");
				text_col_handler();
				break;
			}
			print("7");
			text_col_handler();
			break;
		case 0x09:
			if(shift){
				print("*");
				text_col_handler();
				break;
			}
			print("8");
			text_col_handler();
			break;
		case 0x0A:
			if(shift){
				print("(");
				text_col_handler();
				break;
			}
			print("9");
			text_col_handler();
			break;
		case 0x0B:
			if(shift){
				print(")");
				text_col_handler();
				break;
			}
			print("0");
			text_col_handler();
			break;
		case 0x0C:
			if(shift){
				print("_");
				text_col_handler();
				break;
			}
			print("-");
			text_col_handler();
			break;
		case 0x0D:
			if(shift){
				print("+");
				text_col_handler();
				break;
			}
			print("=");
			text_col_handler();
			break;
		case 0x1A:
			if(shift){
				print("{");
				text_col_handler();
				break;
			}
			print("[");
			text_col_handler();
			break;
		case 0x1B:
			if(shift){
				print("}");
				text_col_handler();
				break;
			}
			print("]");
			text_col_handler();
			break;
		case 0x2B:
			if(shift){
				print("|");
				text_col_handler();
				break;
			}
			print("\\");
			text_col_handler();
			break;
		case 0x27:
			if(shift){
				print(":");
				text_col_handler();
				break;
			}
			print(";");
			text_col_handler();
			break;
		case 0xA8:
			if(shift){
				print("\"");
				text_col_handler();
				break;
			}
			print("\'");
			text_col_handler();
			break;
		case 0x33:
			if(shift){
				print("<");
				text_col_handler();
				break;
			}
			print(",");
			text_col_handler();
			break;
		case 0x34:
			if(shift){
				print(">");
				text_col_handler();
				break;
			}
			print(".");
			text_col_handler();
			break;
		case 0x39:
			print(" ");
			text_col_handler();
			break;
		case 0x0E:
			print("\b");
			break;
		case 0x1C:
			print("\n");
			text_col = 0;
			in_text_col = true;
			readln();
			break;
		// arrowpads
		case 0x4D:
			int offset = get_cursor();
			int rows = offset / (2 * MAX_COLS);
			int cols = offset / 2 - rows * MAX_COLS;
			if(!in_text_col){
				if(control){
					move_right(text_col - cols);
				}
				else{ move_right(1); }
		
				offset = get_cursor();
				cols = offset / 2 - rows * MAX_COLS;
				if(cols == text_col){
					in_text_col = true; 
				}
			}
			break;
		case 0x4B:
			offset = get_cursor();
	
			rows = offset / (2 * MAX_COLS);
			cols = offset / 2 - rows * MAX_COLS;
			if(cols == 0 && rows == 1 || cols == 0){
		
			}
			else{
				if(in_text_col){
					in_text_col = false; 
					text_col = cols;
				}
				if(control){
					move_left(cols);
				}
				else {move_left(1); } 
				
				offset = get_cursor();
				cols = offset / 2 - rows * MAX_COLS;
				if(cols == text_col){ in_text_col = true; }
			}
			break;
	}
}

void text_col_handler(){
	int offset = get_cursor();
	int rows = offset / (2 * MAX_COLS);
	int cols = offset / 2 - rows * MAX_COLS;
	
	if(cols > text_col){
		text_col = cols; 
		in_text_col = true;
	}
}

void keyboard_install(){
	irq_install_handler(IRQ1, keyboard_handler);
}
