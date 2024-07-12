.globl main
main:
.L__main__S:
.L__main__1:
  movl $0x0, %edi
  call exit
  movl $0x1, %eax
  jmp .L__main__E
.L__main__E:
  ret
