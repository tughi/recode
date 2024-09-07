.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %function_pointer.ptr: ptr<ptr<func (value: i32) -> i32>> = alloc ptr<func (value: i32) -> i32>
  # %1: ptr<func (value: i32) -> i32> = address $echo__value
  # store %function_pointer.ptr %1
  lea echo__value, %rax
  movq %rax, 8(%rsp)
  # ret
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  xor %rax, %rax
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
