enum CONSTANTS{
	LOWER_LIMIT = 0,
	UPPER_LIMIT = 61,
	BUFFSIZE = 300
};

enum RESULTS {
	SUCCESS,			/* 0 */
	ERR_EMPTY,			/* 1 */
	ERR_OUT_OF_BOUND,	/* 2 */
	ERR_NDIGIT,			/* 3 */
	/* used in "input_handler.c" */
	IS_FRAC,			/* 4 */
	IS_NUMBER			/* 5 */
};

int is_digit(char symbol);
int check_parameter(char buf[]);
int read_input(char* parameter_name);
void get_params(int *exp_n, int *frac_n);
