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
  sub $0x20, %rsp
.L__pTokenizer__scan_number_token__1:
  # %self.ptr: ptr<ptr<Tokenizer>> = alloc ptr<Tokenizer>
  # store %self.ptr %self
  movq %rdi, 24(%rsp)
  # %value.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 0
  # store %value.ptr %1
  movl $0x0, 20(%rsp)
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
  movb %al, 19(%rsp)
  # %digit.ptr: ptr<i32> = alloc i32
  # %char.1: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %9: u8 = const '0'
  # %10: bool = cmp_eq %char.1 %9
  cmp $0x30, %al
  sete %cl
  # br %10 @4 @5
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__4
  jmp .L__pTokenizer__scan_number_token__5
.L__pTokenizer__scan_number_token__4:
  # %11: i32 = const 0
  # store %digit.ptr %11
  movl $0x0, 15(%rsp)
  # jmp @6
  jmp .L__pTokenizer__scan_number_token__6
.L__pTokenizer__scan_number_token__5:
  # %char.2: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %12: u8 = const '1'
  # %13: bool = cmp_eq %char.2 %12
  cmp $0x31, %al
  sete %cl
  # br %13 @7 @8
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__7
  jmp .L__pTokenizer__scan_number_token__8
.L__pTokenizer__scan_number_token__6:
  # %value.1: i32 = load %value.ptr
  movl 20(%rsp), %eax
  # %39: i32 = const 10
  # %40: i32 = mul %value.1 %39
  movl %eax, %ecx
  movl %ecx, %eax
  movl $0xa, %esi
  mull %esi
  # %digit.1: i32 = load %digit.ptr
  movl 15(%rsp), %ecx
  # %41: i32 = add %40 %digit.1
  movl %eax, %edx
  add %ecx, %edx
  # store %value.ptr %41
  movl %edx, 20(%rsp)
  # %42: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %43: ptr<i32> = offset %42 Tokenizer.index
  movq %rax, %rcx
  # %44: ptr<Tokenizer> = load %self.ptr
  movq 24(%rsp), %rax
  # %45: ptr<i32> = offset %44 Tokenizer.index
  movq %rax, %rdx
  # %46: i32 = load %45
  movl 8(%rdx), %eax
  # %47: i32 = const 1
  # %48: i32 = add %46 %47
  movl %eax, %edx
  add $0x1, %edx
  # store %43 %48
  movl %edx, 8(%rcx)
  # jmp @2
  jmp .L__pTokenizer__scan_number_token__2
.L__pTokenizer__scan_number_token__7:
  # %14: i32 = const 1
  # store %digit.ptr %14
  movl $0x1, 15(%rsp)
  # jmp @9
  jmp .L__pTokenizer__scan_number_token__9
.L__pTokenizer__scan_number_token__8:
  # %char.3: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %15: u8 = const '2'
  # %16: bool = cmp_eq %char.3 %15
  cmp $0x32, %al
  sete %cl
  # br %16 @10 @11
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__10
  jmp .L__pTokenizer__scan_number_token__11
.L__pTokenizer__scan_number_token__9:
  # jmp @6
  jmp .L__pTokenizer__scan_number_token__6
.L__pTokenizer__scan_number_token__10:
  # %17: i32 = const 2
  # store %digit.ptr %17
  movl $0x2, 15(%rsp)
  # jmp @12
  jmp .L__pTokenizer__scan_number_token__12
.L__pTokenizer__scan_number_token__11:
  # %char.4: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %18: u8 = const '3'
  # %19: bool = cmp_eq %char.4 %18
  cmp $0x33, %al
  sete %cl
  # br %19 @13 @14
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__13
  jmp .L__pTokenizer__scan_number_token__14
.L__pTokenizer__scan_number_token__12:
  # jmp @9
  jmp .L__pTokenizer__scan_number_token__9
.L__pTokenizer__scan_number_token__13:
  # %20: i32 = const 3
  # store %digit.ptr %20
  movl $0x3, 15(%rsp)
  # jmp @15
  jmp .L__pTokenizer__scan_number_token__15
.L__pTokenizer__scan_number_token__14:
  # %char.5: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %21: u8 = const '4'
  # %22: bool = cmp_eq %char.5 %21
  cmp $0x34, %al
  sete %cl
  # br %22 @16 @17
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__16
  jmp .L__pTokenizer__scan_number_token__17
.L__pTokenizer__scan_number_token__15:
  # jmp @12
  jmp .L__pTokenizer__scan_number_token__12
.L__pTokenizer__scan_number_token__16:
  # %23: i32 = const 4
  # store %digit.ptr %23
  movl $0x4, 15(%rsp)
  # jmp @18
  jmp .L__pTokenizer__scan_number_token__18
.L__pTokenizer__scan_number_token__17:
  # %char.6: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %24: u8 = const '5'
  # %25: bool = cmp_eq %char.6 %24
  cmp $0x35, %al
  sete %cl
  # br %25 @19 @20
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__19
  jmp .L__pTokenizer__scan_number_token__20
.L__pTokenizer__scan_number_token__18:
  # jmp @15
  jmp .L__pTokenizer__scan_number_token__15
.L__pTokenizer__scan_number_token__19:
  # %26: i32 = const 5
  # store %digit.ptr %26
  movl $0x5, 15(%rsp)
  # jmp @21
  jmp .L__pTokenizer__scan_number_token__21
.L__pTokenizer__scan_number_token__20:
  # %char.7: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %27: u8 = const '6'
  # %28: bool = cmp_eq %char.7 %27
  cmp $0x36, %al
  sete %cl
  # br %28 @22 @23
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__22
  jmp .L__pTokenizer__scan_number_token__23
.L__pTokenizer__scan_number_token__21:
  # jmp @18
  jmp .L__pTokenizer__scan_number_token__18
.L__pTokenizer__scan_number_token__22:
  # %29: i32 = const 6
  # store %digit.ptr %29
  movl $0x6, 15(%rsp)
  # jmp @24
  jmp .L__pTokenizer__scan_number_token__24
.L__pTokenizer__scan_number_token__23:
  # %char.8: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %30: u8 = const '7'
  # %31: bool = cmp_eq %char.8 %30
  cmp $0x37, %al
  sete %cl
  # br %31 @25 @26
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__25
  jmp .L__pTokenizer__scan_number_token__26
.L__pTokenizer__scan_number_token__24:
  # jmp @21
  jmp .L__pTokenizer__scan_number_token__21
.L__pTokenizer__scan_number_token__25:
  # %32: i32 = const 7
  # store %digit.ptr %32
  movl $0x7, 15(%rsp)
  # jmp @27
  jmp .L__pTokenizer__scan_number_token__27
.L__pTokenizer__scan_number_token__26:
  # %char.9: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %33: u8 = const '8'
  # %34: bool = cmp_eq %char.9 %33
  cmp $0x38, %al
  sete %cl
  # br %34 @28 @29
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__28
  jmp .L__pTokenizer__scan_number_token__29
.L__pTokenizer__scan_number_token__27:
  # jmp @24
  jmp .L__pTokenizer__scan_number_token__24
.L__pTokenizer__scan_number_token__28:
  # %35: i32 = const 8
  # store %digit.ptr %35
  movl $0x8, 15(%rsp)
  # jmp @30
  jmp .L__pTokenizer__scan_number_token__30
.L__pTokenizer__scan_number_token__29:
  # %char.10: u8 = load %char.ptr
  movb 19(%rsp), %al
  # %36: u8 = const '9'
  # %37: bool = cmp_eq %char.10 %36
  cmp $0x39, %al
  sete %cl
  # br %37 @31 @32
  cmp $0x0, %cl
  jne .L__pTokenizer__scan_number_token__31
  jmp .L__pTokenizer__scan_number_token__32
.L__pTokenizer__scan_number_token__30:
  # jmp @27
  jmp .L__pTokenizer__scan_number_token__27
.L__pTokenizer__scan_number_token__31:
  # %38: i32 = const 9
  # store %digit.ptr %38
  movl $0x9, 15(%rsp)
  # jmp @33
  jmp .L__pTokenizer__scan_number_token__33
.L__pTokenizer__scan_number_token__32:
  # jmp @3
  jmp .L__pTokenizer__scan_number_token__3
.L__pTokenizer__scan_number_token__33:
  # jmp @30
  jmp .L__pTokenizer__scan_number_token__30
.L__pTokenizer__scan_number_token__3:
  # %49: u64 = const 5
  # %50: ptr<Token> = call $malloc %49
  movq $0x5, %rdi
  call malloc
  # %51: u8 = const 'n'
  # %value.2: i32 = load %value.ptr
  movl 20(%rsp), %ecx
  # %52: Token = struct { Token.kind: %51, Token.value: %value.2 }
  # %53: ptr<u8> = offset %50 Token.kind
  movq %rax, %rdx
  # store %53 %51
  movb $0x6e, 0(%rdx)
  # %54: ptr<i32> = offset %50 Token.value
  movq %rax, %rdx
  # store %54 %value.2
  movl %ecx, 1(%rdx)
  # ret %50
  jmp .L__pTokenizer__scan_number_token__E
.L__pTokenizer__scan_number_token__E:
  add $0x20, %rsp
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
  sub $0x20, %rsp
.L__pFILE__write__signed__1:
  # %self.ptr: ptr<ptr<FILE>> = alloc ptr<FILE>
  # store %self.ptr %self
  movq %rdi, 24(%rsp)
  # %value.ptr: ptr<i32> = alloc i32
  # store %value.ptr %value
  movl %esi, 20(%rsp)
  # %value.1: i32 = load %value.ptr
  movl 20(%rsp), %eax
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
  movq 24(%rsp), %rax
  # %3: u8 = const '-'
  # %4: ptr<FILE> = call $pFILE__write__char %self.1 %3
  movq %rax, %rdi
  movb $0x2d, %sil
  call pFILE__write__char
  # %self.2: ptr<FILE> = load %self.ptr
  movq 24(%rsp), %rax
  # %value.2: i32 = load %value.ptr
  movl 20(%rsp), %ecx
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
  movl 20(%rsp), %eax
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
  movq 24(%rsp), %rax
  # %value.4: i32 = load %value.ptr
  movl 20(%rsp), %ecx
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
  # %digit.ptr: ptr<i32> = alloc i32
  # %value.5: i32 = load %value.ptr
  movl 20(%rsp), %eax
  # %12: i32 = const 10
  # %13: i32 = mod %value.5 %12
  movl %eax, %ecx
  movl %ecx, %eax
  cltd
  movl $0xa, %esi
  idivl %esi
  # store %digit.ptr %13
  movl %edx, 16(%rsp)
  # %char.ptr: ptr<u8> = alloc u8
  # %digit.1: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %14: i32 = const 0
  # %15: bool = cmp_eq %digit.1 %14
  cmp $0x0, %eax
  sete %cl
  # br %15 @6 @7
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__6
  jmp .L__pFILE__write__signed__7
.L__pFILE__write__signed__6:
  # %16: u8 = const '0'
  # store %char.ptr %16
  movb $0x30, 15(%rsp)
  # jmp @8
  jmp .L__pFILE__write__signed__8
.L__pFILE__write__signed__7:
  # %digit.2: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %17: i32 = const 1
  # %18: bool = cmp_eq %digit.2 %17
  cmp $0x1, %eax
  sete %cl
  # br %18 @9 @10
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__9
  jmp .L__pFILE__write__signed__10
.L__pFILE__write__signed__8:
  # %self.4: ptr<FILE> = load %self.ptr
  movq 24(%rsp), %rax
  # %char.1: u8 = load %char.ptr
  movb 15(%rsp), %cl
  # %44: ptr<FILE> = call $pFILE__write__char %self.4 %char.1
  movq %rax, %rdi
  movb %cl, %sil
  call pFILE__write__char
  # %self.5: ptr<FILE> = load %self.ptr
  movq 24(%rsp), %rax
  # ret %self.5
  jmp .L__pFILE__write__signed__E
.L__pFILE__write__signed__9:
  # %19: u8 = const '1'
  # store %char.ptr %19
  movb $0x31, 15(%rsp)
  # jmp @11
  jmp .L__pFILE__write__signed__11
.L__pFILE__write__signed__10:
  # %digit.3: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %20: i32 = const 2
  # %21: bool = cmp_eq %digit.3 %20
  cmp $0x2, %eax
  sete %cl
  # br %21 @12 @13
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__12
  jmp .L__pFILE__write__signed__13
.L__pFILE__write__signed__11:
  # jmp @8
  jmp .L__pFILE__write__signed__8
.L__pFILE__write__signed__12:
  # %22: u8 = const '2'
  # store %char.ptr %22
  movb $0x32, 15(%rsp)
  # jmp @14
  jmp .L__pFILE__write__signed__14
.L__pFILE__write__signed__13:
  # %digit.4: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %23: i32 = const 3
  # %24: bool = cmp_eq %digit.4 %23
  cmp $0x3, %eax
  sete %cl
  # br %24 @15 @16
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__15
  jmp .L__pFILE__write__signed__16
.L__pFILE__write__signed__14:
  # jmp @11
  jmp .L__pFILE__write__signed__11
.L__pFILE__write__signed__15:
  # %25: u8 = const '3'
  # store %char.ptr %25
  movb $0x33, 15(%rsp)
  # jmp @17
  jmp .L__pFILE__write__signed__17
.L__pFILE__write__signed__16:
  # %digit.5: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %26: i32 = const 4
  # %27: bool = cmp_eq %digit.5 %26
  cmp $0x4, %eax
  sete %cl
  # br %27 @18 @19
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__18
  jmp .L__pFILE__write__signed__19
.L__pFILE__write__signed__17:
  # jmp @14
  jmp .L__pFILE__write__signed__14
.L__pFILE__write__signed__18:
  # %28: u8 = const '4'
  # store %char.ptr %28
  movb $0x34, 15(%rsp)
  # jmp @20
  jmp .L__pFILE__write__signed__20
.L__pFILE__write__signed__19:
  # %digit.6: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %29: i32 = const 5
  # %30: bool = cmp_eq %digit.6 %29
  cmp $0x5, %eax
  sete %cl
  # br %30 @21 @22
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__21
  jmp .L__pFILE__write__signed__22
.L__pFILE__write__signed__20:
  # jmp @17
  jmp .L__pFILE__write__signed__17
.L__pFILE__write__signed__21:
  # %31: u8 = const '5'
  # store %char.ptr %31
  movb $0x35, 15(%rsp)
  # jmp @23
  jmp .L__pFILE__write__signed__23
.L__pFILE__write__signed__22:
  # %digit.7: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %32: i32 = const 6
  # %33: bool = cmp_eq %digit.7 %32
  cmp $0x6, %eax
  sete %cl
  # br %33 @24 @25
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__24
  jmp .L__pFILE__write__signed__25
.L__pFILE__write__signed__23:
  # jmp @20
  jmp .L__pFILE__write__signed__20
.L__pFILE__write__signed__24:
  # %34: u8 = const '6'
  # store %char.ptr %34
  movb $0x36, 15(%rsp)
  # jmp @26
  jmp .L__pFILE__write__signed__26
.L__pFILE__write__signed__25:
  # %digit.8: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %35: i32 = const 7
  # %36: bool = cmp_eq %digit.8 %35
  cmp $0x7, %eax
  sete %cl
  # br %36 @27 @28
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__27
  jmp .L__pFILE__write__signed__28
.L__pFILE__write__signed__26:
  # jmp @23
  jmp .L__pFILE__write__signed__23
.L__pFILE__write__signed__27:
  # %37: u8 = const '7'
  # store %char.ptr %37
  movb $0x37, 15(%rsp)
  # jmp @29
  jmp .L__pFILE__write__signed__29
.L__pFILE__write__signed__28:
  # %digit.9: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %38: i32 = const 8
  # %39: bool = cmp_eq %digit.9 %38
  cmp $0x8, %eax
  sete %cl
  # br %39 @30 @31
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__30
  jmp .L__pFILE__write__signed__31
.L__pFILE__write__signed__29:
  # jmp @26
  jmp .L__pFILE__write__signed__26
.L__pFILE__write__signed__30:
  # %40: u8 = const '8'
  # store %char.ptr %40
  movb $0x38, 15(%rsp)
  # jmp @32
  jmp .L__pFILE__write__signed__32
.L__pFILE__write__signed__31:
  # %digit.10: i32 = load %digit.ptr
  movl 16(%rsp), %eax
  # %41: i32 = const 9
  # %42: bool = cmp_eq %digit.10 %41
  cmp $0x9, %eax
  sete %cl
  # br %42 @33 @34
  cmp $0x0, %cl
  jne .L__pFILE__write__signed__33
  jmp .L__pFILE__write__signed__34
.L__pFILE__write__signed__32:
  # jmp @29
  jmp .L__pFILE__write__signed__29
.L__pFILE__write__signed__33:
  # %43: u8 = const '9'
  # store %char.ptr %43
  movb $0x39, 15(%rsp)
  # jmp @34
  jmp .L__pFILE__write__signed__34
.L__pFILE__write__signed__34:
  # jmp @32
  jmp .L__pFILE__write__signed__32
.L__pFILE__write__signed__E:
  add $0x20, %rsp
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
