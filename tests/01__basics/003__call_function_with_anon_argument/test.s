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
  sub $0x10, %rsp
.L__echo__1:
  movl %edi, 12(%rsp)
  movl 12(%rsp), %eax
  jmp .L__echo__E
.L__echo__E:
  add $0x10, %rsp
  ret
