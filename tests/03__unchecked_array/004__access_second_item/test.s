.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %argc.ptr: ptr<i32> = alloc i32
  # store %argc.ptr %argc
  movl %edi, 12(%rsp)
  # %argv.ptr: ptr<ptr<ptr<u8>>> = alloc ptr<ptr<u8>>
  # store %argv.ptr %argv
  movq %rsi, 4(%rsp)
  # %1: i32 = const 1
  # %2: ptr<ptr<u8>> = offset %argv.ptr %1
  movq 4(%rsp), %rcx
  # %3: i32 = const 1
  # %4: ptr<u8> = offset %2 %3
  movq 8(%rcx), %rsi
  # %5: u8 = load %4
  movb 1(%rsi), %al
  # %6: u8 = const '0'
  # %7: bool = cmp_ne %5 %6
  cmp $0x30, %al
  setne %cl
  # br %7 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %8: i32 = const 1
  # ret %8
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %9: i32 = const 0
  # ret %9
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
