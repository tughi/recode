.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movb $0x1, %dil
  call echo
  movb %al, 15(%rsp)
  movb $0x0, %dil
  call echo
  movb %al, 14(%rsp)
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__4
  jmp .L__main__5_F_1
.L__main__4:
  movb 14(%rsp), %cl
  jmp .L__main__5_F_4
.L__main__5:
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__5_F_1:
  jmp .L__main__5
.L__main__5_F_4:
  movb %cl, %al
  jmp .L__main__5
.L__main__2:
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  movb 14(%rsp), %al
  cmp $0x0, %al
  jne .L__main__8
  jmp .L__main__9_F_3
.L__main__8:
  movb 15(%rsp), %cl
  jmp .L__main__9_F_8
.L__main__9:
  cmp $0x0, %al
  jne .L__main__6
  jmp .L__main__7
.L__main__9_F_3:
  jmp .L__main__9
.L__main__9_F_8:
  movb %cl, %al
  jmp .L__main__9
.L__main__6:
  movl $0x2, %eax
  jmp .L__main__E
.L__main__7:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__13
  jmp .L__main__14_F_7
.L__main__13:
  movb 15(%rsp), %cl
  jmp .L__main__14_F_13
.L__main__14:
  cmp $0x0, %al
  jne .L__main__10
  jmp .L__main__11
.L__main__14_F_7:
  jmp .L__main__14
.L__main__14_F_13:
  movb %cl, %al
  jmp .L__main__14
.L__main__10:
  jmp .L__main__12
.L__main__11:
  movl $0x3, %eax
  jmp .L__main__E
.L__main__12:
  movb 14(%rsp), %al
  cmp $0x0, %al
  jne .L__main__17
  jmp .L__main__18_F_12
.L__main__17:
  movb 14(%rsp), %cl
  jmp .L__main__18_F_17
.L__main__18:
  cmp $0x0, %al
  jne .L__main__15
  jmp .L__main__16
.L__main__18_F_12:
  jmp .L__main__18
.L__main__18_F_17:
  movb %cl, %al
  jmp .L__main__18
.L__main__15:
  movl $0x4, %eax
  jmp .L__main__E
.L__main__16:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__21
  jmp .L__main__22_F_16
.L__main__21:
  movb 15(%rsp), %cl
  jmp .L__main__22_F_21
.L__main__22:
  cmp $0x0, %al
  jne .L__main__23
  jmp .L__main__24_F_22
.L__main__22_F_16:
  jmp .L__main__22
.L__main__22_F_21:
  movb %cl, %al
  jmp .L__main__22
.L__main__23:
  movb 14(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__25
  jmp .L__main__26_F_23
.L__main__24:
  cmp $0x0, %al
  jne .L__main__19
  jmp .L__main__20
.L__main__24_F_22:
  jmp .L__main__24
.L__main__25:
  movb 14(%rsp), %al
  jmp .L__main__26_F_25
.L__main__26:
  jmp .L__main__24_F_26
.L__main__26_F_23:
  jmp .L__main__26
.L__main__26_F_25:
  movb %al, %cl
  jmp .L__main__26
.L__main__24_F_26:
  movb %cl, %al
  jmp .L__main__24
.L__main__19:
  movl $0x5, %eax
  jmp .L__main__E
.L__main__20:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret


echo:
.L__echo__S:
.L__echo__1:
  movb %dil, %al
  jmp .L__echo__E
.L__echo__E:
  ret
