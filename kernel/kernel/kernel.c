#include <stdio.h>

#include <kernel/tty.h>
#include "../arch/i386/vga.h"

void kernel_main(void) {
	terminal_initialize();

	while (1==1) {
		terminal_setcolor( vga_entry_color( VGA_COLOR_LIGHT_CYAN, VGA_COLOR_DARK_GREY ) );
		printf("Hallo Welt\n");

		terminal_setcolor( vga_entry_color( VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLUE ) );
		printf("Ich bin ein Betriebssystem!\n");

		terminal_setcolor( vga_entry_color( VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK ) );
		printf("Ein dritter Text.\n");
	}

}
