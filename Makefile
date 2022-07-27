FLAGS=-Wall -g
FILES_PATH=files
ALL_OBJ_FILES=main.o parameter_handler.o input_handler.o

all: IEEE-calculator

IEEE-calculator: $(ALL_OBJ_FILES)
	gcc $(FLAGS) $(ALL_OBJ_FILES) -o IEEE-calculator -lm

main.o:# main.c
	gcc $(FLAGS) -c main.c -o main.o

parameter_handler.o:# parameter_handler.c
	gcc $(FLAGS) -c $(FILES_PATH)/parameter_handler.c -o parameter_handler.o

input_handler.o:# input_handler.c
	gcc $(FLAGS) -c $(FILES_PATH)/input_handler.c -o input_handler.o

run: IEEE-calculator
	./IEEE-calculator

clean:
	rm -f $(ALL_OBJ_FILES)
