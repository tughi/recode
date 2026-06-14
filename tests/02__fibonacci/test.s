.globl main
main:
.L__main__S:
.L__main__1:
  # %1: i32 = const 12
  # %2: i32 = call $fibonacci__of %1
  movl $0xc, %edi
  call fibonacci__of
  # %3: i32 = const 144
  # %4: i32 = sub %2 %3
  movl %eax, %ecx
  sub $0x90, %ecx
  # ret %4
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  ret


fibonacci__of:
.L__fibonacci__of__S:
  pushq %rbx
  sub $0x10, %rsp
.L__fibonacci__of__1:
  # %n.ptr: ptr<i32> = alloc i32
  # store %n.ptr %n
  movl %edi, 12(%rsp)
  # %n.1: i32 = load %n.ptr
  movl 12(%rsp), %eax
  # %1: i32 = const 1
  # %2: bool = cmp_le %n.1 %1
  cmp $0x1, %eax
  setle %cl
  # br %2 @2 @3
  cmp $0x0, %cl
  jne .L__fibonacci__of__2
  jmp .L__fibonacci__of__3
.L__fibonacci__of__2:
  # %n.2: i32 = load %n.ptr
  movl 12(%rsp), %eax
  # ret %n.2
  jmp .L__fibonacci__of__E
.L__fibonacci__of__3:
  # %n.3: i32 = load %n.ptr
  movl 12(%rsp), %eax
  # %3: i32 = const 1
  # %4: i32 = sub %n.3 %3
  movl %eax, %ecx
  sub $0x1, %ecx
  # %5: i32 = call $fibonacci__of %4
  movl %ecx, %edi
  call fibonacci__of
  # %n.4: i32 = load %n.ptr
  movl 12(%rsp), %ecx
  # %6: i32 = const 2
  # %7: i32 = sub %n.4 %6
  movl %ecx, %edx
  sub $0x2, %edx
  # %8: i32 = call $fibonacci__of %7
  movl %eax, %ebx
  movl %edx, %edi
  call fibonacci__of
  # %9: i32 = add %5 %8
  movl %ebx, %ecx
  add %eax, %ecx
  # ret %9
  movl %ecx, %eax
  jmp .L__fibonacci__of__E
.L__fibonacci__of__E:
  add $0x10, %rsp
  popq %rbx
  ret
