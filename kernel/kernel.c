#include "screen.h"
#include "print.h"

void _start () {
	clear_screen();
	char *tab[] = {"1\n", "2\n", "3\n", "4\n", "5\n", "6\n", "7\n", "8\n", "9\n", "10\n","11\n","12\n","13\n","14\n","15\n","16\n","17\n","18\n","19\n","20\n","21\n","22\n","23\n","24\n","25\n","26\n","27\n","28\n","29\n","30\n","31\n" };
	
	for (int i = 0; i < 31; i++) {
		print(tab[i]);
		print("\n");
	}
}

