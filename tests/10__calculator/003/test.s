.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl %edi, 12(%rsp)
  movq %rsi, 4(%rsp)
  movl 12(%rsp), %eax
  cmp $0x1, %eax
  sete %cl
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl $0x1, %edi
  call exit
.L__main__3:
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  xor %rax, %rax
  ret
