.globl main
main:
.L__main__S:
.L__main__1:
  movl $0x0, %edi
  call echo__number
  jmp .L__main__E
.L__main__E:
  ret


echo__number:
.L__echo__number__S:
  sub $0x10, %rsp
.L__echo__number__1:
  movl %edi, 12(%rsp)
  movl 12(%rsp), %eax
  jmp .L__echo__number__E
.L__echo__number__E:
  add $0x10, %rsp
  ret
