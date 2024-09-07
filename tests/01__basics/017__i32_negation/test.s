.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %value.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 42
  # store %value.ptr %1
  movl $0x2a, 12(%rsp)
  # %value.1: i32 = load %value.ptr
  movl 12(%rsp), %eax
  # %2: i32 = const -1
  # %3: i32 = mul %value.1 %2
  movl %eax, %ecx
  movl %ecx, %eax
  movl $0xffffffff, %esi
  mull %esi
  # %value.2: i32 = load %value.ptr
  movl 12(%rsp), %ecx
  # %4: i32 = neg %value.2
  movl %ecx, %edx
  neg %edx
  # %5: bool = cmp_ne %3 %4
  cmp %edx, %eax
  setne %cl
  # br %5 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %6: i32 = const 1
  # ret %6
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %7: i32 = const 0
  # ret %7
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
