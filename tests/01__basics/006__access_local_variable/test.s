.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %result.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 42
  # store %result.ptr %1
  movl $0x2a, 12(%rsp)
  # %result.1: i32 = load %result.ptr
  movl 12(%rsp), %eax
  # %2: i32 = const 42
  # %3: i32 = sub %result.1 %2
  movl %eax, %ecx
  sub $0x2a, %ecx
  # ret %3
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
