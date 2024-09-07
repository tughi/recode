.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %line.ptr: ptr<ptr<Line>> = alloc ptr<Line>
  # %1: u64 = const 16
  # %2: ptr<Line> = call $malloc %1
  movq $0x10, %rdi
  call malloc
  # %3: i32 = const 16
  # %4: i32 = const 32
  # %5: Point = struct { Point.x: %3, Point.y: %4 }
  # %6: i32 = const 48
  # %7: i32 = const 64
  # %8: Point = struct { Point.x: %6, Point.y: %7 }
  # %9: Line = struct { Line.p1: %5, Line.p2: %8 }
  # %10: ptr<Point> = offset %2 Line.p1
  movq %rax, %rcx
  # %11: ptr<i32> = offset %10 Point.x
  lea 0(%rcx), %rdx
  # store %11 %3
  movl $0x10, 0(%rdx)
  # %12: ptr<i32> = offset %10 Point.y
  lea 0(%rcx), %rdx
  # store %12 %4
  movl $0x20, 4(%rdx)
  # %13: ptr<Point> = offset %2 Line.p2
  movq %rax, %rcx
  # %14: ptr<i32> = offset %13 Point.x
  lea 8(%rcx), %rdx
  # store %14 %6
  movl $0x30, 0(%rdx)
  # %15: ptr<i32> = offset %13 Point.y
  lea 8(%rcx), %rdx
  # store %15 %7
  movl $0x40, 4(%rdx)
  # store %line.ptr %2
  movq %rax, 8(%rsp)
  # %16: ptr<Line> = load %line.ptr
  movq 8(%rsp), %rax
  # %17: ptr<Point> = offset %16 Line.p1
  movq %rax, %rcx
  # %18: ptr<i32> = offset %17 Point.x
  lea 0(%rcx), %rax
  # %19: i32 = load %18
  movl 0(%rax), %ecx
  # %20: ptr<Line> = load %line.ptr
  movq 8(%rsp), %rax
  # %21: ptr<Point> = offset %20 Line.p1
  movq %rax, %rdx
  # %22: ptr<i32> = offset %21 Point.y
  lea 0(%rdx), %rax
  # %23: i32 = load %22
  movl 4(%rax), %edx
  # %24: i32 = add %19 %23
  movl %ecx, %eax
  add %edx, %eax
  # %25: ptr<Line> = load %line.ptr
  movq 8(%rsp), %rcx
  # %26: ptr<Point> = offset %25 Line.p2
  movq %rcx, %rdx
  # %27: ptr<i32> = offset %26 Point.x
  lea 8(%rdx), %rcx
  # %28: i32 = load %27
  movl 0(%rcx), %edx
  # %29: i32 = add %24 %28
  movl %eax, %ecx
  add %edx, %ecx
  # %30: ptr<Line> = load %line.ptr
  movq 8(%rsp), %rax
  # %31: ptr<Point> = offset %30 Line.p2
  movq %rax, %rdx
  # %32: ptr<i32> = offset %31 Point.y
  lea 8(%rdx), %rax
  # %33: i32 = load %32
  movl 4(%rax), %edx
  # %34: i32 = add %29 %33
  movl %ecx, %eax
  add %edx, %eax
  # %35: i32 = const 160
  # %36: i32 = sub %34 %35
  movl %eax, %ecx
  sub $0xa0, %ecx
  # ret %36
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
