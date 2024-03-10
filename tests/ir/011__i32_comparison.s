.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movl $0x6, 12(%rsp)
  movl $0x2a, %edi
  call echo
  cmp $0x2a, %eax
  sete %cl
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, 12(%rsp)
  jmp .L__main__3
.L__main__3:
  movl $0x2a, %edi
  call echo
  cmp $0x2a, %eax
  setne %cl
  cmp $0x0, %cl
  jne .L__main__4
  jmp .L__main__5
.L__main__4:
  jmp .L__main__6
.L__main__5:
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, 12(%rsp)
  jmp .L__main__6
.L__main__6:
  movl $0x2a, %edi
  call echo
  cmp $0xd, %eax
  setl %cl
  cmp $0x0, %cl
  jne .L__main__7
  jmp .L__main__8
.L__main__7:
  jmp .L__main__9
.L__main__8:
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, 12(%rsp)
  jmp .L__main__9
.L__main__9:
  movl $0x2a, %edi
  call echo
  cmp $0x2a, %eax
  setle %cl
  cmp $0x0, %cl
  jne .L__main__10
  jmp .L__main__11
.L__main__10:
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, 12(%rsp)
  jmp .L__main__11
.L__main__11:
  movl $0x2a, %edi
  call echo
  cmp $0xd, %eax
  setg %cl
  cmp $0x0, %cl
  jne .L__main__12
  jmp .L__main__13
.L__main__12:
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, 12(%rsp)
  jmp .L__main__13
.L__main__13:
  movl $0x2a, %edi
  call echo
  cmp $0x2a, %eax
  setge %cl
  cmp $0x0, %cl
  jne .L__main__14
  jmp .L__main__15
.L__main__14:
  movl 12(%rsp), %eax
  movl %eax, %ecx
  sub $0x1, %ecx
  movl %ecx, 12(%rsp)
  jmp .L__main__15
.L__main__15:
  movl 12(%rsp), %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret


echo:
.L__echo__S:
.L__echo__1:
  movl %edi, %eax
  jmp .L__echo__E
.L__echo__E:
  ret
