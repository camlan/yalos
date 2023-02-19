#include "screen.h"

void print_at(char* message, int col, int row) {
	// Update the cursor if col and row not negative .
	if ( col >= 0 && row >= 0) {
		set_cursor (get_screen_offset(col,row));
	}
	// Loop through each char of the message and print it.
	int i = 0;
	while (message[i] != 0) {
		print_char (message[i++], col, row, WHITE_ON_BLACK);
	}
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



