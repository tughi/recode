.globl main
main:
.L__main__S:
.L__main__1:
  call nop
  jmp .L__main__E
.L__main__E:
  xor %rax, %rax
  ret


nop:
.L__nop__S:
.L__nop__1:
  jmp .L__nop__E
.L__nop__E:
  ret
