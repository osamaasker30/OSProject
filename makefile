all: compile run

compile:
	if not exist bin mkdir bin
	if not exist lib mkdir lib
	gcc -c ./src/main.c -o ./lib/main.o
	gcc -c ./src/scheduler.c -o ./lib/scheduler.o
	gcc -c ./src/tasks.c -o ./lib/tasks.o
	gcc ./lib/main.o ./lib/scheduler.o ./lib/tasks.o -o ./bin/freertos_sim

run:
	./bin/freertos_sim giris.txt
