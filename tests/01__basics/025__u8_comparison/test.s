.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %min.ptr: ptr<u8> = alloc u8
  # %1: u8 = const 0u8
  # store %min.ptr %1
  movb $0x0, 15(%rsp)
  # %max.ptr: ptr<u8> = alloc u8
  # %2: u8 = const 255u8
  # store %max.ptr %2
  movb $0xff, 14(%rsp)
  # %errors.ptr: ptr<i32> = alloc i32
  # %3: i32 = const 8
  # store %errors.ptr %3
  movl $0x8, 10(%rsp)
  # %4: u8 = call $forty_two
  call forty_two
  # %5: u8 = const 42
  # %6: bool = cmp_eq %4 %5
  cmp $0x2a, %al
  sete %cl
  # br %6 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %errors.1: i32 = load %errors.ptr
  movl 10(%rsp), %eax
  # %7: i32 = const 1
  # %8: i32 = sub %errors.1 %7
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %8
  movl %ecx, 10(%rsp)
  # jmp @3
  jmp .L__main__3
.L__main__3:
  # %9: u8 = call $forty_two
  call forty_two
  # %10: u8 = const 42
  # %11: bool = cmp_ne %9 %10
  cmp $0x2a, %al
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
  movl 10(%rsp), %eax
  # %12: i32 = const 1
  # %13: i32 = sub %errors.2 %12
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %13
  movl %ecx, 10(%rsp)
  # jmp @6
  jmp .L__main__6
.L__main__6:
  # %14: u8 = call $forty_two
  call forty_two
  # %max.1: u8 = load %max.ptr
  movb 14(%rsp), %cl
  # %15: bool = cmp_lt %14 %max.1
  cmp %cl, %al
  setb %dl
  # br %15 @7 @8
  cmp $0x0, %dl
  jne .L__main__7
  jmp .L__main__8
.L__main__7:
  # %errors.3: i32 = load %errors.ptr
  movl 10(%rsp), %eax
  # %16: i32 = const 1
  # %17: i32 = sub %errors.3 %16
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %17
  movl %ecx, 10(%rsp)
  # jmp @8
  jmp .L__main__8
.L__main__8:
  # %18: u8 = call $forty_two
  call forty_two
  # %min.1: u8 = load %min.ptr
  movb 15(%rsp), %cl
  # %19: bool = cmp_lt %18 %min.1
  cmp %cl, %al
  setb %dl
  # br %19 @9 @10
  cmp $0x0, %dl
  jne .L__main__9
  jmp .L__main__10
.L__main__9:
  # jmp @11
  jmp .L__main__11
.L__main__10:
  # %errors.4: i32 = load %errors.ptr
  movl 10(%rsp), %eax
  # %20: i32 = const 1
  # %21: i32 = sub %errors.4 %20
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %21
  movl %ecx, 10(%rsp)
  # jmp @11
  jmp .L__main__11
.L__main__11:
  # %22: u8 = call $forty_two
  call forty_two
  # %23: u8 = const 42
  # %24: bool = cmp_le %22 %23
  cmp $0x2a, %al
  setbe %cl
  # br %24 @12 @13
  cmp $0x0, %cl
  jne .L__main__12
  jmp .L__main__13
.L__main__12:
  # %errors.5: i32 = load %errors.ptr
  movl 10(%rsp), %eax
  # %25: i32 = const 1
  # %26: i32 = sub %errors.5 %25
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %26
  movl %ecx, 10(%rsp)
  # jmp @13
  jmp .L__main__13
.L__main__13:
  # %27: u8 = call $forty_two
  call forty_two
  # %max.2: u8 = load %max.ptr
  movb 14(%rsp), %cl
  # %28: bool = cmp_lt %27 %max.2
  cmp %cl, %al
  setb %dl
  # br %28 @14 @15
  cmp $0x0, %dl
  jne .L__main__14
  jmp .L__main__15
.L__main__14:
  # %errors.6: i32 = load %errors.ptr
  movl 10(%rsp), %eax
  # %29: i32 = const 1
  # %30: i32 = sub %errors.6 %29
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %30
  movl %ecx, 10(%rsp)
  # jmp @15
  jmp .L__main__15
.L__main__15:
  # %31: u8 = call $forty_two
  call forty_two
  # %min.2: u8 = load %min.ptr
  movb 15(%rsp), %cl
  # %32: bool = cmp_lt %31 %min.2
  cmp %cl, %al
  setb %dl
  # br %32 @16 @17
  cmp $0x0, %dl
  jne .L__main__16
  jmp .L__main__17
.L__main__16:
  # jmp @18
  jmp .L__main__18
.L__main__17:
  # %errors.7: i32 = load %errors.ptr
  movl 10(%rsp), %eax
  # %33: i32 = const 1
  # %34: i32 = sub %errors.7 %33
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %34
  movl %ecx, 10(%rsp)
  # jmp @18
  jmp .L__main__18
.L__main__18:
  # %35: u8 = call $forty_two
  call forty_two
  # %36: u8 = const 42
  # %37: bool = cmp_ge %35 %36
  cmp $0x2a, %al
  setae %cl
  # br %37 @19 @20
  cmp $0x0, %cl
  jne .L__main__19
  jmp .L__main__20
.L__main__19:
  # %errors.8: i32 = load %errors.ptr
  movl 10(%rsp), %eax
  # %38: i32 = const 1
  # %39: i32 = sub %errors.8 %38
  movl %eax, %ecx
  sub $0x1, %ecx
  # store %errors.ptr %39
  movl %ecx, 10(%rsp)
  # jmp @20
  jmp .L__main__20
.L__main__20:
  # %errors.9: i32 = load %errors.ptr
  movl 10(%rsp), %eax
  # ret %errors.9
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret


forty_two:
.L__forty_two__S:
.L__forty_two__1:
  # %1: u8 = const 42
  # ret %1
  movb $0x2a, %al
  jmp .L__forty_two__E
.L__forty_two__E:
  ret
