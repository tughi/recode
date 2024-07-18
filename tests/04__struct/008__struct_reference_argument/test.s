.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  lea 8(%rsp), %rax
  movl $0x10, 0(%rax)
  lea 8(%rsp), %rax
  movl $0x20, 4(%rax)
  lea 8(%rsp), %rdi
  call get_y
  movl %eax, %ecx
  sub $0x20, %ecx
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret


get_y:
.L__get_y__S:
  sub $0x10, %rsp
.L__get_y__1:
  movq %rdi, 8(%rsp)
  movq 8(%rsp), %rax
  movq %rax, %rcx
  movl 4(%rcx), %eax
  jmp .L__get_y__E
.L__get_y__E:
  add $0x10, %rsp
  ret
