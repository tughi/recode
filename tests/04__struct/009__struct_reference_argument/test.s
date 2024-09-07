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
  # %6: i32 = call $get_y %point.ptr
  lea 8(%rsp), %rdi
  call get_y
  # %7: i32 = const 32
  # %8: i32 = sub %6 %7
  movl %eax, %ecx
  sub $0x20, %ecx
  # ret %8
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret


get_y:
.L__get_y__S:
  sub $0x10, %rsp
.L__get_y__1:
  # %point.ptr: ptr<ptr<Point>> = alloc ptr<Point>
  # store %point.ptr %point
  movq %rdi, 8(%rsp)
  # %1: ptr<Point> = load %point.ptr
  movq 8(%rsp), %rax
  # %2: ptr<i32> = offset %1 Point.y
  movq %rax, %rcx
  # %3: i32 = load %2
  movl 4(%rcx), %eax
  # ret %3
  jmp .L__get_y__E
.L__get_y__E:
  add $0x10, %rsp
  ret
