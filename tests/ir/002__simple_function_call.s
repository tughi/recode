.globl main
main:
.L__main__S:
.L__main__1:
  call zero
  jmp .L__main__E
.L__main__E:
  ret


zero:
.L__zero__S:
.L__zero__1:
  mov $0, %eax
  jmp .L__zero__E
.L__zero__E:
  ret
