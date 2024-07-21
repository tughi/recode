.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %point.ptr: ptr<Point> = alloc Point
  # %1: i32 = const 0
  # ret %1
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
