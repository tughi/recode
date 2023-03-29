run: ReCode
	./ReCode < compiler/ReCode.c

trace: ReCode
	gdb -batch -ex='set confirm off' -ex='set style enabled on' -ex='run ./ReCode < compiler/ReCode.c' -ex=bt -ex=quit --args ReCode

ReCode: compiler/ReCode.c
	cc --std=c99 -Wall -Wextra -g -o ReCode compiler/ReCode.c

clean:
	rm ReCode
