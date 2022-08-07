#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* some constants are here */
#include "files/parameter_handler.h"
#include "files/input_handler.h"

enum {
	NORMAL,
	DENORMAL,
	ROUND_BITS = 3,
	BITS_IN_INT = 8 * sizeof(int)
};

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

/* reduce frac before call this function */
/* number must be betwen 0 and 1 */
char* binary_notion(Fraction* number, int precision) {
	int i;
	int compare_result, need_round = 1;
	int tmp_value, tmp_bin_len, is_integer;
	char *binary_str = (char*) calloc(precision + ROUND_BITS + 1, sizeof(char));
	char *round_bits = (char*) calloc(ROUND_BITS + 1, sizeof(char));
	
	Fraction *number_cp = (Fraction*) calloc(1, sizeof(Fraction));
	number_cp->numerator = number->numerator;
	number_cp->denominator = number->denominator;

	if (number_cp->denominator != 1) {
		tmp_value = number_cp->denominator;
		is_integer = 0;
	} else {
		tmp_value = number_cp->numerator;
		is_integer = 1;

		/* get higher bit of tmp_value (indexation from left) and store in `i` */
		/* why not take a solution from Hacker's Delight? */
		/* nah, too easy */
		for (i = 0; !((tmp_value >> (BITS_IN_INT - i - 1)) & 1) &&
		        i < BITS_IN_INT; i++) {}

		/* len of tmp_value in binary notation without leading zeros */
		tmp_bin_len = BITS_IN_INT - i;

		if (tmp_bin_len <= precision) {
			/* get binary str */
			for (i = 0; i < precision - tmp_bin_len; i++) {
				binary_str[i] = '0';
			}
			for (i = 0 ; i < tmp_bin_len; i++) {
				binary_str[precision - i - 1] = '0' + tmp_value % 2;
				tmp_value /= 2;
			}
			need_round = 0;
		}
	}

	for (i = 0; i < precision + ROUND_BITS; i++) {
		/* end of converting */
		if ((i + 1 > tmp_bin_len && is_integer) || (number_cp->denominator == 1 && !is_integer)) {
			while (i < precision + ROUND_BITS) {
				binary_str[i++] = '0';
			}
			break;
		}

		/* main operation */
		if (!is_integer) {
			/* int overflow? wtf why?*/
			number_cp->numerator *= 2;
			if (number_cp->numerator / number_cp->denominator) {
				binary_str[i] = '1';
				number_cp->numerator -= number_cp->denominator;
			} else {
				binary_str[i] = '0';
			}
		} else if (tmp_bin_len > precision) {
			binary_str[i] = '0' + ((tmp_value >> (tmp_bin_len - i - 1)) & 1);
		} else {
			/* binary_str is done before loop */
			break;
		}
	}

	if (need_round) {
		binary_str[precision + ROUND_BITS] = '\0';
		strncpy(round_bits, (binary_str + precision), ROUND_BITS);
		round_bits[ROUND_BITS] = '\0';

		compare_result = strcmp(round_bits, "100");
		if (compare_result == 0) {
			/* even-round */
			if (binary_str[precision - 1] == '1') {
				add_bit(binary_str, precision - 1);
			}
		} else if (compare_result > 0) {
			add_bit(binary_str, precision - 1);
		}
	}

	free(number_cp);
	free(round_bits);
	binary_str[precision] = '\0';
	return binary_str;
}


int cmp_abs_fraction(Fraction* n1, Fraction* n2) {
	long long tmp_1 = abs(n1->numerator) * n2->denominator;
	long long tmp_2 = abs(n2->numerator) * n1->denominator;

	if (tmp_1 > tmp_2) {
		return 1;
	}

	if (tmp_1 == tmp_2) {
		return 0;
	}

	return -1;
}

int gcd(int a, int b) {
	if (b == 0 || a == 0) {
		return a + b;
	}

	if (a > b) {
		return gcd(b, a % b);
	}

	return gcd(a, b % a);
}

void reduce_frac(Fraction* number) {
	int gcd_num;
	gcd_num = gcd(number->numerator, number->denominator);

	number->numerator /= gcd_num;
	number->denominator /= gcd_num;
}

int main(void) {
	char s;
	int exp_n, frac_n;
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
	/* binary notation:	|s||  exp_str  ||  frac_str  | */
	/* s */
	if (num->numerator < 0) {
		s = '1';
		num->numerator *= -1;
	} else {
		s = '0';
	}
	reduce_frac(num);

	int exp_shift;
	exp_shift = (1 << (exp_n - 1)) - 1;

	int number_type;
	int frac_step = 1 << frac_n;
	Fraction min_denormal = {
		.numerator = 1,
		.denominator = (1 << (exp_shift - 1)) * frac_step
	};
	Fraction max_denormal = {
		.numerator = frac_step - 1,
		.denominator = min_denormal.denominator
	};

	if (cmp_abs_fraction(num, &max_denormal) <= 0) {
		number_type = DENORMAL;
	} else {
		number_type = NORMAL;
	}

	char *exp_str, *frac_str, *full_str;
	int exp_i;
	int e_power = 0;
	Fraction exp_f = {
		.numerator = 0,
		.denominator = 1
	};

	/* exp_i */
	if (number_type == NORMAL) {
		if (num->numerator >= num->denominator) {
			while (num->numerator > num->denominator * 2) {
				num->denominator *= 2;
				reduce_frac(num);
				e_power++;
			}
			num->numerator -= num->denominator;
			reduce_frac(num);
		} else {
			while (num->numerator < num->denominator) {
				num->numerator *= 2;
				reduce_frac(num);
				e_power--;
			}
			num->numerator -= num->denominator;
			reduce_frac(num);
		}
	} else { /* DENORMAL case */
		/* num <= max_denormal */
		e_power = 0 - exp_shift; /* 1 - exp_shift */
		num->numerator *= max_denormal.denominator / frac_step;
		reduce_frac(num);
	}

	exp_i = exp_shift + e_power;
	exp_f.numerator = exp_i;
	exp_str = binary_notion(&exp_f, exp_n);

	/* frac */
	frac_str = binary_notion(num, frac_n);
	full_str = binary_notion(num, frac_n + ROUND_BITS * 2);

	printf("Result: %c %s %s\n\n", s, exp_str, frac_str);

	if (number_type == NORMAL) {
		printf("NORMAL\n");
	} else {
		printf("DENORMAL\n");
	}

	printf("exp_i:%d (converts into binary)\n", exp_i);
	printf("exp_shift:%d\n", exp_shift);
	printf("e_power:%d\n", e_power);
	printf("frac before round:%s\n", full_str);

	free(full_str);
	free(exp_str);
	free(frac_str);
	free(num);
	return 0;
}
