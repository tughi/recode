.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  lea 0(%rsp), %rax
  lea 8(%rax), %rcx
  movl $0x40, 4(%rcx)
  lea 0(%rsp), %rax
  lea 8(%rax), %rcx
  movl 4(%rcx), %eax
  movl %eax, %ecx
  sub $0x40, %ecx
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
