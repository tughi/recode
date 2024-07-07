.globl main
main:
.L__main__S:
  sub $0x20, %rsp
.L__main__1:
  movl $0x10, 16(%rsp)
  movl $0x20, 20(%rsp)
  movl $0x30, 24(%rsp)
  movl $0x40, 28(%rsp)
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  ret
