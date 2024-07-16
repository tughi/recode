.globl main
main:
.L__main__S:
  sub $0x20, %rsp
.L__main__1:
  movl %edi, 28(%rsp)
  movq %rsi, 20(%rsp)
  movq 20(%rsp), %rax
  movq (%rax), %rcx
  movq %rcx, 12(%rsp)
  movq 12(%rsp), %rax
  movb (%rax), %cl
  movb %cl, 11(%rsp)
  movb 11(%rsp), %al
  cmp $0x62, %al
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
  add $0x20, %rsp
  ret
