#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "files/parameter_handler.h"
#include "files/input_handler.h"

#define BIN_ROUND 3

typedef struct Fraction {
	int numerator;
	int denominator;
} Fraction;

void get_binary(int src, char* dst, int round) {

}

int main(void) {
	int exp_n, frac_n;
	// int numerator = 0;
	// int denominator = 1;
	Fraction* num = (Fraction*) calloc(1, sizeof(Fraction));
	num->numerator = 0;
	num->denominator = 1;

	/* parameter_handler */
	get_params(&exp_n, &frac_n);
	
	/* input_handler */
	get_number(&(num->numerator), &(num->denominator));
	if (num->denominator == 0) {
		printf("Error! Division by zero!\n");
		return 1;
	}

	/* IEEE notation:   (-1)^s * m * 2^e */
	/* binary notation:	|s||  exp  ||  frac  | */
	long long exp_shift;
	char s, *exp_str, *frac_str;
	int exp;
	int e_power = 1;

	exp_shift = pow(2., exp_n - 1) - 1;
	s = '0';
	exp_str = (char*) calloc(exp_n + 1, sizeof(char));
	frac_str = (char*) calloc(frac_n + 1, sizeof(char));
	/* not a frac case */
	if (num->denominator == 1) {
		/* s */
		if (num->numerator < 0) {
			s = '1';
			num->numerator *= -1;
		}

		/* exp */
		while (num->numerator >= (int) pow(2, e_power + 1)) {
			e_power++;
		}
		exp = (int) exp_shift + e_power;
		
		/* frac */
		num->numerator -= (int) pow(2, e_power);
		get_binary(num->numerator, frac_str, frac_n);
	}



	// printf("%d\n", exp);
	// printf("%f\n", pow(2, power_cnt));
	// printf("%lld\n", exp_shift);
	// printf("%d %d\n", exp_n, frac_n);
	// printf("%d / %d\n", numerator, denominator);
	free(exp_str);
	free(frac_str);
	return 0;
}