#include "screen.h"

int get_screen_offset(int row, int col) {
	return 2 * (row * MAX_COLS + col);
}

int get_row_from_screen_offset(int offset) {
    return offset / (2 * MAX_COLS);
}

int move_screen_offset_to_new_line(int offset) {
    return get_screen_offset(get_row_from_screen_offset(offset) + 1, 0);
}
