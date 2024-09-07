.extern stdout

.globl main
main:
.L__main__S:
.L__main__1:
  # %1: u8 = const '4'
  # %2: ptr<File> = load $stdout
  movq stdout, %rax
  # %3: i32 = call $fputc %1 %2
  movb $0x34, %dil
  movq %rax, %rsi
  call fputc
  # %4: u8 = const '2'
  # %5: ptr<File> = load $stdout
  movq stdout, %rax
  # %6: i32 = call $fputc %4 %5
  movb $0x32, %dil
  movq %rax, %rsi
  call fputc
  # %7: u8 = const '\n'
  # %8: ptr<File> = load $stdout
  movq stdout, %rax
  # %9: i32 = call $fputc %7 %8
  movb $0xa, %dil
  movq %rax, %rsi
  call fputc
  # ret
  jmp .L__main__E
.L__main__E:
  xor %rax, %rax
  ret
