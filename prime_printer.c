#include <stdio.h>
#include <math.h>

/*
 * NOTE: when compiling(with gcc) on linux, it may need a -lm flag
 */

int main(){
	unsigned long long int i, q, prime;
	i=1;
	while(1){
		i++;
		prime=1;
		for(q=2; q <= sqrt((double)i); ++q)	{
			if(i % q == 0) {
				prime=0;
				break;
			}
		}
		if(prime == 1)
			printf("%llu\n", i);
	}
	return 0;
}
