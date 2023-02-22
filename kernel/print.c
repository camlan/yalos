#include "screen.h"

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}

void print(char* message) {
    int offset = get_cursor();
    int i = 0;
    while (message[i] != 0) {		
        if (message[i] == '\n') {
			offset = move_screen_offset_to_new_line(offset);
        } else {
            set_char_at_video_memory(message[i], offset);
            offset += 2;
        }
        if (offset >= VIDEO_MEMORY_SIZE) {
			offset = handle_scrolling(offset);	
		}
        i++;
    }
    set_cursor(offset);
}