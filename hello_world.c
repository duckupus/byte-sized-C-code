#include <stdio.h>
#include <stdlib.h>

int main() {
	unsigned int i=0;
	int check[] = {0x1b, 0x5d, 0xa9, 0xb9, 0x285, 0x287, 0x2c8, 0x4ef, 0x5c3, 0x5d0, 0x672, 0x71a};
	int j = 0;
	srand(0x10);
	while(j < sizeof(check) / 4) {
		if(check[j] == i) {
			printf("%c", (rand() % 0x80));
			j++;
		} else
			rand();
		i++;
	}
	puts("");
	return 0;
}
