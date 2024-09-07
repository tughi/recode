.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %t.ptr: ptr<bool> = alloc bool
  # %1: bool = const true
  # %2: bool = call $echo %1
  movb $0x1, %dil
  call echo
  # store %t.ptr %2
  movb %al, 15(%rsp)
  # %f.ptr: ptr<bool> = alloc bool
  # %3: bool = const false
  # %4: bool = call $echo %3
  movb $0x0, %dil
  call echo
  # store %f.ptr %4
  movb %al, 14(%rsp)
  # %t.1: bool = load %t.ptr
  movb 15(%rsp), %al
  # br %t.1 @4 @5
  cmp $0x0, %al
  jne .L__main__4
  jmp .L__main__5_F_1
.L__main__4:
  # %f.1: bool = load %f.ptr
  movb 14(%rsp), %cl
  # jmp @5
  jmp .L__main__5_F_4
.L__main__5:
  # %5: bool = phi @1 %t.1 @4 %f.1
  # br %5 @7 @6
  cmp $0x0, %al
  jne .L__main__7_F_5
  jmp .L__main__6
.L__main__5_F_1:
  jmp .L__main__5
.L__main__5_F_4:
  movb %cl, %al
  jmp .L__main__5
.L__main__7:
  # %7: bool = phi @5 %5 @9 %6
  # br %7 @11 @10
  cmp $0x0, %al
  jne .L__main__11_F_7
  jmp .L__main__10
.L__main__7_F_5:
  jmp .L__main__7
.L__main__6:
  # %f.2: bool = load %f.ptr
  movb 14(%rsp), %cl
  # br %f.2 @8 @9
  cmp $0x0, %cl
  jne .L__main__8
  jmp .L__main__9_F_6
.L__main__11:
  # %12: bool = phi @7 %7 @15 %11
  # br %12 @2 @3
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__11_F_7:
  jmp .L__main__11
.L__main__10:
  # %t.3: bool = load %t.ptr
  movb 15(%rsp), %cl
  # br %t.3 @13 @12
  cmp $0x0, %cl
  jne .L__main__13_F_10
  jmp .L__main__12
.L__main__2:
  # %13: i32 = const 1
  # ret %13
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %14: i32 = const 0
  # ret %14
  movl $0x0, %eax
  jmp .L__main__E
.L__main__13:
  # %8: bool = phi @10 %t.3 @12 %f.3
  # br %8 @14 @15
  cmp $0x0, %cl
  jne .L__main__14
  jmp .L__main__15_F_13
.L__main__13_F_10:
  jmp .L__main__13
.L__main__12:
  # %f.3: bool = load %f.ptr
  movb 14(%rsp), %al
  # jmp @13
  jmp .L__main__13_F_12
.L__main__14:
  # %f.4: bool = load %f.ptr
  movb 14(%rsp), %al
  # br %f.4 @17 @16
  cmp $0x0, %al
  jne .L__main__17_F_14
  jmp .L__main__16
.L__main__15:
  # %10: bool = phi @13 %8 @17 %9
  # %11: bool = not %10
  movb %cl, %al
  xor $0x1, %al
  # jmp @11
  jmp .L__main__11_F_15
.L__main__15_F_13:
  jmp .L__main__15
.L__main__17:
  # %9: bool = phi @14 %f.4 @16 %t.4
  # jmp @15
  jmp .L__main__15_F_17
.L__main__17_F_14:
  jmp .L__main__17
.L__main__16:
  # %t.4: bool = load %t.ptr
  movb 15(%rsp), %cl
  # jmp @17
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
  # %t.2: bool = load %t.ptr
  movb 15(%rsp), %al
  # jmp @9
  jmp .L__main__9_F_8
.L__main__9:
  # %6: bool = phi @6 %f.2 @8 %t.2
  # jmp @7
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
  # %v.ptr: ptr<bool> = alloc bool
  # store %v.ptr %v
  movb %dil, 15(%rsp)
  # %v.1: bool = load %v.ptr
  movb 15(%rsp), %al
  # ret %v.1
  jmp .L__echo__E
.L__echo__E:
  add $0x10, %rsp
  ret
