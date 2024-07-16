.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl %edi, 12(%rsp)
  movq %rsi, 4(%rsp)
  movl $0x1, 0(%rsp)
  movl 0(%rsp), %eax
  movl %eax, %ecx
  movq 4(%rsp), %rsi
  movslq %ecx, %rax
  cqo
  imulq $0x8, %rax
  add %rax, %rsi
  movl 0(%rsp), %eax
  movl %eax, %ecx
  movq 0(%rsi), %rdi
  movslq %ecx, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  movb 0(%rdi), %al
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
