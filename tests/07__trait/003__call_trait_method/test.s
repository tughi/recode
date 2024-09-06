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
  sub $0x30, %rsp
.L__main__1:
  # %square.ptr: ptr<Square> = alloc Square
  # %1: i32 = const 10
  # %2: Square = struct { Square.side: %1 }
  # %3: ptr<i32> = offset %square.ptr Square.side
  lea 44(%rsp), %rax
  # store %3 %1
  movl $0xa, 0(%rax)
  # %square_shape.ptr: ptr<Shape> = alloc Shape
  # %4: ptr<func (self: ptr<Square>) -> i32> = address $pSquare__area
  # %5: Shape = struct { Shape.self: %square.ptr, Shape.area: %4 }
  # %6: ptr<ptr<Any>> = offset %square_shape.ptr Shape.self
  lea 28(%rsp), %rax
  # store %6 %square.ptr
  lea 44(%rsp), %rcx
  movq %rcx, 0(%rax)
  # %7: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %square_shape.ptr Shape.area
  lea 28(%rsp), %rax
  # store %7 %4
  lea pSquare__area, %rcx
  movq %rcx, 8(%rax)
  # %circle.ptr: ptr<Circle> = alloc Circle
  # %8: i32 = const 10
  # %9: Circle = struct { Circle.radius: %8 }
  # %10: ptr<i32> = offset %circle.ptr Circle.radius
  lea 24(%rsp), %rax
  # store %10 %8
  movl $0xa, 0(%rax)
  # %circle_shape.ptr: ptr<Shape> = alloc Shape
  # %11: ptr<func (self: ptr<Circle>) -> i32> = address $pCircle__area
  # %12: Shape = struct { Shape.self: %circle.ptr, Shape.area: %11 }
  # %13: ptr<ptr<Any>> = offset %circle_shape.ptr Shape.self
  lea 8(%rsp), %rax
  # store %13 %circle.ptr
  lea 24(%rsp), %rcx
  movq %rcx, 0(%rax)
  # %14: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %circle_shape.ptr Shape.area
  lea 8(%rsp), %rax
  # store %14 %11
  lea pCircle__area, %rcx
  movq %rcx, 8(%rax)
  # %15: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %square_shape.ptr Shape.area
  lea 28(%rsp), %rax
  # %16: ptr<func (self: ptr<Any>) -> i32> = load %15
  movq 8(%rax), %rcx
  # %17: ptr<ptr<Any>> = offset %square_shape.ptr Shape.self
  lea 28(%rsp), %rax
  # %18: ptr<Any> = load %17
  movq 0(%rax), %rdx
  # %19: i32 = call %16 %18
  movq %rdx, %rdi
  call *%rcx
  # %20: i32 = const 100
  # %21: bool = cmp_ne %19 %20
  cmp $0x64, %eax
  setne %cl
  # br %21 @2 @3
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # %22: i32 = const 1
  # ret %22
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  # %23: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %circle_shape.ptr Shape.area
  lea 8(%rsp), %rax
  # %24: ptr<func (self: ptr<Any>) -> i32> = load %23
  movq 8(%rax), %rcx
  # %25: ptr<ptr<Any>> = offset %circle_shape.ptr Shape.self
  lea 8(%rsp), %rax
  # %26: ptr<Any> = load %25
  movq 0(%rax), %rdx
  # %27: i32 = call %24 %26
  movq %rdx, %rdi
  call *%rcx
  # %28: i32 = const 312
  # %29: bool = cmp_ne %27 %28
  cmp $0x138, %eax
  setne %cl
  # br %29 @4 @5
  cmp $0x0, %cl
  jne .L__main__4
  jmp .L__main__5
.L__main__4:
  # %30: i32 = const 2
  # ret %30
  movl $0x2, %eax
  jmp .L__main__E
.L__main__5:
  # %31: i32 = const 0
  # ret %31
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  add $0x30, %rsp
  ret
