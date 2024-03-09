.globl main
main:
.L__main__S:
.L__main__1:
  movl $0x0, %edi
  call echo
  jmp .L__main__E
.L__main__E:
  ret


echo:
.L__echo__S:
.L__echo__1:
  movl %edi, %eax
  jmp .L__echo__E
.L__echo__E:
  ret
