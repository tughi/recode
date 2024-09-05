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
  # %7: ptr<u8> = offset %name.ptr %6
  movq 4(%rsp), %rcx
  # %8: u8 = load %7
  movb 0(%rcx), %al
  # %9: u8 = const 'b'
  # %10: bool = cmp_ne %8 %9
  cmp $0x62, %al
  setne %cl
  # br %10 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %11: i32 = const 1
  # ret %11
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %12: i32 = const 0
  # ret %12
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  ret
