.globl main
main:
.L__main__S:
.L__main__1:
  movb $0x1, %dil
  call test_not
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  movb $0x0, %dil
  call test_not
  cmp $0x0, %al
  jne .L__main__4
  jmp .L__main__5
.L__main__4:
  jmp .L__main__6
.L__main__5:
  movl $0x2, %eax
  jmp .L__main__E
.L__main__6:
  movb $0x0, %dil
  call test_not
  movb %al, %cl
  xor $0x1, %cl
  cmp $0x0, %cl
  jne .L__main__7
  jmp .L__main__8
.L__main__7:
  movl $0x3, %eax
  jmp .L__main__E
.L__main__8:
  movb $0x1, %dil
  call test_not
  movb %al, %cl
  xor $0x1, %cl
  movb %cl, %al
  xor $0x1, %al
  cmp $0x0, %al
  jne .L__main__9
  jmp .L__main__10
.L__main__9:
  movl $0x4, %eax
  jmp .L__main__E
.L__main__10:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  ret


test_not:
.L__test_not__S:
  sub $0x10, %rsp
.L__test_not__1:
  movb %dil, 15(%rsp)
  movb 15(%rsp), %al
  movb %al, %cl
  xor $0x1, %cl
  movb %cl, %al
  jmp .L__test_not__E
.L__test_not__E:
  add $0x10, %rsp
  ret
