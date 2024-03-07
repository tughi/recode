.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl $0x0, 12(%rsp)
  movl 12(%rsp), %eax
  mov %eax, %ecx
  add $0x1, %ecx
  movl %ecx, 12(%rsp)
  movl 12(%rsp), %eax
  mov %eax, %ecx
  sub $0x1, %ecx
  mov %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
