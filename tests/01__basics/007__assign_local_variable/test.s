.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %x.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 0
  # store %x.ptr %1
  movl $0x0, 12(%rsp)
  # %x.1: i32 = load %x.ptr
  movl 12(%rsp), %eax
  # %2: i32 = const 1
  # %3: i32 = add %x.1 %2
  movl %eax, %ecx
  add $0x1, %ecx
  # store %x.ptr %3
  movl %ecx, 12(%rsp)
  # %x.2: i32 = load %x.ptr
  movl 12(%rsp), %eax
  # %4: i32 = const 1
  # %5: i32 = sub %x.2 %4
  movl %eax, %ecx
  sub $0x1, %ecx
  # ret %5
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
