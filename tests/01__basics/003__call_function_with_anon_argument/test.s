.globl main
main:
.L__main__S:
.L__main__1:
  # %1: i32 = const 0
  # %2: i32 = call $echo %1
  movl $0x0, %edi
  call echo
  # ret %2
  jmp .L__main__E
.L__main__E:
  ret


echo:
.L__echo__S:
  sub $0x10, %rsp
.L__echo__1:
  # %value.ptr: ptr<i32> = alloc i32
  # store %value.ptr %value
  movl %edi, 12(%rsp)
  # %value.1: i32 = load %value.ptr
  movl 12(%rsp), %eax
  # ret %value.1
  jmp .L__echo__E
.L__echo__E:
  add $0x10, %rsp
  ret
