.globl main
main:
.L__main__S:
  sub $0x30, %rsp
.L__main__1:
  # %third.ptr: ptr<Number> = alloc Number
  # %1: i32 = const 43
  # %2: Number = struct { Number.value: %1 }
  # %3: ptr<i32> = offset %third.ptr Number.value
  lea 36(%rsp), %rax
  # store %3 %1
  movl $0x2b, 0(%rax)
  # %second.ptr: ptr<Number> = alloc Number
  # %4: i32 = const 42
  # %5: Number = struct { Number.value: %4, Number.next: %third.ptr }
  # %6: ptr<i32> = offset %second.ptr Number.value
  lea 24(%rsp), %rax
  # store %6 %4
  movl $0x2a, 0(%rax)
  # %7: ptr<ptr<Number>> = offset %second.ptr Number.next
  lea 24(%rsp), %rax
  # store %7 %third.ptr
  lea 36(%rsp), %rcx
  movq %rcx, 4(%rax)
  # %first.ptr: ptr<Number> = alloc Number
  # %8: i32 = const 41
  # %9: Number = struct { Number.value: %8, Number.next: %second.ptr }
  # %10: ptr<i32> = offset %first.ptr Number.value
  lea 12(%rsp), %rax
  # store %10 %8
  movl $0x29, 0(%rax)
  # %11: ptr<ptr<Number>> = offset %first.ptr Number.next
  lea 12(%rsp), %rax
  # store %11 %second.ptr
  lea 24(%rsp), %rcx
  movq %rcx, 4(%rax)
  # %second_value.ptr: ptr<i32> = alloc i32
  # %12: ptr<ptr<Number>> = offset %first.ptr Number.next
  lea 12(%rsp), %rax
  # %13: ptr<Number> = load %12
  movq 4(%rax), %rcx
  # %14: ptr<i32> = offset %13 Number.value
  movq %rcx, %rax
  # %15: i32 = load %14
  movl 0(%rax), %ecx
  # store %second_value.ptr %15
  movl %ecx, 8(%rsp)
  # %second_value_ref.ptr: ptr<ptr<i32>> = alloc ptr<i32>
  # %16: ptr<ptr<Number>> = offset %first.ptr Number.next
  lea 12(%rsp), %rax
  # %17: ptr<Number> = load %16
  movq 4(%rax), %rcx
  # %18: ptr<i32> = offset %17 Number.value
  movq %rcx, %rax
  # store %second_value_ref.ptr %18
  lea 0(%rax), %rcx
  movq %rcx, 0(%rsp)
  # %second_value.1: i32 = load %second_value.ptr
  movl 8(%rsp), %eax
  # %19: i32 = const 42
  # %20: bool = cmp_ne %second_value.1 %19
  cmp $0x2a, %eax
  setne %cl
  # br %20 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %21: i32 = const 1
  # ret %21
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %second_value_ref.1: ptr<i32> = load %second_value_ref.ptr
  movq 0(%rsp), %rax
  # %22: i32 = load %second_value_ref.1
  movl 0(%rax), %ecx
  # %23: i32 = const 42
  # %24: bool = cmp_ne %22 %23
  cmp $0x2a, %ecx
  setne %al
  # br %24 @4 @5
  cmp $0x0, %al
  jne .L__main__4
  jmp .L__main__5
.L__main__4:
  # %25: i32 = const 2
  # ret %25
  movl $0x2, %eax
  jmp .L__main__E
.L__main__5:
  # %26: i32 = const 0
  # ret %26
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x30, %rsp
  ret
