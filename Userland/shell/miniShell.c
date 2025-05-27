#include <miniShell.h>

void shellInit() {

	sysWrite(1, "miniShell > ", strlen("miniShell > "));

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

    char buffer[128];
void shellUpdate() {
    
    sysRead(1, buffer, 12);

 	sysDraw();
}

