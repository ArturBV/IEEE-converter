#include <stdio.h>
#include <stdlib.h>

enum {
	BUFFSIZE = 31
};

int is_digit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}

int get_number(char* parameter_name) {
	char c;
	char buf[BUFFSIZE];
	int i = 0;
	int found_trouble = 0;
/*FIXMEEEE*/
	while (found_trouble) {
		found_trouble = 0;
		/* empty string case */
		if ((c = getchar()) == '\n') {
			printf("Incorrect input! Please, enter a number\n");
			printf("bits for %s: ", parameter_name);
			continue;
		} else {
			buf[i++] = c;
		}

		while ((c = getchar()) != '\n' && c != EOF) {
			if (!is_digit(c)) {
				/* input error */
				/* skip wrong input */
				while ((c = getchar()) != '\n' && c != EOF) {}
				printf("Incorrect input! Please, enter a number\n");
				printf("bits for %s: ", parameter_name);
				/* reset buf index */
				i = 0;
				found_trouble = 1;
			} else {
				buf[i++] = c;
			}
		}

		found_trouble = 1;
	}

	// while ((c = getchar()) != '\n' && c != EOF) {
	// 	if (!is_digit(c)) {
	// 		/* input error */
	// 		/* skip wrong input */
	// 		while ((c = getchar()) != '\n' && c != EOF) {}
	// 		printf("Incorrect input! Please, enter a number\n");
	// 		printf("bits for %s: ", parameter_name);
	// 		/* reset buf index */
	// 		i = 0;
	// 		continue;
	// 	}
	// 	buf[i++] = c;
	// }

	buf[i] = '\0';
	printf("%s\n", buf);
	return atoi(buf);
}

void get_params(int *exp_n, int *frac_n) {
	printf("IEEE(?-754?)\n");
	printf("Set the length of parameters:\n");

	printf("bits for exp: ");
	*exp_n = get_number("exp");

	printf("bits for frac: ");
	*frac_n = get_number("frac");
}