.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %result.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 2
  # store %result.ptr %1
  movl $0x2, 12(%rsp)
  # %2: bool = const true
  # br %2 @2 @3
  movb $0x1, %al
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %3: i32 = const 0
  # store %result.ptr %3
  movl $0x0, 12(%rsp)
  # jmp @4
  jmp .L__main__4
.L__main__3:
  # %4: i32 = const 1
  # store %result.ptr %4
  movl $0x1, 12(%rsp)
  # jmp @4
  jmp .L__main__4
.L__main__4:
  # %result.1: i32 = load %result.ptr
  movl 12(%rsp), %eax
  # ret %result.1
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
