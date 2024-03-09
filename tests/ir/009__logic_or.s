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
  jne .L__main__6_F_1
  jmp .L__main__5
.L__main__6:
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__6_F_1:
  jmp .L__main__6
.L__main__5:
  movb 14(%rsp), %cl
  jmp .L__main__6_F_5
.L__main__2:
  jmp .L__main__4
.L__main__3:
  movl $0x1, %eax
  jmp .L__main__E
.L__main__4:
  movb 14(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__11_F_4
  jmp .L__main__10
.L__main__11:
  cmp $0x0, %cl
  jne .L__main__7
  jmp .L__main__8
.L__main__11_F_4:
  jmp .L__main__11
.L__main__10:
  movb 15(%rsp), %al
  jmp .L__main__11_F_10
.L__main__7:
  jmp .L__main__9
.L__main__8:
  movl $0x2, %eax
  jmp .L__main__E
.L__main__9:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__16_F_9
  jmp .L__main__15
.L__main__16:
  cmp $0x0, %al
  jne .L__main__12
  jmp .L__main__13
.L__main__16_F_9:
  jmp .L__main__16
.L__main__15:
  movb 15(%rsp), %cl
  jmp .L__main__16_F_15
.L__main__12:
  jmp .L__main__14
.L__main__13:
  movl $0x3, %eax
  jmp .L__main__E
.L__main__14:
  movb 14(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__20_F_14
  jmp .L__main__19
.L__main__20:
  cmp $0x0, %cl
  jne .L__main__17
  jmp .L__main__18
.L__main__20_F_14:
  jmp .L__main__20
.L__main__19:
  movb 14(%rsp), %al
  jmp .L__main__20_F_19
.L__main__17:
  movl $0x4, %eax
  jmp .L__main__E
.L__main__18:
  movb 14(%rsp), %al
  cmp $0x0, %al
  jne .L__main__24_F_18
  jmp .L__main__23
.L__main__24:
  cmp $0x0, %al
  jne .L__main__26_F_24
  jmp .L__main__25
.L__main__24_F_18:
  jmp .L__main__24
.L__main__23:
  movb 14(%rsp), %cl
  jmp .L__main__24_F_23
.L__main__26:
  cmp $0x0, %al
  jne .L__main__21
  jmp .L__main__22
.L__main__26_F_24:
  jmp .L__main__26
.L__main__25:
  movb 14(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__28_F_25
  jmp .L__main__27
.L__main__21:
  movl $0x5, %eax
  jmp .L__main__E
.L__main__22:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__28:
  jmp .L__main__26_F_28
.L__main__28_F_25:
  jmp .L__main__28
.L__main__27:
  movb 14(%rsp), %al
  jmp .L__main__28_F_27
.L__main__26_F_28:
  movb %cl, %al
  jmp .L__main__26
.L__main__28_F_27:
  movb %al, %cl
  jmp .L__main__28
.L__main__24_F_23:
  movb %cl, %al
  jmp .L__main__24
.L__main__20_F_19:
  movb %al, %cl
  jmp .L__main__20
.L__main__16_F_15:
  movb %cl, %al
  jmp .L__main__16
.L__main__11_F_10:
  movb %al, %cl
  jmp .L__main__11
.L__main__6_F_5:
  movb %cl, %al
  jmp .L__main__6
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
