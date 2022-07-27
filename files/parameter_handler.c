#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	LOWER_LIMIT = 0,
	UPPER_LIMIT = 61,
	BUFFSIZE = 300
};

enum ERRORS {
	SUCCESS,
	ERR_EMPTY,
	ERR_OUT_OF_BOUND,
	ERR_NDIGIT
};

int is_digit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}

int check_input(char buf[]) {
	if (buf[0] == '\n') {
		return ERR_EMPTY;
	}

	int i;
	for (i = 0; buf[i] != '\n'; i++) {
		if (!is_digit(buf[i])) {
			return ERR_NDIGIT;
		}
	}
	buf[i] = '\0';

	if (atoi(buf) >= UPPER_LIMIT || atoi(buf) <= LOWER_LIMIT) {
		return ERR_OUT_OF_BOUND;
	} 

	return SUCCESS;
}

int read_input(char* parameter_name) {
	char buf[BUFFSIZE];	
	int check_result;

	/* buf = "<symbols>\n\0" */
	fgets(buf, BUFFSIZE, stdin);
	check_result = check_input(buf);
	/* 
	`check_result` side effect - removing '\n'(if `buf` is not just '\n'): 
	buf = "<symbols>\0" 
	*/
	while (check_result != SUCCESS) {
		printf("Incorrect input! ");

		switch (check_result) {
			case ERR_EMPTY:
			case ERR_NDIGIT:
				printf("Please, enter a number\n");
				break;
			case ERR_OUT_OF_BOUND:
				printf("Your number is out of limit(%d, %d)\n", LOWER_LIMIT + 1, UPPER_LIMIT - 1);
				break;
			default:
				printf("You mustn't see this message\n");
		}
		
		printf("bits for %s: ", parameter_name);
		fgets(buf, BUFFSIZE, stdin);
		check_result = check_input(buf);
	}
	
	return atoi(buf);
}

void get_params(int *exp_n, int *frac_n) {
	printf("IEEE(?-754?)\n");
	printf("Set the length of parameters:\n");

	printf("bits for exp: ");
	*exp_n = read_input("exp");

	printf("bits for frac: ");
	*frac_n = read_input("frac");
}
