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
  # %i.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 1
  # store %i.ptr %1
  movl $0x1, 0(%rsp)
  # %i.1: i32 = load %i.ptr
  movl 0(%rsp), %eax
  # %2: ptr<ptr<u8>> = offset %argv.ptr %i.1
  movl %eax, %ecx
  movq 4(%rsp), %rsi
  movslq %ecx, %rax
  cqo
  imulq $0x8, %rax
  add %rax, %rsi
  # %i.2: i32 = load %i.ptr
  movl 0(%rsp), %eax
  # %3: ptr<u8> = offset %2 %i.2
  movl %eax, %ecx
  movq 0(%rsi), %rdi
  movslq %ecx, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  # %4: u8 = load %3
  movb 0(%rdi), %al
  # %5: u8 = const '0'
  # %6: bool = cmp_ne %4 %5
  cmp $0x30, %al
  setne %cl
  # br %6 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %7: i32 = const 1
  # ret %7
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %8: i32 = const 0
  # ret %8
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
