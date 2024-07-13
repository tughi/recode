.globl main
main:
.L__main__S:
.L__main__1:
  cmp $0x1, %edi
  sete %al
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl $0x1, %edi
  call exit
.L__main__3:
  jmp .L__main__E
.L__main__E:
  xor %rax, %rax
  ret
