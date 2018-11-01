
GCC = gcc
CFLAGS = -Ofast
CMAIN=qsort

all: qsort-main.o qsort-sequential.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN).exe

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN).exe
