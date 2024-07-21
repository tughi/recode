.extern stdin

.extern stdout

.extern stderr

.globl main
main:
.L__main__S:
  sub $0x20, %rsp
.L__main__1:
  # %argc.ptr: ptr<i32> = alloc i32
  # store %argc.ptr %argc
  movl %edi, 28(%rsp)
  # %argv.ptr: ptr<ptr<ptr<u8>>> = alloc ptr<ptr<u8>>
  # store %argv.ptr %argv
  movq %rsi, 20(%rsp)
  # %i.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 1
  # store %i.ptr %1
  movl $0x1, 16(%rsp)
  # jmp @2
  jmp .L__main__2
.L__main__2:
  # %arg.ptr: ptr<ptr<u8>> = alloc ptr<u8>
  # %i.1: i32 = load %i.ptr
  movl 16(%rsp), %eax
  # %2: ptr<ptr<u8>> = offset %argv.ptr %i.1
  movl %eax, %ecx
  movq 20(%rsp), %rsi
  movslq %ecx, %rax
  cqo
  imulq $0x8, %rax
  add %rax, %rsi
  # %3: ptr<u8> = load %2
  movq 0(%rsi), %rax
  # store %arg.ptr %3
  movq %rax, 8(%rsp)
  # %j.ptr: ptr<i32> = alloc i32
  # %4: i32 = const 0
  # store %j.ptr %4
  movl $0x0, 4(%rsp)
  # jmp @4
  jmp .L__main__4
.L__main__4:
  # %j.1: i32 = load %j.ptr
  movl 4(%rsp), %eax
  # %5: ptr<u8> = offset %arg.ptr %j.1
  movl %eax, %ecx
  movq 8(%rsp), %rsi
  movslq %ecx, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rsi
  # %6: u8 = load %5
  movb 0(%rsi), %al
  # %7: u8 = const 0
  # %8: bool = cmp_eq %6 %7
  cmp $0x0, %al
  sete %cl
  # br %8 @6 @7
  cmp $0x0, %cl
  jne .L__main__6
  jmp .L__main__7
.L__main__6:
  # jmp @5
  jmp .L__main__5
.L__main__7:
  # %j.2: i32 = load %j.ptr
  movl 4(%rsp), %eax
  # %9: ptr<u8> = offset %arg.ptr %j.2
  movl %eax, %ecx
  movq 8(%rsp), %rsi
  movslq %ecx, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rsi
  # %10: u8 = load %9
  movb 0(%rsi), %al
  # %11: ptr<FILE> = load $stdout
  movq stdout, %rcx
  # %12: i32 = call $fputc %10 %11
  movb %al, %dil
  movq %rcx, %rsi
  call fputc
  # %j.3: i32 = load %j.ptr
  movl 4(%rsp), %eax
  # %13: i32 = const 1
  # %14: i32 = add %j.3 %13
  movl %eax, %ecx
  add $0x1, %ecx
  # store %j.ptr %14
  movl %ecx, 4(%rsp)
  # jmp @4
  jmp .L__main__4
.L__main__5:
  # %i.2: i32 = load %i.ptr
  movl 16(%rsp), %eax
  # %argc.1: i32 = load %argc.ptr
  movl 28(%rsp), %ecx
  # %15: i32 = const 1
  # %16: i32 = sub %argc.1 %15
  movl %ecx, %edx
  sub $0x1, %edx
  # %17: bool = cmp_eq %i.2 %16
  cmp %edx, %eax
  sete %cl
  # br %17 @9 @10
  cmp $0x0, %cl
  jne .L__main__9
  jmp .L__main__10
.L__main__9:
  # jmp @3
  jmp .L__main__3
.L__main__10:
  # %18: u8 = const ' '
  # %19: ptr<FILE> = load $stdout
  movq stdout, %rax
  # %20: i32 = call $fputc %18 %19
  movb $0x20, %dil
  movq %rax, %rsi
  call fputc
  # %i.3: i32 = load %i.ptr
  movl 16(%rsp), %eax
  # %21: i32 = const 1
  # %22: i32 = add %i.3 %21
  movl %eax, %ecx
  add $0x1, %ecx
  # store %i.ptr %22
  movl %ecx, 16(%rsp)
  # jmp @2
  jmp .L__main__2
.L__main__3:
  # ret
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  xor %rax, %rax
  ret
