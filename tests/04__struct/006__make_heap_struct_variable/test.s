.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movq $0x10, %rdi
  call malloc
  movq %rax, %rcx
  lea 0(%rcx), %rdx
  movl $0x10, 0(%rdx)
  lea 0(%rcx), %rdx
  movl $0x20, 4(%rdx)
  movq %rax, %rcx
  lea 8(%rcx), %rdx
  movl $0x30, 0(%rdx)
  lea 8(%rcx), %rdx
  movl $0x40, 4(%rdx)
  movq %rax, 8(%rsp)
  movq 8(%rsp), %rax
  movq %rax, %rcx
  lea 0(%rcx), %rax
  movl 0(%rax), %ecx
  movq 8(%rsp), %rax
  movq %rax, %rdx
  lea 0(%rdx), %rax
  movl 4(%rax), %edx
  movl %ecx, %eax
  add %edx, %eax
  movq 8(%rsp), %rcx
  movq %rcx, %rdx
  lea 8(%rdx), %rcx
  movl 0(%rcx), %edx
  movl %eax, %ecx
  add %edx, %ecx
  movq 8(%rsp), %rax
  movq %rax, %rdx
  lea 8(%rdx), %rax
  movl 4(%rax), %edx
  movl %ecx, %eax
  add %edx, %eax
  movl %eax, %ecx
  sub $0xa0, %ecx
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
