enum CONSTANTS{
	LOWER_LIMIT = 0,
	UPPER_LIMIT = 31,
	BUFFSIZE = 300
};

enum RESULTS {
	SUCCESS,	/* 0 */
	ERR_EMPTY,	/* 1 */
	ERR_OUT_OF_BOUND,	/* 2 */
	ERR_NDIGIT,	/* 3 */
};

int is_digit(char);
int check_parameter(char *);
int read_input(char *);
void get_params(int *, int *);
