.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  lea 0(%rsp), %rax
  lea 0(%rax), %rcx
  movl $0x10, 0(%rcx)
  lea 0(%rax), %rcx
  movl $0x20, 4(%rcx)
  lea 0(%rsp), %rax
  lea 8(%rax), %rcx
  movl $0x30, 0(%rcx)
  lea 8(%rax), %rcx
  movl $0x40, 4(%rcx)
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
