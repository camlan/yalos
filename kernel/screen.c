#include "screen.h"

void clear_screen () {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor(get_screen_offset(0, 0));
}

int handle_scrolling ( int cursor_offset ) {
	// If the cursor is within the screen , return it unmodified .
	if ( cursor_offset < MAX_ROWS * MAX_COLS *2) {
	return cursor_offset ;
	}
	/* Shuffle the rows back one . */
	int i;
	for (i =1; i < MAX_ROWS ; i ++) {
	memory_copy ( get_screen_offset (0 , i) + VIDEO_ADDRESS ,
	get_screen_offset (0 ,i -1) + VIDEO_ADDRESS ,
	MAX_COLS *2
	);
	}
	/* Blank the last line by setting all bytes to 0 */
	char * last_line = get_screen_offset (0 , MAX_ROWS -1) + VIDEO_ADDRESS ;
	for (i =0; i < MAX_COLS *2; i ++) {
	last_line [i] = 0;
	}
	// Move the offset back one row , such that it is now on the last
	// row , rather than off the edge of the screen .
	cursor_offset -= 2*MAX_COLS;
	// Return the updated cursor position .
	return cursor_offset;
}

int handle_scrolling_2 (int offset) { 
	memory_copy((char*)VIDEO_ADDRESS + (MAX_COLS * 2), VIDEO_ADDRESS, MAX_COLS * (MAX_ROWS - 1) * 2);
	
	for (int col = 0; col < MAX_COLS; col++) {
        set_char_at_video_memory(' ', get_screen_offset(MAX_ROWS - 1, col));
    }
	
	return offset - 2 * MAX_COLS;
}