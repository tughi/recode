.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %errors.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 6
  # store %errors.ptr %1
  movl $0x6, 12(%rsp)
  # %2: i32 = const 42
  # %3: i32 = call $echo %2
  movl $0x2a, %edi
  call echo
  # %4: i32 = const 42
  # %5: bool = cmp_eq %3 %4
  cmp $0x2a, %eax
  sete %cl
  # br %5 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %errors.1: i32 = load %errors.ptr
  movl 12(%rsp), %eax
  # %6: i32 = const 1
  # %7: i32 = sub %errors.1 %6
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %7
  movl %ecx, 12(%rsp)
  # jmp @3
  jmp .L__main__3
.L__main__3:
  # %8: i32 = const 42
  # %9: i32 = call $echo %8
  movl $0x2a, %edi
  call echo
  # %10: i32 = const 42
  # %11: bool = cmp_ne %9 %10
  cmp $0x2a, %eax
  setne %cl
  # br %11 @4 @5
  cmp $0x0, %cl
  jne .L__main__4
  jmp .L__main__5
.L__main__4:
  # jmp @6
  jmp .L__main__6
.L__main__5:
  # %errors.2: i32 = load %errors.ptr
  movl 12(%rsp), %eax
  # %12: i32 = const 1
  # %13: i32 = sub %errors.2 %12
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %13
  movl %ecx, 12(%rsp)
  # jmp @6
  jmp .L__main__6
.L__main__6:
  # %14: i32 = const 42
  # %15: i32 = call $echo %14
  movl $0x2a, %edi
  call echo
  # %16: i32 = const 13
  # %17: bool = cmp_lt %15 %16
  cmp $0xd, %eax
  setl %cl
  # br %17 @7 @8
  cmp $0x0, %cl
  jne .L__main__7
  jmp .L__main__8
.L__main__7:
  # jmp @9
  jmp .L__main__9
.L__main__8:
  # %errors.3: i32 = load %errors.ptr
  movl 12(%rsp), %eax
  # %18: i32 = const 1
  # %19: i32 = sub %errors.3 %18
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %19
  movl %ecx, 12(%rsp)
  # jmp @9
  jmp .L__main__9
.L__main__9:
  # %20: i32 = const 42
  # %21: i32 = call $echo %20
  movl $0x2a, %edi
  call echo
  # %22: i32 = const 42
  # %23: bool = cmp_le %21 %22
  cmp $0x2a, %eax
  setle %cl
  # br %23 @10 @11
  cmp $0x0, %cl
  jne .L__main__10
  jmp .L__main__11
.L__main__10:
  # %errors.4: i32 = load %errors.ptr
  movl 12(%rsp), %eax
  # %24: i32 = const 1
  # %25: i32 = sub %errors.4 %24
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %25
  movl %ecx, 12(%rsp)
  # jmp @11
  jmp .L__main__11
.L__main__11:
  # %26: i32 = const 42
  # %27: i32 = call $echo %26
  movl $0x2a, %edi
  call echo
  # %28: i32 = const 13
  # %29: bool = cmp_gt %27 %28
  cmp $0xd, %eax
  setg %cl
  # br %29 @12 @13
  cmp $0x0, %cl
  jne .L__main__12
  jmp .L__main__13
.L__main__12:
  # %errors.5: i32 = load %errors.ptr
  movl 12(%rsp), %eax
  # %30: i32 = const 1
  # %31: i32 = sub %errors.5 %30
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %31
  movl %ecx, 12(%rsp)
  # jmp @13
  jmp .L__main__13
.L__main__13:
  # %32: i32 = const 42
  # %33: i32 = call $echo %32
  movl $0x2a, %edi
  call echo
  # %34: i32 = const 42
  # %35: bool = cmp_ge %33 %34
  cmp $0x2a, %eax
  setge %cl
  # br %35 @14 @15
  cmp $0x0, %cl
  jne .L__main__14
  jmp .L__main__15
.L__main__14:
  # %errors.6: i32 = load %errors.ptr
  movl 12(%rsp), %eax
  # %36: i32 = const 1
  # %37: i32 = sub %errors.6 %36
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %37
  movl %ecx, 12(%rsp)
  # jmp @15
  jmp .L__main__15
.L__main__15:
  # %errors.7: i32 = load %errors.ptr
  movl 12(%rsp), %eax
  # ret %errors.7
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret


echo:
.L__echo__S:
  sub $0x10, %rsp
.L__echo__1:
  # %v.ptr: ptr<i32> = alloc i32
  # store %v.ptr %v
  movl %edi, 12(%rsp)
  # %v.1: i32 = load %v.ptr
  movl 12(%rsp), %eax
  # ret %v.1
  jmp .L__echo__E
.L__echo__E:
  add $0x10, %rsp
  ret
