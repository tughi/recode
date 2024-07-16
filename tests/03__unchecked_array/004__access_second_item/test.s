.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl %edi, 12(%rsp)
  movq %rsi, 4(%rsp)
  movq 4(%rsp), %rcx
  movq 8(%rcx), %rsi
  movb 1(%rsi), %al
  cmp $0x30, %al
  setne %cl
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
