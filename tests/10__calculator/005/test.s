.extern stdin

.extern stdout

.extern stderr

.globl main
main:
.L__main__S:
  sub $0x20, %rsp
.L__main__1:
  movl %edi, 28(%rsp)
  movq %rsi, 20(%rsp)
  movl $0x1, 16(%rsp)
  jmp .L__main__2
.L__main__2:
  movl 16(%rsp), %eax
  movl %eax, %ecx
  movq 20(%rsp), %rsi
  movslq %ecx, %rax
  cqo
  imulq $0x8, %rax
  add %rax, %rsi
  movq 0(%rsi), %rax
  movq %rax, 8(%rsp)
  movl $0x0, 4(%rsp)
  jmp .L__main__4
.L__main__4:
  movl 4(%rsp), %eax
  movl %eax, %ecx
  movq 8(%rsp), %rsi
  movslq %ecx, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rsi
  movb 0(%rsi), %al
  cmp $0x0, %al
  sete %cl
  cmp $0x0, %cl
  jne .L__main__6
  jmp .L__main__7
.L__main__6:
  jmp .L__main__5
.L__main__7:
  movl 4(%rsp), %eax
  movl %eax, %ecx
  movq 8(%rsp), %rsi
  movslq %ecx, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rsi
  movb 0(%rsi), %al
  movq stdout, %rcx
  movb %al, %dil
  movq %rcx, %rsi
  call fputc
  movl 4(%rsp), %eax
  movl %eax, %ecx
  add $0x1, %ecx
  movl %ecx, 4(%rsp)
  jmp .L__main__4
.L__main__5:
  movl 16(%rsp), %eax
  movl 28(%rsp), %ecx
  movl %ecx, %edx
  sub $0x1, %edx
  cmp %edx, %eax
  sete %cl
  cmp $0x0, %cl
  jne .L__main__9
  jmp .L__main__10
.L__main__9:
  jmp .L__main__3
.L__main__10:
  movq stdout, %rax
  movb $0x20, %dil
  movq %rax, %rsi
  call fputc
  movl 16(%rsp), %eax
  movl %eax, %ecx
  add $0x1, %ecx
  movl %ecx, 16(%rsp)
  jmp .L__main__2
.L__main__3:
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  xor %rax, %rax
  ret
