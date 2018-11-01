
GCC = gcc
CFLAGS = -Ofast -fopenmp

CMAIN = qsort

all: qsort-main.o qsort-openmp.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN).exe -lm

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN).exe
