
GCC = gcc
CFLAGS = -Ofast -pthread 

CMAIN=qsort

all: qsort-main.o qsort-pthread.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN).exe -lm

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN).exe
