.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %animal.ptr: ptr<Animal> = alloc Animal
  # ret
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  xor %rax, %rax
  ret
