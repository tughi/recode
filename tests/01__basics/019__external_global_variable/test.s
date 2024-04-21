.extern optind

.globl main
main:
.L__main__S:
.L__main__1:
  movl optind, %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  ret
