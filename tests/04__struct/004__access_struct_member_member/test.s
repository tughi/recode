.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %line.ptr: ptr<Line> = alloc Line
  # %1: i32 = const 16
  # %2: i32 = const 32
  # %3: Point = struct { Point.x: %1, Point.y: %2 }
  # %4: i32 = const 48
  # %5: i32 = const 64
  # %6: Point = struct { Point.x: %4, Point.y: %5 }
  # %7: Line = struct { Line.p1: %3, Line.p2: %6 }
  # %8: ptr<Point> = offset %line.ptr Line.p1
  lea 0(%rsp), %rax
  # %9: ptr<i32> = offset %8 Point.x
  lea 0(%rax), %rcx
  # store %9 %1
  movl $0x10, 0(%rcx)
  # %10: ptr<i32> = offset %8 Point.y
  lea 0(%rax), %rcx
  # store %10 %2
  movl $0x20, 4(%rcx)
  # %11: ptr<Point> = offset %line.ptr Line.p2
  lea 0(%rsp), %rax
  # %12: ptr<i32> = offset %11 Point.x
  lea 8(%rax), %rcx
  # store %12 %4
  movl $0x30, 0(%rcx)
  # %13: ptr<i32> = offset %11 Point.y
  lea 8(%rax), %rcx
  # store %13 %5
  movl $0x40, 4(%rcx)
  # %14: ptr<Point> = offset %line.ptr Line.p2
  lea 0(%rsp), %rax
  # %15: ptr<i32> = offset %14 Point.y
  lea 8(%rax), %rcx
  # %16: i32 = load %15
  movl 4(%rcx), %eax
  # %17: i32 = const 64
  # %18: i32 = sub %16 %17
  movl %eax, %ecx
  sub $0x40, %ecx
  # ret %18
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
