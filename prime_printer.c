#include <stdio.h>
int main(){
	long int i, q, prime;
	i=1;
	while(1){
		i++;
		prime=1;
		for(q=2; q <= i / 2; ++q)	{
			if(i % q == 0) {
				prime=0;
				break;
			}
		}
		if(prime == 1)
			printf("%ld\n", i);
	}
	return 0;
}
