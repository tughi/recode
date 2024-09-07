pDog__legs:
.L__pDog__legs__S:
  sub $0x10, %rsp
.L__pDog__legs__1:
  # %self.ptr: ptr<ptr<Dog>> = alloc ptr<Dog>
  # store %self.ptr %self
  movq %rdi, 8(%rsp)
  # %1: i32 = const 4
  # ret %1
  movl $0x4, %eax
  jmp .L__pDog__legs__E
.L__pDog__legs__E:
  add $0x10, %rsp
  ret


.globl main
main:
.L__main__S:
  sub $0x20, %rsp
.L__main__1:
  # %dog.ptr: ptr<Dog> = alloc Dog
  # %1: i32 = const 10
  # %2: Dog = struct { Dog.age: %1 }
  # %3: ptr<i32> = offset %dog.ptr Dog.age
  lea 28(%rsp), %rax
  # store %3 %1
  movl $0xa, 0(%rax)
  # %animal.ptr: ptr<Animal> = alloc Animal
  # %4: ptr<func (self: ptr<Dog>) -> i32> = address $pDog__legs
  # %5: Animal = struct { Animal.self: %dog.ptr, Animal.legs: %4 }
  # %6: ptr<ptr<Any>> = offset %animal.ptr Animal.self
  lea 12(%rsp), %rax
  # store %6 %dog.ptr
  lea 28(%rsp), %rcx
  movq %rcx, 0(%rax)
  # %7: ptr<ptr<func (self: ptr<Any>) -> i32>> = offset %animal.ptr Animal.legs
  lea 12(%rsp), %rax
  # store %7 %4
  lea pDog__legs, %rcx
  movq %rcx, 8(%rax)
  # ret
  jmp .L__main__E
.L__main__E:
  add $0x20, %rsp
  xor %rax, %rax
  ret
