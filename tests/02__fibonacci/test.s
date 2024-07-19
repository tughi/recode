.globl main
main:
.L__main__S:
.L__main__1:
  movl $0xc, %edi
  call fibonacci__of
  movl %eax, %ecx
  sub $0x90, %ecx
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  ret


fibonacci__of:
.L__fibonacci__of__S:
  pushq %rbx
  sub $0x10, %rsp
.L__fibonacci__of__1:
  movl %edi, 12(%rsp)
  movl 12(%rsp), %eax
  cmp $0x1, %eax
  setle %cl
  cmp $0x0, %cl
  jne .L__fibonacci__of__2
  jmp .L__fibonacci__of__3
.L__fibonacci__of__2:
  movl 12(%rsp), %eax
  jmp .L__fibonacci__of__E
.L__fibonacci__of__3:
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, %edi
  call fibonacci__of
  movl 12(%rsp), %ecx
  movl %ecx, %edx
  sub $0x2, %edx
  movl %eax, %ebx
  movl %edx, %edi
  call fibonacci__of
  movl %ebx, %ecx
  add %eax, %ecx
  movl %ecx, %eax
  jmp .L__fibonacci__of__E
.L__fibonacci__of__E:
  add $0x10, %rsp
  popq %rbx
  ret
