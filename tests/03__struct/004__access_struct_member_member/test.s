.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl $0x10, 0(%rsp)
  movl $0x20, 4(%rsp)
  movl $0x30, 8(%rsp)
  movl $0x40, 12(%rsp)
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x40, %ecx
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
