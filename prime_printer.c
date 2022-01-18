#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * NOTE: when compiling(with gcc) on linux, it may need a -lm flag
 */
void bigfactor(unsigned long long int i) {
	unsigned long long int prime, q;
	i--;
	while(1) {
		i++;
		prime=1;
		if( i % 2 == 0)
			continue;
		for(q=3; q<= i/2; q+=2) {
			if(i % q == 0) {
				prime=0;
				break;
			}
		}
		if(prime==1)
			printf("%llu\n", i);
	}
	return;
}

int main(){
	unsigned long long int i, q, prime, e;
	i=1;
	while(1){
		i++;
		prime=1;
		e=sqrt((double)i);
		/*
		 * check to ensure that the values dont go out of hand
		 * if it does, I guess we cant square root it anymore...
		 * may impliment it in the future to avoid
		 * such a thing from happening hence making the code slightly faster
		 */
		if(e == HUGE_VAL)
			bigfactor(i);

		if( i % 2 == 0) {
			if(i == 2)
				puts("2");
			//shhh I'm lazyyyyy
			continue;
		}
		for(q=3; q <= e; q+=2)	{
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
