
#include <stdlib.h>

void miniShell();

int main() {
	miniShell();

	return 0;
}

#define SHELL_PROMPT "miniShell > "

char* main_buff[1024];
uint32_t current_buff = 0;

void add_str(char* str) {
	for (int i = 0; i < strLen(str); i++) 
		main_buff[current_buff++] = str[i];
}

void miniShell() {

	char* read_buff[256];
	uint8_t hasCommand = 0;

	//add_str(SHELL_PROMT);
	main_buff[0] = 'a';
	main_buff[1] = 'b';
	main_buff[2] = 'c';

	int lastTime = time_ticks();
	int deltaTime = 0;
	
	while(1) {

		if (deltaTime >= 1) {
 			sys_clear();
			write(1, "miniShell > ", strLen("miniShell > "));
 			sys_draw();
			lastTime = time_ticks();
		}

		deltaTime = time_ticks() - lastTime;
	}
}

