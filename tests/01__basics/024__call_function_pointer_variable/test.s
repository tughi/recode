.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %echo_pointer.ptr: ptr<ptr<func (value: i32) -> i32>> = alloc ptr<func (value: i32) -> i32>
  # %1: ptr<func (value: i32) -> i32> = address $echo__value
  # store %echo_pointer.ptr %1
  lea echo__value, %rax
  movq %rax, 8(%rsp)
  # %echo_pointer.1: ptr<func (value: i32) -> i32> = load %echo_pointer.ptr
  movq 8(%rsp), %rax
  # %2: i32 = const 42
  # %3: i32 = call %echo_pointer.1 %2
  movl $0x2a, %edi
  call *%rax
  # %4: i32 = const 42
  # %5: i32 = sub %3 %4
  movl %eax, %ecx
  sub $0x2a, %ecx
  # ret %5
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  ret


echo__value:
.L__echo__value__S:
  sub $0x10, %rsp
.L__echo__value__1:
  # %value.ptr: ptr<i32> = alloc i32
  # store %value.ptr %value
  movl %edi, 12(%rsp)
  # %value.1: i32 = load %value.ptr
  movl 12(%rsp), %eax
  # ret %value.1
  jmp .L__echo__value__E
.L__echo__value__E:
  add $0x10, %rsp
  ret
