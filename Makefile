
all: goodcnt badpc

goodcnt: goodcnt.c
	gcc -o goodcnt goodcnt.c -pthread

badpc: badpc.c
	gcc -o badpc badpc.c -pthread

clean:
	rm -rf goodcnt badpc
