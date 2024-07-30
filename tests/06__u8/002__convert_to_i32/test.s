.globl main
main:
.L__main__S:
.L__main__1:
  # %1: i32 = const 255
  # %2: i32 = call $cast %1
  movl $0xff, %edi
  call cast
  # %3: i32 = const 255i32
  # %4: bool = cmp_ne %2 %3
  cmp $0xff, %eax
  setne %cl
  # br %4 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %5: i32 = const 1
  # ret %5
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %6: i32 = const 0
  # %7: i32 = call $cast %6
  movl $0x0, %edi
  call cast
  # %8: i32 = const 0
  # %9: bool = cmp_ne %7 %8
  cmp $0x0, %eax
  setne %cl
  # br %9 @4 @5
  cmp $0x0, %cl
  jne .L__main__4
  jmp .L__main__5
.L__main__4:
  # %10: i32 = const 2
  # ret %10
  movl $0x2, %eax
  jmp .L__main__E
.L__main__5:
  # %11: i32 = const 0
  # ret %11
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  ret


cast:
.L__cast__S:
  sub $0x10, %rsp
.L__cast__1:
  # %value.ptr: ptr<u8> = alloc u8
  # store %value.ptr %value
  movb %dil, 15(%rsp)
  # %value.1: u8 = load %value.ptr
  movb 15(%rsp), %al
  # %1: i32 = cast %value.1
  movb %al, %cl
  movzbl %cl, %ecx
  # ret %1
  movl %ecx, %eax
  jmp .L__cast__E
.L__cast__E:
  add $0x10, %rsp
  ret
