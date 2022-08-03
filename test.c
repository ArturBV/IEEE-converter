#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum {
	ROUND_BITS = 3,
	BITS_IN_BYTE = 8
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

char* strreverse(char* str, int len) {
	char tmp;

	for (int i = 0; i < len / 2; i++) {
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
	}

	return str;
}

char* test_binary_notion(Fraction* number, int precision) {
	int i, binary_str_len;
	int higher_bit_index;
	int compare_result;
	int tmp_value, is_integer;
	char *binary_str = (char*) calloc(precision + ROUND_BITS + 1, sizeof(char));
	char *round_bits = (char*) calloc(ROUND_BITS + 1, sizeof(char));

	if (number->denominator != 1) {
		tmp_value = number->denominator;
		is_integer = 0;
	} else {
		tmp_value = number->numerator;
		is_integer = 1;
		/* get higher bit of tmp_value (indexation from left) */
		/* why not take a solution from Hacker's Delight? */
		for (i = 0; !((tmp_value >> (sizeof(int) * BITS_IN_BYTE - i - 1)) & 1) &&
				i < sizeof(int) * BITS_IN_BYTE; i++) {
		}
		higher_bit_index = i;
	}
	printf("higher_bit_index:%d for %d\n", higher_bit_index, tmp_value);
	for (i = 0; i < precision + ROUND_BITS; i++) {

		/* FIXME */
		/* converting для целых чисел работает коряво */
		/* end of converting */
		if (tmp_value == 1) {
			binary_str[i++] = '1';
			binary_str_len = i;
			// i++;
			while (i < precision + ROUND_BITS) {
				binary_str[i++] = '0';
				// i++;
			}
			break;
		}

		/* main operation */
		if (!is_integer) {
			if (number->numerator / number->denominator) {
				binary_str[i] = '1';
			} else {
				binary_str[i] = '0';
			}
			number->numerator %= number->denominator;
		} else {
			if (tmp_value % 2) {
				binary_str[i] = '1';
			} else {
				binary_str[i] = '0';
			}
			tmp_value /= 2;
		}
	}
	binary_str[precision + ROUND_BITS] = '\0';
	if (is_integer) {
		printf("binary_str:%s\n", binary_str);
		strreverse(binary_str, precision + ROUND_BITS);
	}

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

	free(round_bits);
	binary_str[precision] = '\0';
	return binary_str;
}
int main(void) {
	Fraction n = {.numerator = 10,
				  .denominator = 1};
	char* bin = test_binary_notion(&n, 5);
	printf("%s\n", bin);
	return 0;
}