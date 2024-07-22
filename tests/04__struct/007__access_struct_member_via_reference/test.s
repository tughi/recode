.globl main
main:
.L__main__S:
  sub $0x20, %rsp
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
  lea 16(%rsp), %rax
  # %9: ptr<i32> = offset %8 Point.x
  lea 0(%rax), %rcx
  # store %9 %1
  movl $0x10, 0(%rcx)
  # %10: ptr<i32> = offset %8 Point.y
  lea 0(%rax), %rcx
  # store %10 %2
  movl $0x20, 4(%rcx)
  # %11: ptr<Point> = offset %line.ptr Line.p2
  lea 16(%rsp), %rax
  # %12: ptr<i32> = offset %11 Point.x
  lea 8(%rax), %rcx
  # store %12 %4
  movl $0x30, 0(%rcx)
  # %13: ptr<i32> = offset %11 Point.y
  lea 8(%rax), %rcx
  # store %13 %5
  movl $0x40, 4(%rcx)
  # %line_reference.ptr: ptr<ptr<Line>> = alloc ptr<Line>
  # store %line_reference.ptr %line.ptr
  lea 16(%rsp), %rax
  movq %rax, 8(%rsp)
  # %14: ptr<Line> = load %line_reference.ptr
  movq 8(%rsp), %rax
  # %15: ptr<Point> = offset %14 Line.p2
  movq %rax, %rcx
  # %16: ptr<i32> = offset %15 Point.y
  lea 8(%rcx), %rax
  # %17: i32 = load %16
  movl 4(%rax), %ecx
  # %18: i32 = const 64
  # %19: i32 = sub %17 %18
  movl %ecx, %eax
  sub $0x40, %eax
  # ret %19
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  ret
