# include <stdio.h>
# include <stdlib.h>

unsigned long long dupMasLargo(unsigned long long x){
	unsigned long long dup1;
	unsigned long long dup2;
	unsigned long long res;
	unsigned long long dml;
	unsigned long long size;
	unsigned long long i;
	size = 0;
	i = 0;
	res = 0;
	
	while (i < 32){
		dup1 = x;
		dup2 = x;
		dup1 = (dup1 << (63 - i)) >> (63 - i);
		dup2 = ((dup2 << (63 - i - i -1)) >> (63 - i)); 
		if (dup1 == dup2) {
			res = dup1;
			size = i + 1;
		}
		i++;
	}
	size = size << 32;
	dml = size | res;
	return dml;
}

