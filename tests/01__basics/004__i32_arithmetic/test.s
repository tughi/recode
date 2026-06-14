.globl main
main:
.L__main__S:
  pushq %rbx
.L__main__1:
  # %1: i32 = const 42
  # %2: i32 = const 10
  # %3: i32 = call $div %1 %2
  movl $0x2a, %edi
  movl $0xa, %esi
  call div
  # %4: i32 = const 2
  # %5: i32 = call $add %3 %4
  movl %eax, %edi
  movl $0x2, %esi
  call add
  # %6: i32 = const 42
  # %7: i32 = const 10
  # %8: i32 = call $mod %6 %7
  movl %eax, %ebx
  movl $0x2a, %edi
  movl $0xa, %esi
  call mod
  # %9: i32 = const 5
  # %10: i32 = call $add %8 %9
  movl %eax, %edi
  movl $0x5, %esi
  call add
  # %11: i32 = call $mul %5 %10
  movl %ebx, %edi
  movl %eax, %esi
  call mul
  # %12: i32 = const 42
  # %13: i32 = call $sub %11 %12
  movl %eax, %edi
  movl $0x2a, %esi
  call sub
  # ret %13
  jmp .L__main__E
.L__main__E:
  popq %rbx
  ret


add:
.L__add__S:
  sub $0x10, %rsp
.L__add__1:
  # %v1.ptr: ptr<i32> = alloc i32
  # store %v1.ptr %v1
  movl %edi, 12(%rsp)
  # %v2.ptr: ptr<i32> = alloc i32
  # store %v2.ptr %v2
  movl %esi, 8(%rsp)
  # %v1.1: i32 = load %v1.ptr
  movl 12(%rsp), %eax
  # %v2.1: i32 = load %v2.ptr
  movl 8(%rsp), %ecx
  # %1: i32 = add %v1.1 %v2.1
  movl %eax, %edx
  add %ecx, %edx
  # ret %1
  movl %edx, %eax
  jmp .L__add__E
.L__add__E:
  add $0x10, %rsp
  ret


sub:
.L__sub__S:
  sub $0x10, %rsp
.L__sub__1:
  # %v1.ptr: ptr<i32> = alloc i32
  # store %v1.ptr %v1
  movl %edi, 12(%rsp)
  # %v2.ptr: ptr<i32> = alloc i32
  # store %v2.ptr %v2
  movl %esi, 8(%rsp)
  # %v1.1: i32 = load %v1.ptr
  movl 12(%rsp), %eax
  # %v2.1: i32 = load %v2.ptr
  movl 8(%rsp), %ecx
  # %1: i32 = sub %v1.1 %v2.1
  movl %eax, %edx
  sub %ecx, %edx
  # ret %1
  movl %edx, %eax
  jmp .L__sub__E
.L__sub__E:
  add $0x10, %rsp
  ret


mul:
.L__mul__S:
  sub $0x10, %rsp
.L__mul__1:
  # %v1.ptr: ptr<i32> = alloc i32
  # store %v1.ptr %v1
  movl %edi, 12(%rsp)
  # %v2.ptr: ptr<i32> = alloc i32
  # store %v2.ptr %v2
  movl %esi, 8(%rsp)
  # %v1.1: i32 = load %v1.ptr
  movl 12(%rsp), %eax
  # %v2.1: i32 = load %v2.ptr
  movl 8(%rsp), %ecx
  # %1: i32 = mul %v1.1 %v2.1
  movl %eax, %edx
  movl %edx, %esi
  movl %esi, %eax
  mull %ecx
  # ret %1
  jmp .L__mul__E
.L__mul__E:
  add $0x10, %rsp
  ret


div:
.L__div__S:
  sub $0x10, %rsp
.L__div__1:
  # %v1.ptr: ptr<i32> = alloc i32
  # store %v1.ptr %v1
  movl %edi, 12(%rsp)
  # %v2.ptr: ptr<i32> = alloc i32
  # store %v2.ptr %v2
  movl %esi, 8(%rsp)
  # %v1.1: i32 = load %v1.ptr
  movl 12(%rsp), %eax
  # %v2.1: i32 = load %v2.ptr
  movl 8(%rsp), %ecx
  # %1: i32 = div %v1.1 %v2.1
  movl %eax, %edx
  movl %edx, %esi
  movl %esi, %eax
  cltd
  idivl %ecx
  # ret %1
  jmp .L__div__E
.L__div__E:
  add $0x10, %rsp
  ret


mod:
.L__mod__S:
  sub $0x10, %rsp
.L__mod__1:
  # %v1.ptr: ptr<i32> = alloc i32
  # store %v1.ptr %v1
  movl %edi, 12(%rsp)
  # %v2.ptr: ptr<i32> = alloc i32
  # store %v2.ptr %v2
  movl %esi, 8(%rsp)
  # %v1.1: i32 = load %v1.ptr
  movl 12(%rsp), %eax
  # %v2.1: i32 = load %v2.ptr
  movl 8(%rsp), %ecx
  # %1: i32 = mod %v1.1 %v2.1
  movl %eax, %edx
  movl %edx, %esi
  movl %esi, %eax
  cltd
  idivl %ecx
  # ret %1
  movl %edx, %eax
  jmp .L__mod__E
.L__mod__E:
  add $0x10, %rsp
  ret
