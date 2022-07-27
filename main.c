#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "files/parameter_handler.h"
#include "files/input_handler.h"

typedef struct Fraction {
	int numerator;
	int denominator;	
} Fraction;

int main(void) {
	int exp_n, frac_n;
	long long exp_shift;
	Fraction number = {0, 1};

	/* parameter_handler */
	get_params(&exp_n, &frac_n);

	printf("\nEnter a number(`123`, `5/3`):\n");
	
	/* input_handler */
	get_number(&(number.numerator), &(number.denominator));

	exp_shift = pow(2., exp_n - 1) - 1;
	
	printf("%lld\n", exp_shift);
	printf("%d %d\n", exp_n, frac_n);
	return 0;
}