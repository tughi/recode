.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl %edi, 12(%rsp)
  movq %rsi, 4(%rsp)
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  xor %rax, %rax
  ret
