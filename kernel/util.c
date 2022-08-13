#include "util.h"
#include "../drivers/screen.h"

void memory_set(char* dest, char c, int no_bytes){
	for(int i = 0; i < no_bytes; i++){
		*(dest + i) = c; 
	}
}

void memory_copy(char* source, char* dest, int no_bytes){
	for(int i = 0; i < no_bytes; i++){
		*(dest + i) = *(source + i); 
	}
}

bool str_eq(char* str1, char* str2){
	if(sizeof(str1) != sizeof(str2)){
		return 0; // If they aren't equal in size, they aren't equal.
	}
	int i = 0; 
	while(1){
		if(str1[i] != str2[i]){
			return 0; // If a single character isn't equal in both strings, then they aren't equal.
		}
		
		if(str1[i] == '\0' && str2[i] == '\0'){
			return 1; // If all tests pass, the strings are equal.
		}
		i++;
	}
}

bool is_number(char* str){
	for(int i = 48; i <= 57; i++){
		if(str == i) return true; 
	}
	return false; 
}
