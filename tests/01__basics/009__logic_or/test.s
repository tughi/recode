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
  # br %t.1 @6 @5
  cmp $0x0, %al
  jne .L__main__6_F_1
  jmp .L__main__5
.L__main__6:
  # %5: bool = phi @1 %t.1 @5 %f.1
  # br %5 @2 @3
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__6_F_1:
  jmp .L__main__6
.L__main__5:
  # %f.1: bool = load %f.ptr
  movb 14(%rsp), %cl
  # jmp @6
  jmp .L__main__6_F_5
.L__main__2:
  # jmp @4
  jmp .L__main__4
.L__main__3:
  # %6: i32 = const 1
  # ret %6
  movl $0x1, %eax
  jmp .L__main__E
.L__main__4:
  # %f.2: bool = load %f.ptr
  movb 14(%rsp), %al
  # br %f.2 @11 @10
  cmp $0x0, %al
  jne .L__main__11_F_4
  jmp .L__main__10
.L__main__11:
  # %7: bool = phi @4 %f.2 @10 %t.2
  # br %7 @7 @8
  cmp $0x0, %al
  jne .L__main__7
  jmp .L__main__8
.L__main__11_F_4:
  jmp .L__main__11
.L__main__10:
  # %t.2: bool = load %t.ptr
  movb 15(%rsp), %cl
  # jmp @11
  jmp .L__main__11_F_10
.L__main__7:
  # jmp @9
  jmp .L__main__9
.L__main__8:
  # %8: i32 = const 2
  # ret %8
  movl $0x2, %eax
  jmp .L__main__E
.L__main__9:
  # %t.3: bool = load %t.ptr
  movb 15(%rsp), %al
  # br %t.3 @16 @15
  cmp $0x0, %al
  jne .L__main__16_F_9
  jmp .L__main__15
.L__main__16:
  # %9: bool = phi @9 %t.3 @15 %t.4
  # br %9 @12 @13
  cmp $0x0, %al
  jne .L__main__12
  jmp .L__main__13
.L__main__16_F_9:
  jmp .L__main__16
.L__main__15:
  # %t.4: bool = load %t.ptr
  movb 15(%rsp), %cl
  # jmp @16
  jmp .L__main__16_F_15
.L__main__12:
  # jmp @14
  jmp .L__main__14
.L__main__13:
  # %10: i32 = const 3
  # ret %10
  movl $0x3, %eax
  jmp .L__main__E
.L__main__14:
  # %f.3: bool = load %f.ptr
  movb 14(%rsp), %al
  # br %f.3 @20 @19
  cmp $0x0, %al
  jne .L__main__20_F_14
  jmp .L__main__19
.L__main__20:
  # %11: bool = phi @14 %f.3 @19 %f.4
  # br %11 @17 @18
  cmp $0x0, %al
  jne .L__main__17
  jmp .L__main__18
.L__main__20_F_14:
  jmp .L__main__20
.L__main__19:
  # %f.4: bool = load %f.ptr
  movb 14(%rsp), %cl
  # jmp @20
  jmp .L__main__20_F_19
.L__main__17:
  # %12: i32 = const 4
  # ret %12
  movl $0x4, %eax
  jmp .L__main__E
.L__main__18:
  # %f.5: bool = load %f.ptr
  movb 14(%rsp), %al
  # br %f.5 @24 @23
  cmp $0x0, %al
  jne .L__main__24_F_18
  jmp .L__main__23
.L__main__24:
  # %13: bool = phi @18 %f.5 @23 %f.6
  # br %13 @26 @25
  cmp $0x0, %al
  jne .L__main__26_F_24
  jmp .L__main__25
.L__main__24_F_18:
  jmp .L__main__24
.L__main__23:
  # %f.6: bool = load %f.ptr
  movb 14(%rsp), %cl
  # jmp @24
  jmp .L__main__24_F_23
.L__main__26:
  # %15: bool = phi @24 %13 @28 %14
  # br %15 @21 @22
  cmp $0x0, %al
  jne .L__main__21
  jmp .L__main__22
.L__main__26_F_24:
  jmp .L__main__26
.L__main__25:
  # %f.7: bool = load %f.ptr
  movb 14(%rsp), %cl
  # br %f.7 @28 @27
  cmp $0x0, %cl
  jne .L__main__28_F_25
  jmp .L__main__27
.L__main__21:
  # %16: i32 = const 5
  # ret %16
  movl $0x5, %eax
  jmp .L__main__E
.L__main__22:
  # %17: i32 = const 0
  # ret %17
  movl $0x0, %eax
  jmp .L__main__E
.L__main__28:
  # %14: bool = phi @25 %f.7 @27 %f.8
  # jmp @26
  jmp .L__main__26_F_28
.L__main__28_F_25:
  jmp .L__main__28
.L__main__27:
  # %f.8: bool = load %f.ptr
  movb 14(%rsp), %al
  # jmp @28
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
  movb %cl, %al
  jmp .L__main__20
.L__main__16_F_15:
  movb %cl, %al
  jmp .L__main__16
.L__main__11_F_10:
  movb %cl, %al
  jmp .L__main__11
.L__main__6_F_5:
  movb %cl, %al
  jmp .L__main__6
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
