.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl $0x2, 12(%rsp)
  mov $0x1, %al
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl $0x0, 12(%rsp)
  jmp .L__main__4
.L__main__3:
  movl $0x1, 12(%rsp)
  jmp .L__main__4
.L__main__4:
  movl 12(%rsp), %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
