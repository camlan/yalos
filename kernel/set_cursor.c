#include "screen.h"

void set_cursor(int offset) {
offset /= 2; // Convert from cell offset to char offset .
// This is similar to get_cursor , only now we write
// bytes to those internal device registers.
port_byte_out (REG_SCREEN_CTRL , 14);
port_byte_out (REG_SCREEN_DATA , (unsigned char)(offset >> 8));
port_byte_out (REG_SCREEN_CTRL , 15);
port_byte_out (REG_SCREEN_DATA, (unsigned char)(offset & 0xff));

//offset -= 2* MAX_COLS;
// Return the updated cursor position .
//return offset;
}