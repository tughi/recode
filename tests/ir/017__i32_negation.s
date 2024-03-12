.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl $0x2a, 12(%rsp)
  movl 12(%rsp), %eax
  movl %eax, %ecx
  movl %ecx, %eax
  movl $0xffffffff, %esi
  mull %esi
  movl 12(%rsp), %ecx
  movl %ecx, %edx
  neg %edx
  cmp %edx, %eax
  setne %cl
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
