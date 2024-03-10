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
.L__fibonacci__1:
  cmp $0x1, %edi
  setle %al
  cmp $0x0, %al
  jne .L__fibonacci__2
  jmp .L__fibonacci__3
.L__fibonacci__2:
  movl %edi, %eax
  jmp .L__fibonacci__E
.L__fibonacci__3:
  movl %edi, %eax
  sub $0x1, %eax
  movl %edi, %ebx
  movl %eax, %edi
  call fibonacci
  movl %ebx, %ecx
  sub $0x2, %ecx
  movl %eax, %ebx
  movl %ecx, %edi
  call fibonacci
  movl %ebx, %ecx
  add %eax, %ecx
  movl %ecx, %eax
  jmp .L__fibonacci__E
.L__fibonacci__E:
  popq %rbx
  ret
