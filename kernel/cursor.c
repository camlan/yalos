#include "screen.h"

int get_cursor() {
	port_byte_out (REG_SCREEN_CTRL , 14);
	int offset = port_byte_in (REG_SCREEN_DATA) << 8;
	port_byte_out (REG_SCREEN_CTRL , 15);
	offset += port_byte_in (REG_SCREEN_DATA);
	// Since the cursor offset reported by the VGA hardware is the
	// number of characters, we multiply by two to convert it to
	// a character cell offset.
	return offset*2;
} 

void set_cursor(int offset) {
    // Convert from cell offset to char offset .
    offset /= 2;
    // This is similar to get_cursor , only now we write
    // bytes to those internal device registers.
    port_byte_out (REG_SCREEN_CTRL , 14);
    port_byte_out (REG_SCREEN_DATA , (unsigned char)(offset >> 8));
    port_byte_out (REG_SCREEN_CTRL , 15);
    port_byte_out (REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}