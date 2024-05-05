.extern stdout

.globl main
main:
.L__main__S:
.L__main__1:
  movq stdout, %rax
  movb $0x34, %dil
  movq %rax, %rsi
  call fputc
  movq stdout, %rax
  movb $0x32, %dil
  movq %rax, %rsi
  call fputc
  movq stdout, %rax
  movb $0xa, %dil
  movq %rax, %rsi
  call fputc
  jmp .L__main__E
.L__main__E:
  xor %rax, %rax
  ret
