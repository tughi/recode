.globl main
main:
.L__main__S:
.L__main__1:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  ret


f1:
.L__f1__S:
  sub $0x10, %rsp
.L__f1__1:
  movl $0x0, 12(%rsp)
  jmp .L__f1__E
.L__f1__E:
  add $0x10, %rsp
  ret


f2:
.L__f2__S:
  sub $0x10, %rsp
.L__f2__1:
  movl $0x0, 12(%rsp)
  movl $0x0, 8(%rsp)
  movl $0x0, 4(%rsp)
  movl $0x0, 0(%rsp)
  jmp .L__f2__E
.L__f2__E:
  add $0x10, %rsp
  ret


f3:
.L__f3__S:
  sub $0x20, %rsp
.L__f3__1:
  movl $0x0, 28(%rsp)
  movl $0x0, 24(%rsp)
  movl $0x0, 20(%rsp)
  movl $0x0, 16(%rsp)
  movl $0x0, 12(%rsp)
  jmp .L__f3__E
.L__f3__E:
  add $0x20, %rsp
  ret
