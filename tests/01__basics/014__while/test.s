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
  sub $0x20, %rsp
.L__fibonacci__1:
  movl %edi, 28(%rsp)
  movl 28(%rsp), %eax
  cmp $0x1, %eax
  setle %cl
  cmp $0x0, %cl
  jne .L__fibonacci__2
  jmp .L__fibonacci__3
.L__fibonacci__2:
  movl 28(%rsp), %eax
  jmp .L__fibonacci__E
.L__fibonacci__3:
  movl $0x0, 24(%rsp)
  movl $0x1, 20(%rsp)
  movl $0x2, 16(%rsp)
  jmp .L__fibonacci__4
.L__fibonacci__4:
  movl 16(%rsp), %eax
  movl 28(%rsp), %ecx
  cmp %ecx, %eax
  setle %dl
  cmp $0x0, %dl
  jne .L__fibonacci__5
  jmp .L__fibonacci__6
.L__fibonacci__5:
  movl 24(%rsp), %eax
  movl 20(%rsp), %ecx
  movl %eax, %edx
  add %ecx, %edx
  movl %edx, 12(%rsp)
  movl 20(%rsp), %eax
  movl %eax, 24(%rsp)
  movl 12(%rsp), %eax
  movl %eax, 20(%rsp)
  movl 16(%rsp), %eax
  movl %eax, %ecx
  add $0x1, %ecx
  movl %ecx, 16(%rsp)
  jmp .L__fibonacci__4
.L__fibonacci__6:
  movl 20(%rsp), %eax
  jmp .L__fibonacci__E
.L__fibonacci__E:
  add $0x20, %rsp
  ret
