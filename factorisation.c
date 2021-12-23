#include <stdio.h>
#include <stdlib.h>


int *pvar[2];

void innitpvar(int size) {
	pvar[0]=(int *)malloc(size * sizeof(int));
	pvar[1]=(int *)malloc(size * sizeof(int));
	if(pvar[0] == NULL || pvar[1] == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char **argv) {
	int val, i;
	int p, size, current, tval;
	int j;
	if(argc == 1) {
		printf("Usage: %s <numbers to be factorised>\n", argv[0]);
		return 0;
	}
	for(i = 1; i < argc; i++) {
		val=atoi(argv[i]);
		tval=val;
		p=2;
		current=0;
		size=1;
		/*skips any negative values*/
		if(val <= 0)
			continue;
		printf("value to be factorised: %d\n", val);
		printf("running tests... ");
		for(j=2; j < tval; j++) {
			if(0==(tval % j)){
				size++;
				tval=tval / j;
			}
		}
		printf("Done!\n");
		innitpvar(size);
		while(p <= val) {
			if(0==(val % p)) {
				if(pvar[0][current] == p) {
					pvar[1][current]++;
				}
				else {
					/* no value of that in arr yet*/
					current++;
					pvar[0][current] = p;
					pvar[1][current] = 1;
				}
				val = val / p;
			} else
				p++;
		}
		printf("prime\t|\tamount\n");
		for(int a=1; a<=size; a++)
			printf("%d\t|\t%d\n", pvar[0][a], pvar[1][a]);
		free(pvar[0]);
		free(pvar[1]);
	}
	return 0;
}
