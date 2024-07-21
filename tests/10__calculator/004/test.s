.extern stdout

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
  # %argc.1: i32 = load %argc.ptr
  movl 12(%rsp), %eax
  # %1: i32 = const 2
  # %2: bool = cmp_ne %argc.1 %1
  cmp $0x2, %eax
  setne %cl
  # br %2 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %3: i32 = const 1
  # call $exit %3
  movl $0x1, %edi
  call exit
.L__main__3:
  # %4: u8 = const '2'
  # %5: ptr<FILE> = load $stdout
  movq stdout, %rax
  # %6: i32 = call $fputc %4 %5
  movb $0x32, %dil
  movq %rax, %rsi
  call fputc
  # ret
  jmp .L__main__E
.L__main__E:
  add $0x10, %rsp
  xor %rax, %rax
  ret
