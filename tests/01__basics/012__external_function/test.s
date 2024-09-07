.globl main
main:
.L__main__S:
.L__main__1:
  # %1: i32 = const 0
  # call $exit %1
  movl $0x0, %edi
  call exit
  # %2: i32 = const 1
  # ret %2
  movl $0x1, %eax
  jmp .L__main__E
.L__main__E:
  ret
