.extern stdin

.extern stdout

.extern stderr

.globl main
main:
.L__main__S:
  sub $0x30, %rsp
.L__main__1:
  # %argc.ptr: ptr<i32> = alloc i32
  # store %argc.ptr %argc
  movl %edi, 44(%rsp)
  # %argv.ptr: ptr<ptr<ptr<u8>>> = alloc ptr<ptr<u8>>
  # store %argv.ptr %argv
  movq %rsi, 36(%rsp)
  # %argc.1: i32 = load %argc.ptr
  movl 44(%rsp), %eax
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
  # %tokenizer.ptr: ptr<Tokenizer> = alloc Tokenizer
  # %4: i32 = const 1
  # %5: ptr<ptr<u8>> = offset %argv.ptr %4
  movq 36(%rsp), %rcx
  # %6: ptr<u8> = load %5
  movq 8(%rcx), %rax
  # %7: i32 = const 0
  # %8: Tokenizer = struct { Tokenizer.data: %6, Tokenizer.index: %7 }
  # %9: ptr<ptr<u8>> = offset %tokenizer.ptr Tokenizer.data
  lea 24(%rsp), %rcx
  # store %9 %6
  movq %rax, 0(%rcx)
  # %10: ptr<i32> = offset %tokenizer.ptr Tokenizer.index
  lea 24(%rsp), %rax
  # store %10 %7
  movl $0x0, 8(%rax)
  # %tokenizer_ref.ptr: ptr<ptr<Tokenizer>> = alloc ptr<Tokenizer>
  # store %tokenizer_ref.ptr %tokenizer.ptr
  lea 24(%rsp), %rax
  movq %rax, 16(%rsp)
  # jmp @4
  jmp .L__main__4
.L__main__4:
  # %11: bool = call $has_next_token %tokenizer.ptr
  lea 24(%rsp), %rdi
  call has_next_token
  # br %11 @5 @6
  cmp $0x0, %al
  jne .L__main__5
  jmp .L__main__6
.L__main__5:
  # %token.ptr: ptr<ptr<Token>> = alloc ptr<Token>
  # %12: ptr<Token> = call $next_token %tokenizer.ptr
  lea 24(%rsp), %rdi
  call next_token
  # store %token.ptr %12
  movq %rax, 8(%rsp)
  # %13: ptr<Token> = load %token.ptr
  movq 8(%rsp), %rax
  # %14: ptr<i32> = offset %13 Token.kind
  movq %rax, %rcx
  # %15: i32 = load %14
  movl 0(%rcx), %eax
  # %16: i32 = const 0
  # %17: bool = cmp_eq %15 %16
  cmp $0x0, %eax
  sete %cl
  # br %17 @7 @8
  cmp $0x0, %cl
  jne .L__main__7
  jmp .L__main__8
.L__main__6:
  # ret
  jmp .L__main__E
.L__main__7:
  # jmp @6
  jmp .L__main__6
.L__main__8:
  # %18: ptr<Token> = load %token.ptr
  movq 8(%rsp), %rax
  # %19: ptr<u8> = offset %18 Token.value
  movq %rax, %rcx
  # %20: u8 = load %19
  movb 4(%rcx), %al
  # %21: ptr<FILE> = load $stdout
  movq stdout, %rcx
  # %22: i32 = call $fputc %20 %21
  movb %al, %dil
  movq %rcx, %rsi
  call fputc
  # jmp @4
  jmp .L__main__4
.L__main__E:
  add $0x30, %rsp
  xor %rax, %rax
  ret


has_next_token:
.L__has_next_token__S:
  sub $0x10, %rsp
.L__has_next_token__1:
  # %self.ptr: ptr<ptr<Tokenizer>> = alloc ptr<Tokenizer>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %1: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %2: ptr<ptr<u8>> = offset %1 Tokenizer.data
  movq %rax, %rcx
  # %3: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %4: ptr<i32> = offset %3 Tokenizer.index
  movq %rax, %rdx
  # %5: i32 = load %4
  movl 8(%rdx), %eax
  # %6: ptr<u8> = offset %2 %5
  movl %eax, %edx
  movl %edx, %esi
  movq 0(%rcx), %rdi
  movslq %esi, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  # %7: u8 = load %6
  movb 0(%rdi), %al
  # %8: u8 = const 0
  # %9: bool = cmp_ne %7 %8
  cmp $0x0, %al
  setne %cl
  # ret %9
  movb %cl, %al
  jmp .L__has_next_token__E
.L__has_next_token__E:
  add $0x10, %rsp
  ret


next_token:
.L__next_token__S:
  sub $0x10, %rsp
.L__next_token__1:
  # %self.ptr: ptr<ptr<Tokenizer>> = alloc ptr<Tokenizer>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %value.ptr: ptr<u8> = alloc u8
  # %1: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %2: ptr<ptr<u8>> = offset %1 Tokenizer.data
  movq %rax, %rcx
  # %3: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %4: ptr<i32> = offset %3 Tokenizer.index
  movq %rax, %rdx
  # %5: i32 = load %4
  movl 8(%rdx), %eax
  # %6: ptr<u8> = offset %2 %5
  movl %eax, %edx
  movl %edx, %esi
  movq 0(%rcx), %rdi
  movslq %esi, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  # %7: u8 = load %6
  movb 0(%rdi), %al
  # store %value.ptr %7
  movb %al, 7(%rsp)
  # %8: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %9: ptr<i32> = offset %8 Tokenizer.index
  movq %rax, %rcx
  # %10: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %11: ptr<i32> = offset %10 Tokenizer.index
  movq %rax, %rdx
  # %12: i32 = load %11
  movl 8(%rdx), %eax
  # %13: i32 = const 1
  # %14: i32 = add %12 %13
  movl %eax, %edx
  add $0x1, %edx
  # store %9 %14
  movl %edx, 8(%rcx)
  # %15: u64 = const 5
  # %16: ptr<Token> = call $malloc %15
  movq $0x5, %rdi
  call malloc
  # %17: i32 = const 1
  # %value.1: u8 = load %value.ptr
  movb 7(%rsp), %cl
  # %18: Token = struct { Token.kind: %17, Token.value: %value.1 }
  # %19: ptr<i32> = offset %16 Token.kind
  movq %rax, %rdx
  # store %19 %17
  movl $0x1, 0(%rdx)
  # %20: ptr<u8> = offset %16 Token.value
  movq %rax, %rdx
  # store %20 %value.1
  movb %cl, 4(%rdx)
  # ret %16
  jmp .L__next_token__E
.L__next_token__E:
  add $0x10, %rsp
  ret
