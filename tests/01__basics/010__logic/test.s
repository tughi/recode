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
  jne .L__main__7_F_5
  jmp .L__main__6
.L__main__5_F_1:
  jmp .L__main__5
.L__main__5_F_4:
  movb %cl, %al
  jmp .L__main__5
.L__main__7:
  cmp $0x0, %al
  jne .L__main__11_F_7
  jmp .L__main__10
.L__main__7_F_5:
  jmp .L__main__7
.L__main__6:
  movb 14(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__8
  jmp .L__main__9_F_6
.L__main__11:
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__11_F_7:
  jmp .L__main__11
.L__main__10:
  movb 15(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__13_F_10
  jmp .L__main__12
.L__main__2:
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__13:
  cmp $0x0, %cl
  jne .L__main__14
  jmp .L__main__15_F_13
.L__main__13_F_10:
  jmp .L__main__13
.L__main__12:
  movb 14(%rsp), %al
  jmp .L__main__13_F_12
.L__main__14:
  movb 14(%rsp), %al
  cmp $0x0, %al
  jne .L__main__17_F_14
  jmp .L__main__16
.L__main__15:
  movb %cl, %al
  xor $0x1, %al
  jmp .L__main__11_F_15
.L__main__15_F_13:
  jmp .L__main__15
.L__main__17:
  jmp .L__main__15_F_17
.L__main__17_F_14:
  jmp .L__main__17
.L__main__16:
  movb 15(%rsp), %cl
  jmp .L__main__17_F_16
.L__main__15_F_17:
  movb %al, %cl
  jmp .L__main__15
.L__main__11_F_15:
  jmp .L__main__11
.L__main__17_F_16:
  movb %cl, %al
  jmp .L__main__17
.L__main__13_F_12:
  movb %al, %cl
  jmp .L__main__13
.L__main__8:
  movb 15(%rsp), %al
  jmp .L__main__9_F_8
.L__main__9:
  jmp .L__main__7_F_9
.L__main__9_F_6:
  jmp .L__main__9
.L__main__9_F_8:
  movb %al, %cl
  jmp .L__main__9
.L__main__7_F_9:
  movb %cl, %al
  jmp .L__main__7
.L__main__E:
  add $0x10, %rsp
  ret


echo:
.L__echo__S:
  sub $0x10, %rsp
.L__echo__1:
  movb %dil, 15(%rsp)
  movb 15(%rsp), %al
  jmp .L__echo__E
.L__echo__E:
  add $0x10, %rsp
  ret
