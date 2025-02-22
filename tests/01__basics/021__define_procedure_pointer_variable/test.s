.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %procedure_pointer.ptr: ptr<ptr<proc (value: i32) -> i32>> = alloc ptr<proc (value: i32) -> i32>
  # ret
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  xor %rax, %rax
  ret
