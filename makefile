SHELL = /bin/bash
CC = gcc
CFLAGS = -Wl,-z lazy
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE} 

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

clean:
	rm ${EXE} 

run:
	time ./fileperf ./input.txt ./output.txt 0
	time ./fileperf ./input.txt ./output.txt -1
	time ./fileperf ./input.txt ./output.txt 4096
	time ./fileperf ./input.txt ./output.txt 16384
	time ./fileperf ./input.txt ./output.txt 65536
	time ./fileperf ./input.txt ./output.txt 1048576
	time ./fileperf ./input.txt ./output.txt 8388608

