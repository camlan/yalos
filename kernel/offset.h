#ifndef OFFSET
#define OFFSET
int get_screen_offset(int row, int col);
int get_row_from_screen_offset(int offset);
int move_screen_offset_to_new_line(int offset);
#endif