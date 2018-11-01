
GCC = gcc
CFLAGS = -Ofast 

CMAIN=qsort

all: qsort-main.o 
	$(GCC) $(CFLAGS) $^ -o $(CMAIN).exe -lm

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN).exe
