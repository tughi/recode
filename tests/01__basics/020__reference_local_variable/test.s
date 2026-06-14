.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %value.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 42
  # store %value.ptr %1
  movl $0x2a, 12(%rsp)
  # %value_ref.ptr: ptr<ptr<i32>> = alloc ptr<i32>
  # store %value_ref.ptr %value.ptr
  lea 12(%rsp), %rax
  movq %rax, 4(%rsp)
  # %value_ref.1: ptr<i32> = load %value_ref.ptr
  movq 4(%rsp), %rax
  # %2: i32 = load %value_ref.1
  movl 0(%rax), %ecx
  # %3: i32 = const 42
  # %4: i32 = sub %2 %3
  movl %ecx, %eax
  sub $0x2a, %eax
  # ret %4
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
