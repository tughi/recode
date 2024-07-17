.globl main
main:
.L__main__S:
  pushq %rbx
.L__main__1:
  movl $0x2a, %edi
  movl $0xa, %esi
  call div
  movl %eax, %edi
  movl $0x2, %esi
  call add
  movl %eax, %ebx
  movl $0x2a, %edi
  movl $0xa, %esi
  call mod
  movl %eax, %edi
  movl $0x5, %esi
  call add
  movl %ebx, %edi
  movl %eax, %esi
  call mul
  movl %eax, %edi
  movl $0x2a, %esi
  call sub
  jmp .L__main__E
.L__main__E:
  popq %rbx
  ret


add:
.L__add__S:
  sub $0x10, %rsp
.L__add__1:
  movl %edi, 12(%rsp)
  movl %esi, 8(%rsp)
  movl 12(%rsp), %eax
  movl 8(%rsp), %ecx
  movl %eax, %edx
  add %ecx, %edx
  movl %edx, %eax
  jmp .L__add__E
.L__add__E:
  add $0x10, %rsp
  ret


sub:
.L__sub__S:
  sub $0x10, %rsp
.L__sub__1:
  movl %edi, 12(%rsp)
  movl %esi, 8(%rsp)
  movl 12(%rsp), %eax
  movl 8(%rsp), %ecx
  movl %eax, %edx
  sub %ecx, %edx
  movl %edx, %eax
  jmp .L__sub__E
.L__sub__E:
  add $0x10, %rsp
  ret


mul:
.L__mul__S:
  sub $0x10, %rsp
.L__mul__1:
  movl %edi, 12(%rsp)
  movl %esi, 8(%rsp)
  movl 12(%rsp), %eax
  movl 8(%rsp), %ecx
  movl %eax, %edx
  movl %edx, %esi
  movl %esi, %eax
  mull %ecx
  jmp .L__mul__E
.L__mul__E:
  add $0x10, %rsp
  ret


div:
.L__div__S:
  sub $0x10, %rsp
.L__div__1:
  movl %edi, 12(%rsp)
  movl %esi, 8(%rsp)
  movl 12(%rsp), %eax
  movl 8(%rsp), %ecx
  movl %eax, %edx
  movl %edx, %esi
  movl %esi, %eax
  cltd
  idivl %ecx
  jmp .L__div__E
.L__div__E:
  add $0x10, %rsp
  ret


mod:
.L__mod__S:
  sub $0x10, %rsp
.L__mod__1:
  movl %edi, 12(%rsp)
  movl %esi, 8(%rsp)
  movl 12(%rsp), %eax
  movl 8(%rsp), %ecx
  movl %eax, %edx
  movl %edx, %esi
  movl %esi, %eax
  cltd
  idivl %ecx
  movl %edx, %eax
  jmp .L__mod__E
.L__mod__E:
  add $0x10, %rsp
  ret
