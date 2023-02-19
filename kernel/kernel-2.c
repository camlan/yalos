#include "screen.h"

void _start () {
	clear_screen();
	print_2("Hello");
	set_cursor(get_cursor() + 80 * 2- 10);
	print_2("World");
	print_2("World\nBrave");
	
	char *tab[] = {"a", "b", "c", "d", "e", "f", "g","h","i","j","m","n","o","p","r","s","t","u","x","y","z","1","2","3","5","4","777", "444" };
	
	for (int i = 0; i < MAX_ROWS+3; i++) {
		print_2("\n");
	}
}

