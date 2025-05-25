#include <miniShell.h>

void shellInit() {
	int lastTime = sysTimeTicks();
	int deltaTime = 0;
	
	while(1) {

		if (deltaTime >= 1) {

            shellUpdate();

	        lastTime = sysTimeTicks();
		}

		deltaTime = sysTimeTicks() - lastTime;
	}

}

void shellUpdate() {
    
 	sysClear();
	sysWrite(1, "miniShell > ", strlen("miniShell > "));
 	sysDraw();
}


char* main_buff[1024];
uint32_t current_buff = 0;

void add_str(char* str) {
	for (int i = 0; i < strlen(str); i++) 
		main_buff[current_buff++] = str[i];
}

void miniShell() {

	char* read_buff[256];
	uint8_t hasCommand = 0;

	//add_str(SHELL_PROMT);
	main_buff[0] = 'a';
	main_buff[1] = 'b';
	main_buff[2] = 'c';

	int lastTime = sysTimeTicks();
	int deltaTime = 0;
	
	while(1) {

		if (deltaTime >= 1) {
 			sysClear();
			sysWrite(1, "miniShell > ", strlen("miniShell > "));
 			sysDraw();
			lastTime = sysTimeTicks();
		}

		deltaTime = sysTimeTicks() - lastTime;
	}
}

