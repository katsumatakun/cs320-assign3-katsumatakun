
all: goodcnt

goodcnt: goodcnt.c
	gcc -o goodcnt goodcnt.c -pthread

badpc: badpc.c
	gcc -o badpc badpc.c -thread

clean:
	rm -rf cnt badpc
