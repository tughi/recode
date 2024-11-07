.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %argc.ptr: ptr<i32> = alloc i32
  # store %argc.ptr %argc
  movl %edi, 12(%rsp)
  # %argv.ptr: ptr<ptr<ptr<u8>>> = alloc ptr<ptr<u8>>
  # store %argv.ptr %argv
  movq %rsi, 4(%rsp)
  # ret
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  xor %rax, %rax
  ret
