
## If you don't have icc installed in your computer
## change the GCC = gcc  and and the -fcilkpuls flag
GCC = /opt/intel/bin/icc
CFLAGS = -O3 -lcilkrts -ldl 

CMAIN=qsort

all: qsort-main.o qsort-cilk.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN).exe -lm

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN).exe
