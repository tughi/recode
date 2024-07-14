.globl main
main:
.L__main__S:
.L__main__1:
  movl $0xc, %edi
  call fibonacci
  movl %eax, %ecx
  sub $0x90, %ecx
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  ret


fibonacci:
.L__fibonacci__S:
  pushq %rbx
  sub $0x10, %rsp
.L__fibonacci__1:
  movl %edi, 12(%rsp)
  movl 12(%rsp), %eax
  cmp $0x1, %eax
  setle %cl
  cmp $0x0, %cl
  jne .L__fibonacci__2
  jmp .L__fibonacci__3
.L__fibonacci__2:
  movl 12(%rsp), %eax
  jmp .L__fibonacci__E
.L__fibonacci__3:
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, %edi
  call fibonacci
  movl 12(%rsp), %ecx
  movl %ecx, %edx
  sub $0x2, %edx
  movl %eax, %ebx
  movl %edx, %edi
  call fibonacci
  movl %ebx, %ecx
  add %eax, %ecx
  movl %ecx, %eax
  jmp .L__fibonacci__E
.L__fibonacci__E:
  add $0x10, %rsp
  popq %rbx
  ret
