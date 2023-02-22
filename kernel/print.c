#include "screen.h"


void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}

void print_char (char character, int col, int row, char attribute_byte) {
	
unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;

if (!attribute_byte) {
	attribute_byte = WHITE_ON_BLACK;
}

/* Get the video memory offset for the screen location */
int offset ;

/* If col and row are non - negative , use them for offset . */
if (col >= 0 && row >= 0) {
	offset = get_screen_offset(col, row);
/* Otherwise , use the current cursor position . */
} else {
	offset = get_cursor();
}

// If we see a newline character , set offset to the end of
// current row , so it will be advanced to the first col
// of the next row.
if (character == '\n') {	
	offset = move_screen_offset_to_new_line(offset);
	// int rows = offset/(2*MAX_COLS);
	// offset = get_screen_offset(MAX_COLS-1, rows);
	// Otherwise , write the character and its attribute byte to
	// video memory at our calculated offset .
} else {
	set_char_at_video_memory(character, offset);
	
	// vidmem[offset] = character;
	// vidmem[offset+1] = attribute_byte;
}

// Update the offset to the next character cell , which is
// two bytes ahead of the current cell .
offset += 2;
// Make scrolling adjustment , for when we reach the bottom
// of the screen .
offset = handle_scrolling (offset);
// Update the cursor position on the screen device .
set_cursor (offset);
}

void print_2(char* message) {
    int offset = get_cursor();
    int i = 0;
    while (message[i] != 0) {
		
		if (offset >= VIDEO_MEMORY_SIZE) {
			offset = handle_scrolling_2(offset);
			
		}
		
        if (message[i] == '\n') {
            // offset = move_screen_offset_to_new_line(offset);
			//set_char_at_video_memory('W', offset);
            //offset += 2;
			offset = move_screen_offset_to_new_line(offset);
			
        } else {
            set_char_at_video_memory(message[i], offset);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}


