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
.L__add__1:
  movl %edi, %eax
  add %esi, %eax
  jmp .L__add__E
.L__add__E:
  ret


sub:
.L__sub__S:
.L__sub__1:
  movl %edi, %eax
  sub %esi, %eax
  jmp .L__sub__E
.L__sub__E:
  ret


mul:
.L__mul__S:
.L__mul__1:
  movl %edi, %eax
  mull %esi
  jmp .L__mul__E
.L__mul__E:
  ret


div:
.L__div__S:
.L__div__1:
  movl %edi, %eax
  cltd
  idiv %esi
  jmp .L__div__E
.L__div__E:
  ret


mod:
.L__mod__S:
.L__mod__1:
  movl %edi, %eax
  cltd
  idiv %esi
  movl %edx, %eax
  jmp .L__mod__E
.L__mod__E:
  ret
