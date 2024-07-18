.extern stdin

.extern stdout

.extern stderr

.globl main
main:
.L__main__S:
  sub $0x30, %rsp
.L__main__1:
  movl %edi, 44(%rsp)
  movq %rsi, 36(%rsp)
  movl 44(%rsp), %eax
  cmp $0x2, %eax
  setne %cl
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl $0x1, %edi
  call exit
.L__main__3:
  movq 36(%rsp), %rcx
  movq 8(%rcx), %rax
  lea 24(%rsp), %rcx
  movq %rax, 0(%rcx)
  lea 24(%rsp), %rax
  movl $0x0, 8(%rax)
  lea 24(%rsp), %rax
  movq %rax, 16(%rsp)
  jmp .L__main__4
.L__main__4:
  lea 24(%rsp), %rdi
  call has_next_token
  cmp $0x0, %al
  jne .L__main__5
  jmp .L__main__6
.L__main__5:
  lea 24(%rsp), %rdi
  call next_token
  movq %rax, 8(%rsp)
  movq 8(%rsp), %rax
  movq %rax, %rcx
  movl 0(%rcx), %eax
  cmp $0x0, %eax
  sete %cl
  cmp $0x0, %cl
  jne .L__main__7
  jmp .L__main__8
.L__main__6:
  jmp .L__main__E
.L__main__7:
  jmp .L__main__6
.L__main__8:
  movq 8(%rsp), %rax
  movq %rax, %rcx
  movb 4(%rcx), %al
  movq stdout, %rcx
  movb %al, %dil
  movq %rcx, %rsi
  call fputc
  jmp .L__main__4
.L__main__E:
  add $0x30, %rsp
  xor %rax, %rax
  ret


has_next_token:
.L__has_next_token__S:
  sub $0x10, %rsp
.L__has_next_token__1:
  movq %rdi, 8(%rsp)
  movq 8(%rsp), %rax
  movq %rax, %rcx
  movq 8(%rsp), %rax
  movq %rax, %rdx
  movl 8(%rdx), %eax
  movl %eax, %edx
  movl %edx, %esi
  movq 0(%rcx), %rdi
  movslq %esi, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  movb 0(%rdi), %al
  cmp $0x0, %al
  setne %cl
  movb %cl, %al
  jmp .L__has_next_token__E
.L__has_next_token__E:
  add $0x10, %rsp
  ret


next_token:
.L__next_token__S:
  sub $0x10, %rsp
.L__next_token__1:
  movq %rdi, 8(%rsp)
  movq 8(%rsp), %rax
  movq %rax, %rcx
  movq 8(%rsp), %rax
  movq %rax, %rdx
  movl 8(%rdx), %eax
  movl %eax, %edx
  movl %edx, %esi
  movq 0(%rcx), %rdi
  movslq %esi, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  movb 0(%rdi), %al
  movb %al, 7(%rsp)
  movq 8(%rsp), %rax
  movq %rax, %rcx
  movq 8(%rsp), %rax
  movq %rax, %rdx
  movl 8(%rdx), %eax
  movl %eax, %edx
  add $0x1, %edx
  movl %edx, 8(%rcx)
  movq $0x5, %rdi
  call malloc
  movb 7(%rsp), %cl
  movq %rax, %rdx
  movl $0x1, 0(%rdx)
  movq %rax, %rdx
  movb %cl, 4(%rdx)
  jmp .L__next_token__E
.L__next_token__E:
  add $0x10, %rsp
  ret
