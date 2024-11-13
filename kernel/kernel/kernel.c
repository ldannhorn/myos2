#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	while (1==1) {
		printf("Hallo Welt\n");
		printf("Ich bin ein Betriebssystem!\n");
		printf("Ein dritter Text.\n");
	}
}
