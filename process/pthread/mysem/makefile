CFLAGS+=-pthread
LDFLAGS+=-pthread


all:mysem

mysem:main.o mysem.o
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS+=-pthread)

clean:
	rm -rf *.o mysem
