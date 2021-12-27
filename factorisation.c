#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * NOTE: This program is not complete, optimisations(e.g. making it factorise the number once)
 * are still in progress
 */

typedef unsigned long long int ulli;


ulli *pvar[2];

void innitpvar(ulli size) {
	pvar[0]=malloc(size * sizeof(ulli));
	pvar[1]=malloc(size * sizeof(ulli));
	if(pvar[0] == NULL || pvar[1] == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char **argv) {
	ulli val, i, p, size, current, tval;
	ulli j;
	time_t t_start, t_end;
	if(argc == 1) {
		printf("Usage: %s <numbers to be factorised>\n", argv[0]);
		return 0;
	}
	for(i = 1; i < argc; i++) {
		p=sscanf(argv[i], "%lld", &val);
		if(val <= 0 || p != 1)
			continue;
		tval=val;
		p=2;
		current=0;
		size=1;
		printf("value to be factorised: %lld\n", val);
		t_start=time(NULL);
		printf("running tests... ");
		for(j=2; j < tval; j++) {
			if(0==(tval % j)){
				size++;
				tval=tval / j;
			}
		}
		t_end=time(NULL);
		printf("Done!\n");
		printf("eta time to factorize %lld: %ld\n", val, (t_end - t_start));
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
			printf("%lld\t|\t%lld\n", pvar[0][a], pvar[1][a]);
		free(pvar[0]);
		free(pvar[1]);
	}
	return 0;
}
