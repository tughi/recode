.globl main
main:
.L__main__S:
  sub $0x20, %rsp
.L__main__1:
  lea 16(%rsp), %rax
  lea 0(%rax), %rcx
  movl $0x10, 0(%rcx)
  lea 0(%rax), %rcx
  movl $0x20, 4(%rcx)
  lea 16(%rsp), %rax
  lea 8(%rax), %rcx
  movl $0x30, 0(%rcx)
  lea 8(%rax), %rcx
  movl $0x40, 4(%rcx)
  lea 16(%rsp), %rax
  movq %rax, 8(%rsp)
  movq 8(%rsp), %rax
  movq %rax, %rcx
  lea 8(%rcx), %rax
  movl 4(%rax), %ecx
  movl %ecx, %eax
  sub $0x40, %eax
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  ret
