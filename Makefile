run: ReCode
	time -p ./ReCode compiler/ReCode.c build/ReCode.c
	cc --std=c90 -Wpedantic -Wno-declaration-after-statement -g -o build/ReCode build/ReCode.c
	build/ReCode compiler/ReCode.c - | diff build/ReCode.c -

trace: ReCode
	gdb ./ReCode -batch -ex='set confirm off' -ex='set style enabled on' -ex='set args compiler/ReCode.c build/ReCode.c' -ex=run -ex=backtrace -ex=quit

ReCode: compiler/ReCode.c
	cc --std=c99 -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-parameter -Wno-builtin-declaration-mismatch -g -o ReCode compiler/ReCode.c

clean:
	rm ReCode
