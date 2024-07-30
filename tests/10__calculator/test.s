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
  # %argc.1: i32 = load %argc.ptr
  movl 28(%rsp), %eax
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
  movq 20(%rsp), %rcx
  # %6: ptr<u8> = load %5
  movq 8(%rcx), %rax
  # %7: i32 = const 0
  # %8: Tokenizer = struct { Tokenizer.data: %6, Tokenizer.index: %7 }
  # %9: ptr<ptr<u8>> = offset %tokenizer.ptr Tokenizer.data
  lea 8(%rsp), %rcx
  # store %9 %6
  movq %rax, 0(%rcx)
  # %10: ptr<i32> = offset %tokenizer.ptr Tokenizer.index
  lea 8(%rsp), %rax
  # store %10 %7
  movl $0x0, 8(%rax)
  # jmp @4
  jmp .L__main__4
.L__main__4:
  # %11: bool = call $pTokenizer__has_next_token %tokenizer.ptr
  lea 8(%rsp), %rdi
  call pTokenizer__has_next_token
  # br %11 @5 @6
  cmp $0x0, %al
  jne .L__main__5
  jmp .L__main__6
.L__main__5:
  # %token.ptr: ptr<ptr<Token>> = alloc ptr<Token>
  # %12: ptr<Token> = call $pTokenizer__next_token %tokenizer.ptr
  lea 8(%rsp), %rdi
  call pTokenizer__next_token
  # store %token.ptr %12
  movq %rax, 0(%rsp)
  # %13: ptr<Token> = load %token.ptr
  movq 0(%rsp), %rax
  # %14: ptr<u8> = offset %13 Token.kind
  movq %rax, %rcx
  # %15: u8 = load %14
  movb 0(%rcx), %al
  # %16: u8 = const 0
  # %17: bool = cmp_eq %15 %16
  cmp $0x0, %al
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
  # %18: ptr<FILE> = load $stdout
  movq stdout, %rax
  # %token.1: ptr<Token> = load %token.ptr
  movq 0(%rsp), %rcx
  # %19: ptr<FILE> = call $pFILE__write__token %18 %token.1
  movq %rax, %rdi
  movq %rcx, %rsi
  call pFILE__write__token
  # %20: ptr<FILE> = call $pFILE__end_line %19
  movq %rax, %rdi
  call pFILE__end_line
  # jmp @4
  jmp .L__main__4
.L__main__E:
  add $0x20, %rsp
  xor %rax, %rax
  ret


pTokenizer__has_next_token:
.L__pTokenizer__has_next_token__S:
  sub $0x10, %rsp
.L__pTokenizer__has_next_token__1:
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
  jmp .L__pTokenizer__has_next_token__E
.L__pTokenizer__has_next_token__E:
  add $0x10, %rsp
  ret


pTokenizer__next_token:
.L__pTokenizer__next_token__S:
  sub $0x10, %rsp
.L__pTokenizer__next_token__1:
  # %self.ptr: ptr<ptr<Tokenizer>> = alloc ptr<Tokenizer>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %char.ptr: ptr<u8> = alloc u8
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
  # store %char.ptr %7
  movb %al, 7(%rsp)
  # %char.1: u8 = load %char.ptr
  movb 7(%rsp), %al
  # %8: u8 = const '0'
  # %9: bool = cmp_ge %char.1 %8
  cmp $0x30, %al
  setae %cl
  # br %9 @4 @5
  cmp $0x0, %cl
  jne .L__pTokenizer__next_token__4
  jmp .L__pTokenizer__next_token__5_F_1
.L__pTokenizer__next_token__4:
  # %char.2: u8 = load %char.ptr
  movb 7(%rsp), %al
  # %10: u8 = const '9'
  # %11: bool = cmp_le %char.2 %10
  cmp $0x39, %al
  setbe %cl
  # jmp @5
  jmp .L__pTokenizer__next_token__5_F_4
.L__pTokenizer__next_token__5:
  # %12: bool = phi @1 %9 @4 %11
  # br %12 @2 @3
  cmp $0x0, %cl
  jne .L__pTokenizer__next_token__2
  jmp .L__pTokenizer__next_token__3
.L__pTokenizer__next_token__5_F_1:
  jmp .L__pTokenizer__next_token__5
.L__pTokenizer__next_token__5_F_4:
  jmp .L__pTokenizer__next_token__5
.L__pTokenizer__next_token__2:
  # %self.1: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %13: ptr<Token> = call $pTokenizer__scan_number_token %self.1
  movq %rax, %rdi
  call pTokenizer__scan_number_token
  # ret %13
  jmp .L__pTokenizer__next_token__E
.L__pTokenizer__next_token__3:
  # %14: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %15: ptr<i32> = offset %14 Tokenizer.index
  movq %rax, %rcx
  # %16: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %17: ptr<i32> = offset %16 Tokenizer.index
  movq %rax, %rdx
  # %18: i32 = load %17
  movl 8(%rdx), %eax
  # %19: i32 = const 1
  # %20: i32 = add %18 %19
  movl %eax, %edx
  add $0x1, %edx
  # store %15 %20
  movl %edx, 8(%rcx)
  # %21: u64 = const 5
  # %22: ptr<Token> = call $malloc %21
  movq $0x5, %rdi
  call malloc
  # %char.3: u8 = load %char.ptr
  movb 7(%rsp), %cl
  # %23: i32 = const 0
  # %24: Token = struct { Token.kind: %char.3, Token.value: %23 }
  # %25: ptr<u8> = offset %22 Token.kind
  movq %rax, %rdx
  # store %25 %char.3
  movb %cl, 0(%rdx)
  # %26: ptr<i32> = offset %22 Token.value
  movq %rax, %rcx
  # store %26 %23
  movl $0x0, 1(%rcx)
  # ret %22
  jmp .L__pTokenizer__next_token__E
.L__pTokenizer__next_token__E:
  add $0x10, %rsp
  ret


pTokenizer__scan_number_token:
.L__pTokenizer__scan_number_token__S:
  sub $0x10, %rsp
.L__pTokenizer__scan_number_token__1:
  # %self.ptr: ptr<ptr<Tokenizer>> = alloc ptr<Tokenizer>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %value.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 0
  # store %value.ptr %1
  movl $0x0, 4(%rsp)
  # jmp @2
  jmp .L__pTokenizer__scan_number_token__2
.L__pTokenizer__scan_number_token__2:
  # %char.ptr: ptr<u8> = alloc u8
  # %2: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %3: ptr<ptr<u8>> = offset %2 Tokenizer.data
  movq %rax, %rcx
  # %4: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %5: ptr<i32> = offset %4 Tokenizer.index
  movq %rax, %rdx
  # %6: i32 = load %5
  movl 8(%rdx), %eax
  # %7: ptr<u8> = offset %3 %6
  movl %eax, %edx
  movl %edx, %esi
  movq 0(%rcx), %rdi
  movslq %esi, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  # %8: u8 = load %7
  movb 0(%rdi), %al
  # store %char.ptr %8
  movb %al, 3(%rsp)
  # %char.1: u8 = load %char.ptr
  movb 3(%rsp), %al
  # %9: u8 = const '0'
  # %10: bool = cmp_lt %char.1 %9
  cmp $0x30, %al
  setb %cl
  # br %10 @7 @6
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__7_F_2
  jmp .L__pTokenizer__scan_number_token__6
.L__pTokenizer__scan_number_token__7:
  # %13: bool = phi @2 %10 @6 %12
  # br %13 @4 @5
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__4
  jmp .L__pTokenizer__scan_number_token__5
.L__pTokenizer__scan_number_token__7_F_2:
  jmp .L__pTokenizer__scan_number_token__7
.L__pTokenizer__scan_number_token__6:
  # %char.2: u8 = load %char.ptr
  movb 3(%rsp), %al
  # %11: u8 = const '9'
  # %12: bool = cmp_gt %char.2 %11
  cmp $0x39, %al
  seta %cl
  # jmp @7
  jmp .L__pTokenizer__scan_number_token__7_F_6
.L__pTokenizer__scan_number_token__4:
  # jmp @3
  jmp .L__pTokenizer__scan_number_token__3
.L__pTokenizer__scan_number_token__5:
  # %value.1: i32 = load %value.ptr
  movl 4(%rsp), %eax
  # %14: i32 = const 10
  # %15: i32 = mul %value.1 %14
  movl %eax, %ecx
  movl %ecx, %eax
  movl $0xa, %esi
  mull %esi
  # %char.3: u8 = load %char.ptr
  movb 3(%rsp), %cl
  # %16: u8 = const '0'
  # %17: u8 = sub %char.3 %16
  movb %cl, %dl
  sub $0x30, %dl
  # %18: i32 = cast %17
  movb %dl, %cl
  movzbl %cl, %ecx
  # %19: i32 = add %15 %18
  movl %eax, %edx
  add %ecx, %edx
  # store %value.ptr %19
  movl %edx, 4(%rsp)
  # %20: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %21: ptr<i32> = offset %20 Tokenizer.index
  movq %rax, %rcx
  # %22: ptr<Tokenizer> = load %self.ptr
  movq 8(%rsp), %rax
  # %23: ptr<i32> = offset %22 Tokenizer.index
  movq %rax, %rdx
  # %24: i32 = load %23
  movl 8(%rdx), %eax
  # %25: i32 = const 1
  # %26: i32 = add %24 %25
  movl %eax, %edx
  add $0x1, %edx
  # store %21 %26
  movl %edx, 8(%rcx)
  # jmp @2
  jmp .L__pTokenizer__scan_number_token__2
.L__pTokenizer__scan_number_token__3:
  # %27: u64 = const 5
  # %28: ptr<Token> = call $malloc %27
  movq $0x5, %rdi
  call malloc
  # %29: u8 = const 'n'
  # %value.2: i32 = load %value.ptr
  movl 4(%rsp), %ecx
  # %30: Token = struct { Token.kind: %29, Token.value: %value.2 }
  # %31: ptr<u8> = offset %28 Token.kind
  movq %rax, %rdx
  # store %31 %29
  movb $0x6e, 0(%rdx)
  # %32: ptr<i32> = offset %28 Token.value
  movq %rax, %rdx
  # store %32 %value.2
  movl %ecx, 1(%rdx)
  # ret %28
  jmp .L__pTokenizer__scan_number_token__E
.L__pTokenizer__scan_number_token__7_F_6:
  jmp .L__pTokenizer__scan_number_token__7
.L__pTokenizer__scan_number_token__E:
  add $0x10, %rsp
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


pFILE__write__signed:
.L__pFILE__write__signed__S:
  sub $0x10, %rsp
.L__pFILE__write__signed__1:
  # %self.ptr: ptr<ptr<FILE>> = alloc ptr<FILE>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %value.ptr: ptr<i32> = alloc i32
  # store %value.ptr %value
  movl %esi, 4(%rsp)
  # %value.1: i32 = load %value.ptr
  movl 4(%rsp), %eax
  # %1: i32 = const 0
  # %2: bool = cmp_lt %value.1 %1
  cmp $0x0, %eax
  setl %cl
  # br %2 @2 @3
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__2
  jmp .L__pFILE__write__signed__3
.L__pFILE__write__signed__2:
  # %self.1: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # %3: u8 = const '-'
  # %4: ptr<FILE> = call $pFILE__write__char %self.1 %3
  movq %rax, %rdi
  movb $0x2d, %sil
  call pFILE__write__char
  # %self.2: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # %value.2: i32 = load %value.ptr
  movl 4(%rsp), %ecx
  # %5: i32 = neg %value.2
  movl %ecx, %edx
  neg %edx
  # %6: ptr<FILE> = call $pFILE__write__signed %self.2 %5
  movq %rax, %rdi
  movl %edx, %esi
  call pFILE__write__signed
  # ret %6
  jmp .L__pFILE__write__signed__E
.L__pFILE__write__signed__3:
  # %value.3: i32 = load %value.ptr
  movl 4(%rsp), %eax
  # %7: i32 = const 10
  # %8: bool = cmp_ge %value.3 %7
  cmp $0xa, %eax
  setge %cl
  # br %8 @4 @5
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__4
  jmp .L__pFILE__write__signed__5
.L__pFILE__write__signed__4:
  # %self.3: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # %value.4: i32 = load %value.ptr
  movl 4(%rsp), %ecx
  # %9: i32 = const 10
  # %10: i32 = div %value.4 %9
  movq %rax, %rdx
  movq %rdx, %rsi
  movl %ecx, %eax
  cltd
  movl $0xa, %edi
  idivl %edi
  # %11: ptr<FILE> = call $pFILE__write__signed %self.3 %10
  movq %rsi, %rdi
  movl %eax, %esi
  call pFILE__write__signed
  # jmp @5
  jmp .L__pFILE__write__signed__5
.L__pFILE__write__signed__5:
  # %self.4: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # %value.5: i32 = load %value.ptr
  movl 4(%rsp), %ecx
  # %12: i32 = const 10
  # %13: i32 = mod %value.5 %12
  movq %rax, %rdx
  movq %rdx, %rsi
  movl %ecx, %eax
  cltd
  movl $0xa, %edi
  idivl %edi
  # %14: u8 = cast %13
  movl %edx, %eax
  # %15: u8 = const '0'
  # %16: u8 = add %14 %15
  movb %al, %cl
  add $0x30, %cl
  # %17: ptr<FILE> = call $pFILE__write__char %self.4 %16
  movq %rsi, %rdi
  movb %cl, %sil
  call pFILE__write__char
  # ret %17
  jmp .L__pFILE__write__signed__E
.L__pFILE__write__signed__E:
  add $0x10, %rsp
  ret


pFILE__write__token:
.L__pFILE__write__token__S:
  sub $0x10, %rsp
.L__pFILE__write__token__1:
  # %self.ptr: ptr<ptr<FILE>> = alloc ptr<FILE>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %token.ptr: ptr<ptr<Token>> = alloc ptr<Token>
  # store %token.ptr %token
  movq %rsi, 0(%rsp)
  # %self.1: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # %1: ptr<Token> = load %token.ptr
  movq 0(%rsp), %rcx
  # %2: ptr<u8> = offset %1 Token.kind
  movq %rcx, %rdx
  # %3: u8 = load %2
  movb 0(%rdx), %cl
  # %4: ptr<FILE> = call $pFILE__write__char %self.1 %3
  movq %rax, %rdi
  movb %cl, %sil
  call pFILE__write__char
  # %5: ptr<Token> = load %token.ptr
  movq 0(%rsp), %rax
  # %6: ptr<u8> = offset %5 Token.kind
  movq %rax, %rcx
  # %7: u8 = load %6
  movb 0(%rcx), %al
  # %8: u8 = const 'n'
  # %9: bool = cmp_eq %7 %8
  cmp $0x6e, %al
  sete %cl
  # br %9 @2 @3
  cmp $0x0, %cl
  jne .L__pFILE__write__token__2
  jmp .L__pFILE__write__token__3
.L__pFILE__write__token__2:
  # %self.2: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # %10: u8 = const ':'
  # %11: ptr<FILE> = call $pFILE__write__char %self.2 %10
  movq %rax, %rdi
  movb $0x3a, %sil
  call pFILE__write__char
  # %12: u8 = const ' '
  # %13: ptr<FILE> = call $pFILE__write__char %11 %12
  movq %rax, %rdi
  movb $0x20, %sil
  call pFILE__write__char
  # %14: ptr<Token> = load %token.ptr
  movq 0(%rsp), %rcx
  # %15: ptr<i32> = offset %14 Token.value
  movq %rcx, %rdx
  # %16: i32 = load %15
  movl 1(%rdx), %ecx
  # %17: ptr<FILE> = call $pFILE__write__signed %13 %16
  movq %rax, %rdi
  movl %ecx, %esi
  call pFILE__write__signed
  # jmp @3
  jmp .L__pFILE__write__token__3
.L__pFILE__write__token__3:
  # %self.3: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # ret %self.3
  jmp .L__pFILE__write__token__E
.L__pFILE__write__token__E:
  add $0x10, %rsp
  ret


pFILE__end_line:
.L__pFILE__end_line__S:
  sub $0x10, %rsp
.L__pFILE__end_line__1:
  # %self.ptr: ptr<ptr<FILE>> = alloc ptr<FILE>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %self.1: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # %1: u8 = const '\n'
  # %2: ptr<FILE> = call $pFILE__write__char %self.1 %1
  movq %rax, %rdi
  movb $0xa, %sil
  call pFILE__write__char
  # %self.2: ptr<FILE> = load %self.ptr
  movq 8(%rsp), %rax
  # ret %self.2
  jmp .L__pFILE__end_line__E
.L__pFILE__end_line__E:
  add $0x10, %rsp
  ret
