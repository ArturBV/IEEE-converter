FLAGS=-Wall -g
FILES_PATH=files
ALL_OBJ_FILES=main.o input_handler.o

all: IEEE-calculator

IEEE-calculator: $(ALL_OBJ_FILES)
	@gcc $(FLAGS) $(ALL_OBJ_FILES) -o IEEE-calculator

main.o:# main.c
	@gcc $(FLAGS) -c main.c -o main.o

input_handler.o:# input_handler.c
	@gcc $(FLAGS) -c $(FILES_PATH)/input_handler.c -o input_handler.o

run: clean IEEE-calculator
	@./IEEE-calculator

clean:
	@rm -f $(ALL_OBJ_FILES)
