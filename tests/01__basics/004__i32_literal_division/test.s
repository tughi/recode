.globl main
main:
.L__main__S:
.L__main__1:
  # %1: i32 = call $forty_two
  call forty_two
  # %2: i32 = const 42
  # %3: i32 = div %1 %2
  movl %eax, %ecx
  movl %ecx, %eax
  cltd
  movl $0x2a, %esi
  idivl %esi
  # %4: i32 = const 1
  # %5: i32 = sub %3 %4
  movl %eax, %ecx
  sub $0x1, %ecx
  # ret %5
  movl %ecx, %eax
  jmp .L__main__E
.L__main__E:
  ret


forty_two:
.L__forty_two__S:
.L__forty_two__1:
  # %1: i32 = const 42
  # ret %1
  movl $0x2a, %eax
  jmp .L__forty_two__E
.L__forty_two__E:
  ret
