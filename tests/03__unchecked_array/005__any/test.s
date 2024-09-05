.globl main
main:
.L__main__S:
  sub $0x20, %rsp
.L__main__1:
  # %argc.ptr: ptr<i32> = alloc i32
  # store %argc.ptr %argc
  movl %edi, 28(%rsp)
  # %argv.ptr: ptr<ptr<ptr<u8>>> = alloc ptr<ptr<u8>>
  # store %argv.ptr %argv
  movq %rsi, 20(%rsp)
  # %any.ptr: ptr<ptr<Any>> = alloc ptr<Any>
  # %1: i32 = const 0
  # %2: ptr<ptr<u8>> = offset %argv.ptr %1
  movq 20(%rsp), %rcx
  # %3: ptr<u8> = load %2
  movq 0(%rcx), %rax
  # %4: ptr<Any> = cast %3
  movq %rax, %rcx
  # store %any.ptr %4
  movq %rcx, 12(%rsp)
  # %name.ptr: ptr<ptr<u8>> = alloc ptr<u8>
  # %any.1: ptr<Any> = load %any.ptr
  movq 12(%rsp), %rax
  # %5: ptr<u8> = cast %any.1
  movq %rax, %rcx
  # store %name.ptr %5
  movq %rcx, 4(%rsp)
  # %6: i32 = const 0
  # %7: ptr<ptr<u8>> = offset %argv.ptr %6
  movq 20(%rsp), %rcx
  # %8: i32 = const 0
  # %9: ptr<u8> = offset %7 %8
  movq 0(%rcx), %rsi
  # %10: u8 = load %9
  movb 0(%rsi), %al
  # %11: i32 = const 0
  # %12: ptr<u8> = offset %name.ptr %11
  movb %al, %cl
  movq 4(%rsp), %rsi
  # %13: u8 = load %12
  movb 0(%rsi), %al
  # %14: u8 = sub %10 %13
  movb %cl, %dl
  sub %al, %dl
  # %15: u8 = const 0
  # %16: bool = cmp_ne %14 %15
  cmp $0x0, %dl
  setne %al
  # br %16 @2 @3
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %17: i32 = const 1
  # ret %17
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %18: i32 = const 0
  # ret %18
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  ret
