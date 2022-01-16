#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long int ulli;
size_t relloc_size;


ulli *pvar[2];

void innitpvar() {
	relloc_size=sizeof(ulli);
	pvar[0]=malloc(relloc_size);
	pvar[1]=malloc(relloc_size);
	if(pvar[0] == NULL || pvar[1] == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv) {
	ulli val, i, p, current;
	if(argc == 1) {
		printf("Usage: %s <numbers to be factorised>\n", argv[0]);
		return 0;
	}
	for(i = 1; i < argc; i++) {
		p=sscanf(argv[i], "%llu", &val);
		if(val <= 0 || p != 1)
			continue;
		p=2;
		current=0;
		printf("value to be factorised: %llu\n", val);
		innitpvar();
		while(p <= val) {
			if(0==(val % p)) {
				if(pvar[0][current] == p) {
					pvar[1][current]++;
				}
				else {
					/* no value of that in arr yet*/
					relloc_size += sizeof(ulli);
					pvar[0] = realloc(pvar[0], relloc_size);
					pvar[1] = realloc(pvar[1], relloc_size);
					current++;
					pvar[0][current] = p;
					pvar[1][current] = 1;
				}
				val = val / p;
			} else
				p++;
		}
		printf("prime\t|\tpower\n");
		for(int a=1; a<=current; a++)
			printf("%llu\t|\t%llu\n", pvar[0][a], pvar[1][a]);
		free(pvar[0]);
		free(pvar[1]);
	}
	return 0;
}
