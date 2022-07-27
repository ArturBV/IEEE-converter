#include <stdio.h>
#include <stdlib.h>

#include "files/input_handler.h"

int main(void) {
	int exp_n, frac_n;
	get_params(&exp_n, &frac_n);

	
	

	printf("%d %d\n", exp_n, frac_n);
	return 0;
}