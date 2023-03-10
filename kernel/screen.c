#include "screen.h"
#include "memory_copy.h"
#include "cursor.h"
#include "offset.h"

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char* screen = (char*)VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor(get_screen_offset(0, 0));
}

int handle_scrolling(int offset) { 
	memory_copy((char*)VIDEO_ADDRESS + (MAX_COLS * 2), (char*) VIDEO_ADDRESS, MAX_COLS * (MAX_ROWS - 1) * 2);
	
	for (int col = 0; col < MAX_COLS; col++) {
        set_char_at_video_memory('\0', get_screen_offset(MAX_ROWS - 1, col));
    }
	return offset - (2 * MAX_COLS);
}