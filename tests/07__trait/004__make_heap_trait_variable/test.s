pSquare__area:
.L__pSquare__area__S:
  sub $0x10, %rsp
.L__pSquare__area__1:
  # %self.ptr: ptr<ptr<Square>> = alloc ptr<Square>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %1: ptr<Square> = load %self.ptr
  movq 8(%rsp), %rax
  # %2: ptr<i32> = offset %1 Square.side
  movq %rax, %rcx
  # %3: i32 = load %2
  movl 0(%rcx), %eax
  # %4: ptr<Square> = load %self.ptr
  movq 8(%rsp), %rcx
  # %5: ptr<i32> = offset %4 Square.side
  movq %rcx, %rdx
  # %6: i32 = load %5
  movl 0(%rdx), %ecx
  # %7: i32 = mul %3 %6
  movl %eax, %edx
  movl %edx, %esi
  movl %esi, %eax
  mull %ecx
  # ret %7
  jmp .L__pSquare__area__E
.L__pSquare__area__E:
  add $0x10, %rsp
  ret


pCircle__area:
.L__pCircle__area__S:
  sub $0x10, %rsp
.L__pCircle__area__1:
  # %self.ptr: ptr<ptr<Circle>> = alloc ptr<Circle>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %1: i32 = const 312
  # %2: ptr<Circle> = load %self.ptr
  movq 8(%rsp), %rax
  # %3: ptr<i32> = offset %2 Circle.radius
  movq %rax, %rcx
  # %4: i32 = load %3
  movl 0(%rcx), %eax
  # %5: i32 = mul %1 %4
  movl %eax, %ecx
  movl $0x138, %eax
  mull %ecx
  # %6: ptr<Circle> = load %self.ptr
  movq 8(%rsp), %rcx
  # %7: ptr<i32> = offset %6 Circle.radius
  movq %rcx, %rdx
  # %8: i32 = load %7
  movl 0(%rdx), %ecx
  # %9: i32 = mul %5 %8
  movl %eax, %edx
  movl %edx, %esi
  movl %esi, %eax
  mull %ecx
  # %10: i32 = const 100
  # %11: i32 = div %9 %10
  movl %eax, %ecx
  movl %ecx, %eax
  cltd
  movl $0x64, %esi
  idivl %esi
  # ret %11
  jmp .L__pCircle__area__E
.L__pCircle__area__E:
  add $0x10, %rsp
  ret


.globl main
main:
.L__main__S:
  sub $0x20, %rsp
.L__main__1:
  # %square.ptr: ptr<ptr<Square>> = alloc ptr<Square>
  # %1: u64 = const 4
  # %2: ptr<Square> = call $malloc %1
  movq $0x4, %rdi
  call malloc
  # %3: i32 = const 10
  # %4: Square = struct { Square.side: %3 }
  # %5: ptr<i32> = offset %2 Square.side
  movq %rax, %rcx
  # store %5 %3
  movl $0xa, 0(%rcx)
  # store %square.ptr %2
  movq %rax, 24(%rsp)
  # %square_shape.ptr: ptr<ptr<Shape>> = alloc ptr<Shape>
  # %6: u64 = const 16
  # %7: ptr<Shape> = call $malloc %6
  movq $0x10, %rdi
  call malloc
  # %square.1: ptr<Square> = load %square.ptr
  movq 24(%rsp), %rcx
  # %8: ptr<func (self: ptr<Square>) -> i32> = address $pSquare__area
  # %9: Shape = struct { Shape.self: %square.1, Shape.area: %8 }
  # %10: ptr<ptr<Any>> = offset %7 Shape.self
  movq %rax, %rdx
  # store %10 %square.1
  movq %rcx, 0(%rdx)
  # %11: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %7 Shape.area
  movq %rax, %rcx
  # store %11 %8
  lea pSquare__area, %rdx
  movq %rdx, 8(%rcx)
  # store %square_shape.ptr %7
  movq %rax, 16(%rsp)
  # %circle.ptr: ptr<ptr<Circle>> = alloc ptr<Circle>
  # %12: u64 = const 4
  # %13: ptr<Circle> = call $malloc %12
  movq $0x4, %rdi
  call malloc
  # %14: i32 = const 10
  # %15: Circle = struct { Circle.radius: %14 }
  # %16: ptr<i32> = offset %13 Circle.radius
  movq %rax, %rcx
  # store %16 %14
  movl $0xa, 0(%rcx)
  # store %circle.ptr %13
  movq %rax, 8(%rsp)
  # %square_shape.1: ptr<Shape> = load %square_shape.ptr
  movq 16(%rsp), %rax
  # %17: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %square_shape.1 Shape.area
  movq %rax, %rcx
  # %18: ptr<func (self: ptr<Any>) -> i32> = load %17
  movq 8(%rcx), %rdx
  # %19: ptr<ptr<Any>> = offset %square_shape.1 Shape.self
  movq %rax, %rcx
  # %20: ptr<Any> = load %19
  movq 0(%rcx), %rax
  # %21: i32 = call %18 %20
  movq %rax, %rdi
  call *%rdx
  # %22: i32 = const 100
  # %23: bool = cmp_ne %21 %22
  cmp $0x64, %eax
  setne %cl
  # br %23 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %24: i32 = const 1
  # ret %24
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %25: u64 = const 16
  # %26: ptr<Shape> = call $malloc %25
  movq $0x10, %rdi
  call malloc
  # %circle.1: ptr<Circle> = load %circle.ptr
  movq 8(%rsp), %rcx
  # %27: ptr<func (self: ptr<Circle>) -> i32> = address $pCircle__area
  # %28: Shape = struct { Shape.self: %circle.1, Shape.area: %27 }
  # %29: ptr<ptr<Any>> = offset %26 Shape.self
  movq %rax, %rdx
  # store %29 %circle.1
  movq %rcx, 0(%rdx)
  # %30: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %26 Shape.area
  movq %rax, %rcx
  # store %30 %27
  lea pCircle__area, %rdx
  movq %rdx, 8(%rcx)
  # %31: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %26 Shape.area
  movq %rax, %rcx
  # %32: ptr<func (self: ptr<Any>) -> i32> = load %31
  movq 8(%rcx), %rdx
  # %33: ptr<ptr<Any>> = offset %26 Shape.self
  movq %rax, %rcx
  # %34: ptr<Any> = load %33
  movq 0(%rcx), %rax
  # %35: i32 = call %32 %34
  movq %rax, %rdi
  call *%rdx
  # %36: i32 = const 312
  # %37: bool = cmp_ne %35 %36
  cmp $0x138, %eax
  setne %cl
  # br %37 @4 @5
  cmp $0x0, %cl
  jne .L__main__4
  jmp .L__main__5
.L__main__4:
  # %38: i32 = const 2
  # ret %38
  movl $0x2, %eax
  jmp .L__main__E
.L__main__5:
  # %39: i32 = const 0
  # ret %39
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  ret
