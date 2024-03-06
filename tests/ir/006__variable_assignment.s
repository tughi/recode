.globl main
main:
.L__main__S:
  sub $4, %rsp
.L__main__1:
  movl $0, 0(%rsp)
  movl 0(%rsp), %eax
  mov %eax, %ecx
  add $1, %ecx
  movl %ecx, 0(%rsp)
  movl 0(%rsp), %eax
  mov %eax, %ecx
  sub $1, %ecx
  mov %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $4, %rsp
  ret
