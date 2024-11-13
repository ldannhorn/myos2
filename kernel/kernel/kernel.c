#include <stdio.h>

#include <kernel/tty.h>
//#include "vga.h"

void kernel_main(void) {
	terminal_initialize();

	while (1==1) {
		terminal_setcolor( 11 | 8 << 4 );
		printf("Hallo Welt\n");

		terminal_setcolor( 10 | 1 << 4 );
		printf("Ich bin ein Betriebssystem!\n");

		terminal_setcolor( 13 | 0 << 4 );
		printf("Ein dritter Text.\n");
	}

}
