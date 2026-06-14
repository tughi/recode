.extern stdout

.globl main
main:
.L__main__S:
.L__main__1:
  # %1: ptr<FILE> = load $stdout
  movq stdout, %rax
  # %2: u8 = const '4'
  # %3: ptr<FILE> = call $pFILE__write__char %1 %2
  movq %rax, %rdi
  movb $0x34, %sil
  call pFILE__write__char
  # %4: u8 = const '2'
  # %5: ptr<FILE> = call $pFILE__write__char %3 %4
  movq %rax, %rdi
  movb $0x32, %sil
  call pFILE__write__char
  # %6: u8 = const '\n'
  # %7: ptr<FILE> = call $pFILE__write__char %5 %6
  movq %rax, %rdi
  movb $0xa, %sil
  call pFILE__write__char
  # ret
  jmp .L__main__E
.L__main__E:
  xor %rax, %rax
  ret


pFILE__write__char:
.L__pFILE__write__char__S:
  sub $0x10, %rsp
.L__pFILE__write__char__1:
  # %self.ptr: ptr<ptr<FILE>> = alloc ptr<FILE>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %char.ptr: ptr<u8> = alloc u8
  # store %char.ptr %char
  movb %sil, 7(%rsp)
  # %char.1: u8 = load %char.ptr
  movb 7(%rsp), %al
  # %1: ptr<FILE> = load $stdout
  movq stdout, %rcx
  # %2: i32 = call $fputc %char.1 %1
  movb %al, %dil
  movq %rcx, %rsi
  call fputc
  # %self.1: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # ret %self.1
  jmp .L__pFILE__write__char__E
.L__pFILE__write__char__E:
  add $0x10, %rsp
  ret
