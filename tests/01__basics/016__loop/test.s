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
  sub $0x10, %rsp
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
  movl $0x0, 12(%rsp)
  movl $0x1, 8(%rsp)
  movl $0x2, 4(%rsp)
  jmp .L__fibonacci__4
.L__fibonacci__4:
  movl 12(%rsp), %eax
  movl 8(%rsp), %ecx
  movl %eax, %edx
  add %ecx, %edx
  movl %edx, 0(%rsp)
  movl 8(%rsp), %eax
  movl %eax, 12(%rsp)
  movl 0(%rsp), %eax
  movl %eax, 8(%rsp)
  movl 4(%rsp), %eax
  cmp %edi, %eax
  sete %cl
  cmp $0x0, %cl
  jne .L__fibonacci__6
  jmp .L__fibonacci__7
.L__fibonacci__6:
  jmp .L__fibonacci__5
.L__fibonacci__7:
  movl 4(%rsp), %eax
  movl %eax, %ecx
  add $0x1, %ecx
  movl %ecx, 4(%rsp)
  jmp .L__fibonacci__4
.L__fibonacci__5:
  movl 8(%rsp), %eax
  jmp .L__fibonacci__E
.L__fibonacci__E:
  add $0x10, %rsp
  ret
