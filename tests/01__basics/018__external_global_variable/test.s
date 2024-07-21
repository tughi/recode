.extern optind

.globl main
main:
.L__main__S:
.L__main__1:
  # %1: i32 = load $optind
  movl optind, %eax
  # %2: i32 = const 1
  # %3: i32 = sub %1 %2
  movl %eax, %ecx
  sub $0x1, %ecx
  # ret %3
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  ret
