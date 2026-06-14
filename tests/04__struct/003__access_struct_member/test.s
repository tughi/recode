.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %point.ptr: ptr<Point> = alloc Point
  # %1: i32 = const 16
  # %2: i32 = const 32
  # %3: Point = struct { Point.x: %1, Point.y: %2 }
  # %4: ptr<i32> = offset %point.ptr Point.x
  lea 8(%rsp), %rax
  # store %4 %1
  movl $0x10, 0(%rax)
  # %5: ptr<i32> = offset %point.ptr Point.y
  lea 8(%rsp), %rax
  # store %5 %2
  movl $0x20, 4(%rax)
  # %6: ptr<i32> = offset %point.ptr Point.x
  lea 8(%rsp), %rax
  # %7: i32 = load %6
  movl 0(%rax), %ecx
  # %8: i32 = const 16
  # %9: i32 = sub %7 %8
  movl %ecx, %eax
  sub $0x10, %eax
  # ret %9
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
