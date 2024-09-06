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
  # %stdout_writer.ptr: ptr<ptr<Writer>> = alloc ptr<Writer>
  # %11: u64 = const 16
  # %12: ptr<Writer> = call $malloc %11
  movq $0x10, %rdi
  call malloc
  # %13: ptr<FILE> = load $stdout
  movq stdout, %rcx
  # %14: ptr<func (self: ptr<FILE>, char: u8)> = address $pFILE__write_char
  # %15: Writer = struct { Writer.self: %13, Writer.write_char: %14 }
  # %16: ptr<ptr<Any>> = offset %12 Writer.self
  movq %rax, %rdx
  # store %16 %13
  movq %rcx, 0(%rdx)
  # %17: ptr<ptr<func (self: ptr<Any>, char: u8)>> = offset %12 Writer.write_char
  movq %rax, %rcx
  # store %17 %14
  lea pFILE__write_char, %rdx
  movq %rdx, 8(%rcx)
  # store %stdout_writer.ptr %12
  movq %rax, 16(%rsp)
  # jmp @4
  jmp .L__main__4
.L__main__4:
  # %18: bool = call $pTokenizer__has_next_token %tokenizer.ptr
  lea 24(%rsp), %rdi
  call pTokenizer__has_next_token
  # br %18 @5 @6
  cmp $0x0, %al
  jne .L__main__5
  jmp .L__main__6
.L__main__5:
  # %token.ptr: ptr<ptr<Token>> = alloc ptr<Token>
  # %19: ptr<Token> = call $pTokenizer__next_token %tokenizer.ptr
  lea 24(%rsp), %rdi
  call pTokenizer__next_token
  # store %token.ptr %19
  movq %rax, 8(%rsp)
  # %20: ptr<Token> = load %token.ptr
  movq 8(%rsp), %rax
  # %21: ptr<u8> = offset %20 Token.kind
  movq %rax, %rcx
  # %22: u8 = load %21
  movb 0(%rcx), %al
  # %23: u8 = const 0
  # %24: bool = cmp_eq %22 %23
  cmp $0x0, %al
  sete %cl
  # br %24 @7 @8
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
  # %stdout_writer.1: ptr<Writer> = load %stdout_writer.ptr
  movq 16(%rsp), %rax
  # %token.1: ptr<Token> = load %token.ptr
  movq 8(%rsp), %rcx
  # %25: ptr<Writer> = call $pWriter__write__token %stdout_writer.1 %token.1
  movq %rax, %rdi
  movq %rcx, %rsi
  call pWriter__write__token
  # %26: ptr<Writer> = call $pWriter__end_line %25
  movq %rax, %rdi
  call pWriter__end_line
  # jmp @4
  jmp .L__main__4
.L__main__E:
  add $0x30, %rsp
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
  pushq %rbx
  pushq %rbp
  sub $0x20, %rsp
.L__pTokenizer__next_token__1:
  # %self.ptr: ptr<ptr<Tokenizer>> = alloc ptr<Tokenizer>
  # store %self.ptr %self
  movq %rdi, 24(%rsp)
  # %lexeme_builder.ptr: ptr<StringBuilder> = alloc StringBuilder
  # %1: u64 = const 4
  # %2: ptr<Any> = call $malloc %1
  movq $0x4, %rdi
  call malloc
  # %3: ptr<u8> = cast %2
  movq %rax, %rcx
  # %4: i32 = const 4
  # %5: i32 = const 0
  # %6: StringBuilder = struct { StringBuilder.data: %3, StringBuilder.data_size: %4, StringBuilder.length: %5 }
  # %7: ptr<ptr<u8>> = offset %lexeme_builder.ptr StringBuilder.data
  lea 8(%rsp), %rax
  # store %7 %3
  movq %rcx, 0(%rax)
  # %8: ptr<i32> = offset %lexeme_builder.ptr StringBuilder.data_size
  lea 8(%rsp), %rax
  # store %8 %4
  movl $0x4, 8(%rax)
  # %9: ptr<i32> = offset %lexeme_builder.ptr StringBuilder.length
  lea 8(%rsp), %rax
  # store %9 %5
  movl $0x0, 12(%rax)
  # %char.ptr: ptr<u8> = alloc u8
  # %10: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %11: ptr<ptr<u8>> = offset %10 Tokenizer.data
  movq %rax, %rcx
  # %12: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %13: ptr<i32> = offset %12 Tokenizer.index
  movq %rax, %rdx
  # %14: i32 = load %13
  movl 8(%rdx), %eax
  # %15: ptr<u8> = offset %11 %14
  movl %eax, %edx
  movl %edx, %esi
  movq 0(%rcx), %rdi
  movslq %esi, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  # %16: u8 = load %15
  movb 0(%rdi), %al
  # store %char.ptr %16
  movb %al, 7(%rsp)
  # %char.1: u8 = load %char.ptr
  movb 7(%rsp), %al
  # %17: u8 = const '0'
  # %18: bool = cmp_ge %char.1 %17
  cmp $0x30, %al
  setae %cl
  # br %18 @4 @5
  cmp $0x0, %cl
  jne .L__pTokenizer__next_token__4
  jmp .L__pTokenizer__next_token__5_F_1
.L__pTokenizer__next_token__4:
  # %char.2: u8 = load %char.ptr
  movb 7(%rsp), %al
  # %19: u8 = const '9'
  # %20: bool = cmp_le %char.2 %19
  cmp $0x39, %al
  setbe %cl
  # jmp @5
  jmp .L__pTokenizer__next_token__5_F_4
.L__pTokenizer__next_token__5:
  # %21: bool = phi @1 %18 @4 %20
  # br %21 @2 @3
  cmp $0x0, %cl
  jne .L__pTokenizer__next_token__2
  jmp .L__pTokenizer__next_token__3
.L__pTokenizer__next_token__5_F_1:
  jmp .L__pTokenizer__next_token__5
.L__pTokenizer__next_token__5_F_4:
  jmp .L__pTokenizer__next_token__5
.L__pTokenizer__next_token__2:
  # %self.1: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %22: ptr<Token> = call $pTokenizer__scan_number_token %self.1 %lexeme_builder.ptr
  movq %rax, %rdi
  lea 8(%rsp), %rsi
  call pTokenizer__scan_number_token
  # ret %22
  jmp .L__pTokenizer__next_token__E
.L__pTokenizer__next_token__3:
  # %23: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %24: ptr<i32> = offset %23 Tokenizer.index
  movq %rax, %rcx
  # %25: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %26: ptr<i32> = offset %25 Tokenizer.index
  movq %rax, %rdx
  # %27: i32 = load %26
  movl 8(%rdx), %eax
  # %28: i32 = const 1
  # %29: i32 = add %27 %28
  movl %eax, %edx
  add $0x1, %edx
  # store %24 %29
  movl %edx, 8(%rcx)
  # %30: u64 = const 13
  # %31: ptr<Token> = call $malloc %30
  movq $0xd, %rdi
  call malloc
  # %char.3: u8 = load %char.ptr
  movb 7(%rsp), %cl
  # %char.4: u8 = load %char.ptr
  movb 7(%rsp), %dl
  # %32: ptr<StringBuilder> = call $pStringBuilder__write__char %lexeme_builder.ptr %char.4
  movq %rax, %rbx
  movb %cl, %bpl
  lea 8(%rsp), %rdi
  movb %dl, %sil
  call pStringBuilder__write__char
  # %33: ptr<u8> = call $pStringBuilder__build %32
  movq %rax, %rdi
  call pStringBuilder__build
  # %34: i32 = const 0
  # %35: Token = struct { Token.kind: %char.3, Token.lexeme: %33, Token.value: %34 }
  # %36: ptr<u8> = offset %31 Token.kind
  movq %rbx, %rcx
  # store %36 %char.3
  movb %bpl, 0(%rcx)
  # %37: ptr<ptr<u8>> = offset %31 Token.lexeme
  movq %rbx, %rcx
  # store %37 %33
  movq %rax, 1(%rcx)
  # %38: ptr<i32> = offset %31 Token.value
  movq %rbx, %rax
  # store %38 %34
  movl $0x0, 9(%rax)
  # ret %31
  movq %rbx, %rax
  jmp .L__pTokenizer__next_token__E
.L__pTokenizer__next_token__E:
  add $0x20, %rsp
  popq %rbp
  popq %rbx
  ret


pTokenizer__scan_number_token:
.L__pTokenizer__scan_number_token__S:
  pushq %rbx
  sub $0x20, %rsp
.L__pTokenizer__scan_number_token__1:
  # %self.ptr: ptr<ptr<Tokenizer>> = alloc ptr<Tokenizer>
  # store %self.ptr %self
  movq %rdi, 24(%rsp)
  # %lexeme_builder.ptr: ptr<ptr<StringBuilder>> = alloc ptr<StringBuilder>
  # store %lexeme_builder.ptr %lexeme_builder
  movq %rsi, 16(%rsp)
  # %value.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 0
  # store %value.ptr %1
  movl $0x0, 12(%rsp)
  # jmp @2
  jmp .L__pTokenizer__scan_number_token__2
.L__pTokenizer__scan_number_token__2:
  # %char.ptr: ptr<u8> = alloc u8
  # %2: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %3: ptr<ptr<u8>> = offset %2 Tokenizer.data
  movq %rax, %rcx
  # %4: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
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
  movb %al, 11(%rsp)
  # %char.1: u8 = load %char.ptr
  movb 11(%rsp), %al
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
  movb 11(%rsp), %al
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
  # %lexeme_builder.1: ptr<StringBuilder> = load %lexeme_builder.ptr
  movq 16(%rsp), %rax
  # %char.3: u8 = load %char.ptr
  movb 11(%rsp), %cl
  # %14: ptr<StringBuilder> = call $pStringBuilder__write__char %lexeme_builder.1 %char.3
  movq %rax, %rdi
  movb %cl, %sil
  call pStringBuilder__write__char
  # %value.1: i32 = load %value.ptr
  movl 12(%rsp), %eax
  # %15: i32 = const 10
  # %16: i32 = mul %value.1 %15
  movl %eax, %ecx
  movl %ecx, %eax
  movl $0xa, %esi
  mull %esi
  # %char.4: u8 = load %char.ptr
  movb 11(%rsp), %cl
  # %17: u8 = const '0'
  # %18: u8 = sub %char.4 %17
  movb %cl, %dl
  sub $0x30, %dl
  # %19: i32 = cast %18
  movb %dl, %cl
  movzbl %cl, %ecx
  # %20: i32 = add %16 %19
  movl %eax, %edx
  add %ecx, %edx
  # store %value.ptr %20
  movl %edx, 12(%rsp)
  # %21: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %22: ptr<i32> = offset %21 Tokenizer.index
  movq %rax, %rcx
  # %23: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %24: ptr<i32> = offset %23 Tokenizer.index
  movq %rax, %rdx
  # %25: i32 = load %24
  movl 8(%rdx), %eax
  # %26: i32 = const 1
  # %27: i32 = add %25 %26
  movl %eax, %edx
  add $0x1, %edx
  # store %22 %27
  movl %edx, 8(%rcx)
  # jmp @2
  jmp .L__pTokenizer__scan_number_token__2
.L__pTokenizer__scan_number_token__3:
  # %28: u64 = const 13
  # %29: ptr<Token> = call $malloc %28
  movq $0xd, %rdi
  call malloc
  # %30: u8 = const 'n'
  # %lexeme_builder.2: ptr<StringBuilder> = load %lexeme_builder.ptr
  movq 16(%rsp), %rcx
  # %31: ptr<u8> = call $pStringBuilder__build %lexeme_builder.2
  movq %rax, %rbx
  movq %rcx, %rdi
  call pStringBuilder__build
  # %value.2: i32 = load %value.ptr
  movl 12(%rsp), %ecx
  # %32: Token = struct { Token.kind: %30, Token.lexeme: %31, Token.value: %value.2 }
  # %33: ptr<u8> = offset %29 Token.kind
  movq %rbx, %rdx
  # store %33 %30
  movb $0x6e, 0(%rdx)
  # %34: ptr<ptr<u8>> = offset %29 Token.lexeme
  movq %rbx, %rdx
  # store %34 %31
  movq %rax, 1(%rdx)
  # %35: ptr<i32> = offset %29 Token.value
  movq %rbx, %rax
  # store %35 %value.2
  movl %ecx, 9(%rax)
  # ret %29
  movq %rbx, %rax
  jmp .L__pTokenizer__scan_number_token__E
.L__pTokenizer__scan_number_token__7_F_6:
  jmp .L__pTokenizer__scan_number_token__7
.L__pTokenizer__scan_number_token__E:
  add $0x20, %rsp
  popq %rbx
  ret


pWriter__write__token:
.L__pWriter__write__token__S:
  sub $0x10, %rsp
.L__pWriter__write__token__1:
  # %self.ptr: ptr<ptr<Writer>> = alloc ptr<Writer>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %token.ptr: ptr<ptr<Token>> = alloc ptr<Token>
  # store %token.ptr %token
  movq %rsi, 0(%rsp)
  # %self.1: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # %1: ptr<Token> = load %token.ptr
  movq 0(%rsp), %rcx
  # %2: ptr<u8> = offset %1 Token.kind
  movq %rcx, %rdx
  # %3: u8 = load %2
  movb 0(%rdx), %cl
  # %4: ptr<Writer> = call $pWriter__write__char %self.1 %3
  movq %rax, %rdi
  movb %cl, %sil
  call pWriter__write__char
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
  jne .L__pWriter__write__token__2
  jmp .L__pWriter__write__token__3
.L__pWriter__write__token__2:
  # %self.2: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # %10: u8 = const ':'
  # %11: ptr<Writer> = call $pWriter__write__char %self.2 %10
  movq %rax, %rdi
  movb $0x3a, %sil
  call pWriter__write__char
  # %12: u8 = const ' '
  # %13: ptr<Writer> = call $pWriter__write__char %11 %12
  movq %rax, %rdi
  movb $0x20, %sil
  call pWriter__write__char
  # %14: ptr<Token> = load %token.ptr
  movq 0(%rsp), %rcx
  # %15: ptr<i32> = offset %14 Token.value
  movq %rcx, %rdx
  # %16: i32 = load %15
  movl 9(%rdx), %ecx
  # %17: ptr<Writer> = call $pWriter__write__signed %13 %16
  movq %rax, %rdi
  movl %ecx, %esi
  call pWriter__write__signed
  # jmp @3
  jmp .L__pWriter__write__token__3
.L__pWriter__write__token__3:
  # %self.3: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # ret %self.3
  jmp .L__pWriter__write__token__E
.L__pWriter__write__token__E:
  add $0x10, %rsp
  ret


pStringBuilder__write__char:
.L__pStringBuilder__write__char__S:
  pushq %rbx
  sub $0x10, %rsp
.L__pStringBuilder__write__char__1:
  # %self.ptr: ptr<ptr<StringBuilder>> = alloc ptr<StringBuilder>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %char.ptr: ptr<u8> = alloc u8
  # store %char.ptr %char
  movb %sil, 7(%rsp)
  # %1: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %2: ptr<i32> = offset %1 StringBuilder.length
  movq %rax, %rcx
  # %3: i32 = load %2
  movl 12(%rcx), %eax
  # %4: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rcx
  # %5: ptr<i32> = offset %4 StringBuilder.data_size
  movq %rcx, %rdx
  # %6: i32 = load %5
  movl 8(%rdx), %ecx
  # %7: bool = cmp_eq %3 %6
  cmp %ecx, %eax
  sete %dl
  # br %7 @2 @3
  cmp $0x0, %dl
  jne .L__pStringBuilder__write__char__2
  jmp .L__pStringBuilder__write__char__3
.L__pStringBuilder__write__char__2:
  # %8: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %9: ptr<i32> = offset %8 StringBuilder.data_size
  movq %rax, %rcx
  # %10: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %11: ptr<i32> = offset %10 StringBuilder.data_size
  movq %rax, %rdx
  # %12: i32 = load %11
  movl 8(%rdx), %eax
  # %13: i32 = const 8
  # %14: i32 = add %12 %13
  movl %eax, %edx
  add $0x8, %edx
  # store %9 %14
  movl %edx, 8(%rcx)
  # %15: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %16: ptr<ptr<u8>> = offset %15 StringBuilder.data
  movq %rax, %rcx
  # %17: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %18: ptr<ptr<u8>> = offset %17 StringBuilder.data
  movq %rax, %rdx
  # %19: ptr<u8> = load %18
  movq 0(%rdx), %rax
  # %20: ptr<Any> = cast %19
  movq %rax, %rdx
  # %21: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %22: ptr<i32> = offset %21 StringBuilder.data_size
  movq %rax, %rsi
  # %23: i32 = load %22
  movl 8(%rsi), %eax
  # %24: u64 = cast %23
  movl %eax, %esi
  # %25: ptr<Any> = call $realloc %20 %24
  movq %rcx, %rbx
  movq %rdx, %rdi
  movq %rsi, %rax
  movq %rax, %rsi
  call realloc
  # %26: ptr<u8> = cast %25
  movq %rax, %rcx
  # store %16 %26
  movq %rcx, 0(%rbx)
  # jmp @3
  jmp .L__pStringBuilder__write__char__3
.L__pStringBuilder__write__char__3:
  # %27: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %28: ptr<ptr<u8>> = offset %27 StringBuilder.data
  movq %rax, %rcx
  # %29: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %30: ptr<i32> = offset %29 StringBuilder.length
  movq %rax, %rdx
  # %31: i32 = load %30
  movl 12(%rdx), %eax
  # %32: ptr<u8> = offset %28 %31
  movl %eax, %edx
  movl %edx, %esi
  movq 0(%rcx), %rdi
  movslq %esi, %rax
  cqo
  imulq $0x1, %rax
  add %rax, %rdi
  # %char.1: u8 = load %char.ptr
  movb 7(%rsp), %al
  # store %32 %char.1
  movb %al, 0(%rdi)
  # %33: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %34: ptr<i32> = offset %33 StringBuilder.length
  movq %rax, %rcx
  # %35: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %36: ptr<i32> = offset %35 StringBuilder.length
  movq %rax, %rdx
  # %37: i32 = load %36
  movl 12(%rdx), %eax
  # %38: i32 = const 1
  # %39: i32 = add %37 %38
  movl %eax, %edx
  add $0x1, %edx
  # store %34 %39
  movl %edx, 12(%rcx)
  # %self.1: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # ret %self.1
  jmp .L__pStringBuilder__write__char__E
.L__pStringBuilder__write__char__E:
  add $0x10, %rsp
  popq %rbx
  ret


pStringBuilder__build:
.L__pStringBuilder__build__S:
  sub $0x10, %rsp
.L__pStringBuilder__build__1:
  # %self.ptr: ptr<ptr<StringBuilder>> = alloc ptr<StringBuilder>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %self.1: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %1: u8 = const 0
  # %2: ptr<StringBuilder> = call $pStringBuilder__write__char %self.1 %1
  movq %rax, %rdi
  movb $0x0, %sil
  call pStringBuilder__write__char
  # %3: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %4: ptr<ptr<u8>> = offset %3 StringBuilder.data
  movq %rax, %rcx
  # %5: ptr<u8> = load %4
  movq 0(%rcx), %rax
  # ret %5
  jmp .L__pStringBuilder__build__E
.L__pStringBuilder__build__E:
  add $0x10, %rsp
  ret


pStringBuilder__write_char:
.L__pStringBuilder__write_char__S:
  sub $0x10, %rsp
.L__pStringBuilder__write_char__1:
  # %self.ptr: ptr<ptr<StringBuilder>> = alloc ptr<StringBuilder>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %char.ptr: ptr<u8> = alloc u8
  # store %char.ptr %char
  movb %sil, 7(%rsp)
  # %self.1: ptr<StringBuilder> = load %self.ptr
  movq 8(%rsp), %rax
  # %char.1: u8 = load %char.ptr
  movb 7(%rsp), %cl
  # %1: ptr<StringBuilder> = call $pStringBuilder__write__char %self.1 %char.1
  movq %rax, %rdi
  movb %cl, %sil
  call pStringBuilder__write__char
  # ret
  jmp .L__pStringBuilder__write_char__E
.L__pStringBuilder__write_char__E:
  add $0x10, %rsp
  ret


pWriter__write__char:
.L__pWriter__write__char__S:
  sub $0x10, %rsp
.L__pWriter__write__char__1:
  # %self.ptr: ptr<ptr<Writer>> = alloc ptr<Writer>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %char.ptr: ptr<u8> = alloc u8
  # store %char.ptr %char
  movb %sil, 7(%rsp)
  # %self.1: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # %1: ptr<ptr<func (self: ptr<Any>, char: u8)>> = offset %self.1 Writer.write_char
  movq %rax, %rcx
  # %2: ptr<func (self: ptr<Any>, char: u8)> = load %1
  movq 8(%rcx), %rdx
  # %3: ptr<ptr<Any>> = offset %self.1 Writer.self
  movq %rax, %rcx
  # %4: ptr<Any> = load %3
  movq 0(%rcx), %rax
  # %char.1: u8 = load %char.ptr
  movb 7(%rsp), %cl
  # call %2 %4 %char.1
  movq %rax, %rdi
  movb %cl, %sil
  call *%rdx
  # %self.2: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # ret %self.2
  jmp .L__pWriter__write__char__E
.L__pWriter__write__char__E:
  add $0x10, %rsp
  ret


pWriter__write__signed:
.L__pWriter__write__signed__S:
  sub $0x10, %rsp
.L__pWriter__write__signed__1:
  # %self.ptr: ptr<ptr<Writer>> = alloc ptr<Writer>
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
  jne .L__pWriter__write__signed__2
  jmp .L__pWriter__write__signed__3
.L__pWriter__write__signed__2:
  # %self.1: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # %3: u8 = const '-'
  # %4: ptr<Writer> = call $pWriter__write__char %self.1 %3
  movq %rax, %rdi
  movb $0x2d, %sil
  call pWriter__write__char
  # %self.2: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # %value.2: i32 = load %value.ptr
  movl 4(%rsp), %ecx
  # %5: i32 = neg %value.2
  movl %ecx, %edx
  neg %edx
  # %6: ptr<Writer> = call $pWriter__write__signed %self.2 %5
  movq %rax, %rdi
  movl %edx, %esi
  call pWriter__write__signed
  # ret %6
  jmp .L__pWriter__write__signed__E
.L__pWriter__write__signed__3:
  # %value.3: i32 = load %value.ptr
  movl 4(%rsp), %eax
  # %7: i32 = const 10
  # %8: bool = cmp_ge %value.3 %7
  cmp $0xa, %eax
  setge %cl
  # br %8 @4 @5
  cmp $0x0, %cl
  jne .L__pWriter__write__signed__4
  jmp .L__pWriter__write__signed__5
.L__pWriter__write__signed__4:
  # %self.3: ptr<Writer> = load %self.ptr
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
  # %11: ptr<Writer> = call $pWriter__write__signed %self.3 %10
  movq %rsi, %rdi
  movl %eax, %esi
  call pWriter__write__signed
  # jmp @5
  jmp .L__pWriter__write__signed__5
.L__pWriter__write__signed__5:
  # %self.4: ptr<Writer> = load %self.ptr
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
  # %17: ptr<Writer> = call $pWriter__write__char %self.4 %16
  movq %rsi, %rdi
  movb %cl, %sil
  call pWriter__write__char
  # ret %17
  jmp .L__pWriter__write__signed__E
.L__pWriter__write__signed__E:
  add $0x10, %rsp
  ret


pWriter__end_line:
.L__pWriter__end_line__S:
  sub $0x10, %rsp
.L__pWriter__end_line__1:
  # %self.ptr: ptr<ptr<Writer>> = alloc ptr<Writer>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %self.1: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # %1: u8 = const '\n'
  # %2: ptr<Writer> = call $pWriter__write__char %self.1 %1
  movq %rax, %rdi
  movb $0xa, %sil
  call pWriter__write__char
  # %self.2: ptr<Writer> = load %self.ptr
  movq 8(%rsp), %rax
  # ret %self.2
  jmp .L__pWriter__end_line__E
.L__pWriter__end_line__E:
  add $0x10, %rsp
  ret


pFILE__write_char:
.L__pFILE__write_char__S:
  sub $0x10, %rsp
.L__pFILE__write_char__1:
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
  # ret
  jmp .L__pFILE__write_char__E
.L__pFILE__write_char__E:
  add $0x10, %rsp
  ret
