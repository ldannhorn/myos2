#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include <kernel/vga.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}


void terminal_scroll_up()
{
	uint16_t* new_terminal_buffer;
	
	// Copy lines 1 - VGA_HIGHT into new buffer
	for (size_t y = 1; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index_src = y * VGA_WIDTH + x;
			const size_t index_new = (y-1) * VGA_WIDTH + x;
			new_terminal_buffer[index_new] = terminal_buffer[index_src];
		}
	}

	// Fill last line with ' '
	for (size_t x = 0; x < VGA_WIDTH; x++) {
		const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
		new_terminal_buffer[index] = vga_entry(' ', terminal_color);
	}

	// Replace terminal_buffer
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = new_terminal_buffer[index];
		}
	}
}

void terminal_newline()
{
	terminal_column = 0;
	terminal_row++;

	if (terminal_row == VGA_HEIGHT) {
		terminal_row = VGA_HEIGHT - 1;
		terminal_scroll_up();
	}
}

void terminal_putchar(char c) 
{
	unsigned char uc = c;

	// Handle newline
	if (uc == '\n') {
		terminal_newline();
		return;
	}

	// Put char
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	
	// Move position right and put newline if at the end
	if (++terminal_column == VGA_WIDTH) {
		terminal_newline();
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
