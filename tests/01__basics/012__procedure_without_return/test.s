.globl main
main:
.L__main__S:
.L__main__1:
  # call $finish
  call finish
  # %1: i32 = const 1
  # ret %1
  movl $0x1, %eax
  jmp .L__main__E
.L__main__E:
  ret


finish:
.L__finish__S:
.L__finish__1:
  # call $nothing
  call nothing
  # %1: i32 = const 0
  # call $exit %1
  movl $0x0, %edi
  call exit
.L__finish__E:
  ret


nothing:
.L__nothing__S:
.L__nothing__1:
  # ret
  jmp .L__nothing__E
.L__nothing__E:
  ret
