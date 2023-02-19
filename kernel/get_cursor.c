#include "screen.h"

int get_cursor() {
	port_byte_out ( REG_SCREEN_CTRL , 14);
	int offset = port_byte_in ( REG_SCREEN_DATA ) << 8;
	port_byte_out ( REG_SCREEN_CTRL , 15);
	offset += port_byte_in ( REG_SCREEN_DATA );
	// Since the cursor offset reported by the VGA hardware is the
	// number of characters , we multiply by two to convert it to
	// a character cell offset .
	return offset *2;
} 