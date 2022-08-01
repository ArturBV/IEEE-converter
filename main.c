#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* constants are here */
#include "files/parameter_handler.h"
#include "files/input_handler.h"

#define ROUND_BITS 3

typedef struct Fraction {
	int numerator;
	int denominator;
} Fraction;

void add_bit(char* number, int index) {
	if (index < 0) {
		return;
	}

	if (number[index] == '1') {
		number[index] = '0';
		add_bit(number, index - 1);
		return;
	}

	/* if number[index] == '0' */
	number[index] = '1';
	return;
}

/* denominator > 1 */
char* binary_notion(Fraction* number, int precision) {
	int compare_result;
	// 
	char *binary_str = (char*) calloc(precision + ROUND_BITS + 1, sizeof(char));
	char *round_bits = (char*) calloc(ROUND_BITS + 1, sizeof(char));
	for (int i = 0; i < precision + ROUND_BITS; i++) {
		number->denominator /= 2;
		if (number->denominator == 1) {
			binary_str[i] = '1';
			if (i >= precision) {
				round_bits[i - precision] = binary_str[i];
			}
			i++;
			while (i < precision + ROUND_BITS) {
				binary_str[i] = '0';
				if (i >= precision) {
					round_bits[i - precision] = binary_str[i];
				}
				i++;
			}
			break;
		}

		if (number->numerator / number->denominator) {
			binary_str[i] = '1';
		} else {
			binary_str[i] = '0';
		}
		number->numerator %= number->denominator;

		if (i >= precision) {
			round_bits[i - precision] = binary_str[i];
		}
	}
	binary_str[precision + ROUND_BITS] = '\0';
	round_bits[ROUND_BITS] = '\0';

	/* even-round */
	compare_result = strcmp(round_bits, "100");
	if (compare_result == 0) {
		if (binary_str[precision - 1] == '1') {
			add_bit(binary_str, precision - 1);
		}
	} else if (compare_result > 0) {
		add_bit(binary_str, precision - 1);
	}

	free(round_bits);
	binary_str[precision] = '\0';
	return binary_str;
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

	s = '0';
	exp_str = (char*) calloc(exp_n + 1, sizeof(char));
	// frac_str = (char*) calloc(frac_n + 1, sizeof(char));

	/* not a frac case */
	if (num->denominator == 1) {
		/* s */
		if (num->numerator < 0) {
			s = '1';
			num->numerator *= -1;
		}

		/* exp */
		exp_shift = pow(2., exp_n - 1) - 1;
		exp_shift = (2 << (exp_n - 1)) - 1;
		while (num->numerator >= (2 << (e_power + 1))) {
			e_power++;
		}
		exp = (int) exp_shift + e_power;
		for (int i = 0; i < exp_n; i++) {
			if (exp>>(exp_n - i - 1) & 1) {
				exp_str[i] = '1';
			} else {
				exp_str[i] = '0';
			}
		}
		exp_str[exp_n] = '\0';
		
		/* frac */
		num->denominator = 2 << e_power; /* 2^e_power */
		num->numerator -= num->denominator; /* 0 <= num <= 1 */

		// frac_round = (char*) calloc(frac_n + ROUND_BITS + 1, sizeof(char));
		// round_bits = (char*) calloc(ROUND_BITS + 1, sizeof(char));
		// for (int i = 0; i < frac_n + ROUND_BITS; i++) {
		// 	num->denominator >>= 1; /* /= 2 */
		// 	if (num->denominator == 1) {
		// 		frac_round[i] = '1';
		// 		if (i >= frac_n) {
		// 			round_bits[i - frac_n] = frac_round[i];
		// 		}
		// 		i++;
		// 		while (i < frac_n + ROUND_BITS) {
		// 			frac_round[i] = '0';
		// 			if (i >= frac_n) {
		// 				round_bits[i - frac_n] = frac_round[i];
		// 			}
		// 			i++;
		// 		}
		// 		break;
		// 	}

		// 	if (num->numerator / num->denominator) {
		// 		frac_round[i] = '1';
		// 	} else {
		// 		frac_round[i] = '0';
		// 	}
		// 	num->numerator %= num->denominator;

		// 	if (i >= frac_n) {
		// 		round_bits[i - frac_n] = frac_round[i];
		// 	}
		// }
		// frac_round[frac_n + ROUND_BITS] = '\0';
		// round_bits[ROUND_BITS] = '\0';

		frac_str = binary_notion(num, frac_n);
	}

	printf("Result: %c %s %s\n", s, exp_str, frac_str);


	printf("%d\n", exp);
	// printf("%f\n", pow(2, e_power));
	// printf("%lld\n", exp_shift);
	// printf("%d %d\n", exp_n, frac_n);
	printf("%d / %d\n", num->numerator, num->denominator);
	free(exp_str);
	free(frac_str);
	free(num);
	return 0;
}
