.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %line.ptr: ptr<Line> = alloc Line
  # %1: ptr<Point> = offset %line.ptr Line.p2
  lea 0(%rsp), %rax
  # %2: ptr<i32> = offset %1 Point.y
  lea 8(%rax), %rcx
  # %3: i32 = const 64
  # store %2 %3
  movl $0x40, 4(%rcx)
  # %4: ptr<Point> = offset %line.ptr Line.p2
  lea 0(%rsp), %rax
  # %5: ptr<i32> = offset %4 Point.y
  lea 8(%rax), %rcx
  # %6: i32 = load %5
  movl 4(%rcx), %eax
  # %7: i32 = const 64
  # %8: i32 = sub %6 %7
  movl %eax, %ecx
  sub $0x40, %ecx
  # ret %8
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
