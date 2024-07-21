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
  sub $0x20, %rsp
.L__fibonacci__of__1:
  # %n.ptr: ptr<i32> = alloc i32
  # store %n.ptr %n
  movl %edi, 28(%rsp)
  # %n.1: i32 = load %n.ptr
  movl 28(%rsp), %eax
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
  movl 28(%rsp), %eax
  # ret %n.2
  jmp .L__fibonacci__of__E
.L__fibonacci__of__3:
  # %v1.ptr: ptr<i32> = alloc i32
  # %3: i32 = const 0
  # store %v1.ptr %3
  movl $0x0, 24(%rsp)
  # %v2.ptr: ptr<i32> = alloc i32
  # %4: i32 = const 1
  # store %v2.ptr %4
  movl $0x1, 20(%rsp)
  # %i.ptr: ptr<i32> = alloc i32
  # %5: i32 = const 2
  # store %i.ptr %5
  movl $0x2, 16(%rsp)
  # jmp @4
  jmp .L__fibonacci__of__4
.L__fibonacci__of__4:
  # %v3.ptr: ptr<i32> = alloc i32
  # %v1.1: i32 = load %v1.ptr
  movl 24(%rsp), %eax
  # %v2.1: i32 = load %v2.ptr
  movl 20(%rsp), %ecx
  # %6: i32 = add %v1.1 %v2.1
  movl %eax, %edx
  add %ecx, %edx
  # store %v3.ptr %6
  movl %edx, 12(%rsp)
  # %v2.2: i32 = load %v2.ptr
  movl 20(%rsp), %eax
  # store %v1.ptr %v2.2
  movl %eax, 24(%rsp)
  # %v3.1: i32 = load %v3.ptr
  movl 12(%rsp), %eax
  # store %v2.ptr %v3.1
  movl %eax, 20(%rsp)
  # %i.1: i32 = load %i.ptr
  movl 16(%rsp), %eax
  # %n.3: i32 = load %n.ptr
  movl 28(%rsp), %ecx
  # %7: bool = cmp_eq %i.1 %n.3
  cmp %ecx, %eax
  sete %dl
  # br %7 @6 @7
  cmp $0x0, %dl
  jne .L__fibonacci__of__6
  jmp .L__fibonacci__of__7
.L__fibonacci__of__6:
  # jmp @5
  jmp .L__fibonacci__of__5
.L__fibonacci__of__7:
  # %i.2: i32 = load %i.ptr
  movl 16(%rsp), %eax
  # %8: i32 = const 1
  # %9: i32 = add %i.2 %8
  movl %eax, %ecx
  add $0x1, %ecx
  # store %i.ptr %9
  movl %ecx, 16(%rsp)
  # jmp @4
  jmp .L__fibonacci__of__4
.L__fibonacci__of__5:
  # %v2.3: i32 = load %v2.ptr
  movl 20(%rsp), %eax
  # ret %v2.3
  jmp .L__fibonacci__of__E
.L__fibonacci__of__E:
  add $0x20, %rsp
  ret
