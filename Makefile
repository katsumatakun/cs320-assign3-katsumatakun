
all: goodcnt badpc r_and_w roller

goodcnt: goodcnt.c
	gcc -o goodcnt goodcnt.c -pthread

badpc: badpc.c
	gcc -o badpc badpc.c -pthread

r_and_w: r_and_w.c
	gcc -o r_and_w r_and_w.c -pthread

roller: roller.c
	gcc -o roller roller.c -pthread

clean:
	rm -rf goodcnt badpc r_and_w roller
