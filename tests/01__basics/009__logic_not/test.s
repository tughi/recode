.globl main
main:
.L__main__S:
.L__main__1:
  # %1: bool = const true
  # %2: bool = call $test_not %1
  movb $0x1, %dil
  call test_not
  # br %2 @2 @3
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %3: i32 = const 1
  # ret %3
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %4: bool = const false
  # %5: bool = call $test_not %4
  movb $0x0, %dil
  call test_not
  # br %5 @4 @5
  cmp $0x0, %al
  jne .L__main__4
  jmp .L__main__5
.L__main__4:
  # jmp @6
  jmp .L__main__6
.L__main__5:
  # %6: i32 = const 2
  # ret %6
  movl $0x2, %eax
  jmp .L__main__E
.L__main__6:
  # %7: bool = const false
  # %8: bool = call $test_not %7
  movb $0x0, %dil
  call test_not
  # %9: bool = not %8
  movb %al, %cl
  xor $0x1, %cl
  # br %9 @7 @8
  cmp $0x0, %cl
  jne .L__main__7
  jmp .L__main__8
.L__main__7:
  # %10: i32 = const 3
  # ret %10
  movl $0x3, %eax
  jmp .L__main__E
.L__main__8:
  # %11: bool = const true
  # %12: bool = call $test_not %11
  movb $0x1, %dil
  call test_not
  # %13: bool = not %12
  movb %al, %cl
  xor $0x1, %cl
  # %14: bool = not %13
  movb %cl, %al
  xor $0x1, %al
  # br %14 @9 @10
  cmp $0x0, %al
  jne .L__main__9
  jmp .L__main__10
.L__main__9:
  # %15: i32 = const 4
  # ret %15
  movl $0x4, %eax
  jmp .L__main__E
.L__main__10:
  # %16: i32 = const 0
  # ret %16
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  ret


test_not:
.L__test_not__S:
  sub $0x10, %rsp
.L__test_not__1:
  # %v.ptr: ptr<bool> = alloc bool
  # store %v.ptr %v
  movb %dil, 15(%rsp)
  # %v.1: bool = load %v.ptr
  movb 15(%rsp), %al
  # %1: bool = not %v.1
  movb %al, %cl
  xor $0x1, %cl
  # ret %1
  movb %cl, %al
  jmp .L__test_not__E
.L__test_not__E:
  add $0x10, %rsp
  ret
