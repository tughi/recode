.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %array.ptr: ptr<ptr<i32>> = alloc ptr<i32>
  # %1: u64 = const 32
  # %2: ptr<Any> = call $malloc %1
  movq $0x20, %rdi
  call malloc
  # %3: ptr<i32> = cast %2
  movq %rax, %rcx
  # store %array.ptr %3
  movq %rcx, 8(%rsp)
  # %4: i32 = const 3
  # %5: ptr<i32> = offset %array.ptr %4
  movq 8(%rsp), %rcx
  # %6: i32 = const 42
  # store %5 %6
  movl $0x2a, 12(%rcx)
  # %7: i32 = const 3
  # %8: ptr<i32> = offset %array.ptr %7
  movq 8(%rsp), %rcx
  # %9: i32 = load %8
  movl 12(%rcx), %eax
  # %10: i32 = const 42
  # %11: i32 = sub %9 %10
  movl %eax, %ecx
  sub $0x2a, %ecx
  # ret %11
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
