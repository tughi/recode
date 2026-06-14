.globl main
main:
.L__main__S:
.L__main__1:
  # %1: i32 = const 0
  # ret %1
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  ret


f1:
.L__f1__S:
  sub $0x10, %rsp
.L__f1__1:
  # %v1.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 1
  # store %v1.ptr %1
  movl $0x1, 12(%rsp)
  # ret
  jmp .L__f1__E
.L__f1__E:
  add $0x10, %rsp
  ret


f2:
.L__f2__S:
  sub $0x10, %rsp
.L__f2__1:
  # %v1.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 1
  # store %v1.ptr %1
  movl $0x1, 12(%rsp)
  # %v2.ptr: ptr<i32> = alloc i32
  # %2: i32 = const 2
  # store %v2.ptr %2
  movl $0x2, 8(%rsp)
  # %v3.ptr: ptr<i32> = alloc i32
  # %3: i32 = const 3
  # store %v3.ptr %3
  movl $0x3, 4(%rsp)
  # %v4.ptr: ptr<i32> = alloc i32
  # %4: i32 = const 4
  # store %v4.ptr %4
  movl $0x4, 0(%rsp)
  # ret
  jmp .L__f2__E
.L__f2__E:
  add $0x10, %rsp
  ret


f3:
.L__f3__S:
  sub $0x20, %rsp
.L__f3__1:
  # %v1.ptr: ptr<i32> = alloc i32
  # %1: i32 = const 1
  # store %v1.ptr %1
  movl $0x1, 28(%rsp)
  # %v2.ptr: ptr<i32> = alloc i32
  # %2: i32 = const 2
  # store %v2.ptr %2
  movl $0x2, 24(%rsp)
  # %v3.ptr: ptr<i32> = alloc i32
  # %3: i32 = const 3
  # store %v3.ptr %3
  movl $0x3, 20(%rsp)
  # %v4.ptr: ptr<i32> = alloc i32
  # %4: i32 = const 4
  # store %v4.ptr %4
  movl $0x4, 16(%rsp)
  # %v5.ptr: ptr<i32> = alloc i32
  # %5: i32 = const 5
  # store %v5.ptr %5
  movl $0x5, 12(%rsp)
  # ret
  jmp .L__f3__E
.L__f3__E:
  add $0x20, %rsp
  ret
