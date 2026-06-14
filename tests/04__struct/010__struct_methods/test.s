pNumber__get_value:
.L__pNumber__get_value__S:
  sub $0x10, %rsp
.L__pNumber__get_value__1:
  # %self.ptr: ptr<ptr<Number>> = alloc ptr<Number>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %1: ptr<Number> = load %self.ptr
  movq 8(%rsp), %rax
  # %2: ptr<i32> = offset %1 Number.value
  movq %rax, %rcx
  # %3: i32 = load %2
  movl 0(%rcx), %eax
  # ret %3
  jmp .L__pNumber__get_value__E
.L__pNumber__get_value__E:
  add $0x10, %rsp
  ret


pNumber__set_value:
.L__pNumber__set_value__S:
  sub $0x10, %rsp
.L__pNumber__set_value__1:
  # %self.ptr: ptr<ptr<Number>> = alloc ptr<Number>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %value.ptr: ptr<i32> = alloc i32
  # store %value.ptr %value
  movl %esi, 4(%rsp)
  # %1: ptr<Number> = load %self.ptr
  movq 8(%rsp), %rax
  # %2: ptr<i32> = offset %1 Number.value
  movq %rax, %rcx
  # %value.1: i32 = load %value.ptr
  movl 4(%rsp), %eax
  # store %2 %value.1
  movl %eax, 0(%rcx)
  # ret
  jmp .L__pNumber__set_value__E
.L__pNumber__set_value__E:
  add $0x10, %rsp
  ret


.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %number.ptr: ptr<Number> = alloc Number
  # %1: i32 = const 0
  # %2: Number = struct { Number.value: %1 }
  # %3: ptr<i32> = offset %number.ptr Number.value
  lea 12(%rsp), %rax
  # store %3 %1
  movl $0x0, 0(%rax)
  # %4: i32 = const 42
  # call $pNumber__set_value %number.ptr %4
  lea 12(%rsp), %rdi
  movl $0x2a, %esi
  call pNumber__set_value
  # %5: i32 = call $pNumber__get_value %number.ptr
  lea 12(%rsp), %rdi
  call pNumber__get_value
  # %6: i32 = const 42
  # %7: i32 = sub %5 %6
  movl %eax, %ecx
  sub $0x2a, %ecx
  # ret %7
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret
