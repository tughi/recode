run: ReCode
	./ReCode < compiler/ReCode.c > build/ReCode.c
	cc --std=c99 -Wpedantic -g -o build/ReCode build/ReCode.c
	build/ReCode < compiler/ReCode.c | diff build/ReCode.c -

trace: ReCode
	gdb -batch -ex='set confirm off' -ex='set style enabled on' -ex='run ./ReCode < compiler/ReCode.c' -ex=bt -ex=quit --args ReCode

ReCode: compiler/ReCode.c
	cc --std=c99 -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-parameter -Wno-builtin-declaration-mismatch -g -o ReCode compiler/ReCode.c

clean:
	rm ReCode
