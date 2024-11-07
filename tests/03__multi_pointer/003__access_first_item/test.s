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
  # %arg.ptr: ptr<ptr<u8>> = alloc ptr<u8>
  # %1: i32 = const 0
  # %2: ptr<ptr<u8>> = offset %argv.ptr %1
  movq 20(%rsp), %rcx
  # %3: ptr<u8> = load %2
  movq 0(%rcx), %rax
  # store %arg.ptr %3
  movq %rax, 12(%rsp)
  # %char.ptr: ptr<u8> = alloc u8
  # %4: i32 = const 0
  # %5: ptr<u8> = offset %arg.ptr %4
  movq 12(%rsp), %rcx
  # %6: u8 = load %5
  movb 0(%rcx), %al
  # store %char.ptr %6
  movb %al, 11(%rsp)
  # %char.1: u8 = load %char.ptr
  movb 11(%rsp), %al
  # %7: u8 = const 'b'
  # %8: bool = cmp_ne %char.1 %7
  cmp $0x62, %al
  setne %cl
  # br %8 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %9: i32 = const 1
  # ret %9
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %10: i32 = const 0
  # ret %10
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  ret
