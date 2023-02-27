#ifndef SCREEN_CONST_FUNC
#define SCREEN_CONST_FUNC
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define VIDEO_MEMORY_SIZE (MAX_ROWS * MAX_COLS * 2)
#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void clear_screen();
int handle_scrolling(int offset);
void set_char_at_video_memory(char c, int i);
#endif
