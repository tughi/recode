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
  # br %5 @2 @3
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__5_F_1:
  jmp .L__main__5
.L__main__5_F_4:
  movb %cl, %al
  jmp .L__main__5
.L__main__2:
  # %6: i32 = const 1
  # ret %6
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %f.2: bool = load %f.ptr
  movb 14(%rsp), %al
  # br %f.2 @8 @9
  cmp $0x0, %al
  jne .L__main__8
  jmp .L__main__9_F_3
.L__main__8:
  # %t.2: bool = load %t.ptr
  movb 15(%rsp), %cl
  # jmp @9
  jmp .L__main__9_F_8
.L__main__9:
  # %7: bool = phi @3 %f.2 @8 %t.2
  # br %7 @6 @7
  cmp $0x0, %al
  jne .L__main__6
  jmp .L__main__7
.L__main__9_F_3:
  jmp .L__main__9
.L__main__9_F_8:
  movb %cl, %al
  jmp .L__main__9
.L__main__6:
  # %8: i32 = const 2
  # ret %8
  movl $0x2, %eax
  jmp .L__main__E
.L__main__7:
  # %t.3: bool = load %t.ptr
  movb 15(%rsp), %al
  # br %t.3 @13 @14
  cmp $0x0, %al
  jne .L__main__13
  jmp .L__main__14_F_7
.L__main__13:
  # %t.4: bool = load %t.ptr
  movb 15(%rsp), %cl
  # jmp @14
  jmp .L__main__14_F_13
.L__main__14:
  # %9: bool = phi @7 %t.3 @13 %t.4
  # br %9 @10 @11
  cmp $0x0, %al
  jne .L__main__10
  jmp .L__main__11
.L__main__14_F_7:
  jmp .L__main__14
.L__main__14_F_13:
  movb %cl, %al
  jmp .L__main__14
.L__main__10:
  # jmp @12
  jmp .L__main__12
.L__main__11:
  # %10: i32 = const 3
  # ret %10
  movl $0x3, %eax
  jmp .L__main__E
.L__main__12:
  # %f.3: bool = load %f.ptr
  movb 14(%rsp), %al
  # br %f.3 @17 @18
  cmp $0x0, %al
  jne .L__main__17
  jmp .L__main__18_F_12
.L__main__17:
  # %f.4: bool = load %f.ptr
  movb 14(%rsp), %cl
  # jmp @18
  jmp .L__main__18_F_17
.L__main__18:
  # %11: bool = phi @12 %f.3 @17 %f.4
  # br %11 @15 @16
  cmp $0x0, %al
  jne .L__main__15
  jmp .L__main__16
.L__main__18_F_12:
  jmp .L__main__18
.L__main__18_F_17:
  movb %cl, %al
  jmp .L__main__18
.L__main__15:
  # %12: i32 = const 4
  # ret %12
  movl $0x4, %eax
  jmp .L__main__E
.L__main__16:
  # %t.5: bool = load %t.ptr
  movb 15(%rsp), %al
  # br %t.5 @21 @22
  cmp $0x0, %al
  jne .L__main__21
  jmp .L__main__22_F_16
.L__main__21:
  # %t.6: bool = load %t.ptr
  movb 15(%rsp), %cl
  # jmp @22
  jmp .L__main__22_F_21
.L__main__22:
  # %13: bool = phi @16 %t.5 @21 %t.6
  # br %13 @23 @24
  cmp $0x0, %al
  jne .L__main__23
  jmp .L__main__24_F_22
.L__main__22_F_16:
  jmp .L__main__22
.L__main__22_F_21:
  movb %cl, %al
  jmp .L__main__22
.L__main__23:
  # %f.5: bool = load %f.ptr
  movb 14(%rsp), %cl
  # br %f.5 @25 @26
  cmp $0x0, %cl
  jne .L__main__25
  jmp .L__main__26_F_23
.L__main__24:
  # %15: bool = phi @22 %13 @26 %14
  # br %15 @19 @20
  cmp $0x0, %al
  jne .L__main__19
  jmp .L__main__20
.L__main__24_F_22:
  jmp .L__main__24
.L__main__25:
  # %f.6: bool = load %f.ptr
  movb 14(%rsp), %al
  # jmp @26
  jmp .L__main__26_F_25
.L__main__26:
  # %14: bool = phi @23 %f.5 @25 %f.6
  # jmp @24
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
  # %16: i32 = const 5
  # ret %16
  movl $0x5, %eax
  jmp .L__main__E
.L__main__20:
  # %17: i32 = const 0
  # ret %17
  movl $0x0, %eax
  jmp .L__main__E
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
