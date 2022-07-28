#include <stdio.h>
#include <stdlib.h>
#include "parameter_handler.h"


int check_number(char buf[]) {
	int i;
	int slash_index = -1;

	if (buf[0] == '\n') {
		return ERR_EMPTY;
	}

	for (i = 0; buf[i] != '\0'; i++) {
		if (buf[i] == '\n') {
			buf[i] = '\0';
			break;
		}
		/* remember first slash index */
		if (slash_index == -1 && buf[i] == '/') {
			slash_index = i;
		}
	}

	/* i == len of `buf` without '\n' */
	if (slash_index == 0 || slash_index == i - 1) {
		return ERR_NDIGIT;
	}

	for (i = 0; buf[i] != '\0'; i++) {
		if (i == slash_index) {
			continue;
		}
		if (!is_digit(buf[i])) {
			if (i == 0 && buf[i] == '-') {
				continue;
			}
			return ERR_NDIGIT;
		}
	}
	/*
	if (slash_index == -1) {
		return SUCCESS;
	}*/

	return SUCCESS;
}

void get_number(int* numerator, int* denominator) {
	char buf[BUFFSIZE];
	/* part_number is a piece of fraction */
	char part_number[BUFFSIZE];
	int numerator_flag = 0;
	int i, part_num_i;
	int check_result;

	printf("Enter your number(-123 or 5/3):\n");
	
	fgets(buf, BUFFSIZE, stdin);
	check_result = check_number(buf);
	// while (check_result != IS_FRAC && check_result != IS_NUMBER) {
	while (check_result != SUCCESS) {
		switch (check_result) {
			case ERR_EMPTY:
				printf("You should enter smth(for example: 456, 9/13):\n");
				break;
			case ERR_NDIGIT:
				printf("Please, enter a number(example: 123, -7/6 (not 7/-6)):\n");
				break;
		}

		fgets(buf, BUFFSIZE, stdin);
		check_result = check_number(buf);
	}

	for (i = part_num_i = 0; buf[i] != '\0'; i++, part_num_i++) {
		/* get numerator */
		if (buf[i] == '/') {
			numerator_flag = 1;

			part_number[part_num_i] = '\0';
			*numerator = atoi(part_number);
			part_num_i = -1;	/* after `continue` it will incremented */
			continue;
		}
		part_number[part_num_i] = buf[i];
	}

	part_number[part_num_i] = '\0';
	if (!numerator_flag) {
		/* if there is no '/' in input, the whole number is stored in numerator */
		*numerator = atoi(part_number);
	} else {
		/* get denominator */
		*denominator = atoi(part_number);
	}
}