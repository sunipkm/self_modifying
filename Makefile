CC = gcc
COBJS = test.o

all: $(COBJS)
	$(CC) $(COBJS) -o test.out
	echo "Execute ./test.out multiple times, every time the value printed will increase by 100"

%.o: %.c
	$(CC) -O2 -o $@ -c $<

.PHONY: clean

clean:
	rm -vf *.o
	rm -vf *.out
