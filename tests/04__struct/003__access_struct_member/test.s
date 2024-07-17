.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  lea 8(%rsp), %rax
  movl $0x10, 0(%rax)
  lea 8(%rsp), %rax
  movl $0x20, 4(%rax)
  lea 8(%rsp), %rax
  movl 0(%rax), %ecx
  movl %ecx, %eax
  sub $0x10, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
