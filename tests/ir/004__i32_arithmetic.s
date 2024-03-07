.globl main
main:
.L__main__S:
.L__main__1:
  mov $0x2a, %edi
  mov $0xa, %esi
  call div
  mov %eax, %edi
  mov $0x2, %esi
  call add
  mov %eax, %ebx
  mov $0x2a, %edi
  mov $0xa, %esi
  call mod
  mov %eax, %edi
  mov $0x5, %esi
  call add
  mov %ebx, %edi
  mov %eax, %esi
  call mul
  mov %eax, %edi
  mov $0x2a, %esi
  call sub
  jmp .L__main__E
.L__main__E:
  ret


add:
.L__add__S:
.L__add__1:
  mov %edi, %eax
  add %esi, %eax
  jmp .L__add__E
.L__add__E:
  ret


sub:
.L__sub__S:
.L__sub__1:
  mov %edi, %eax
  sub %esi, %eax
  jmp .L__sub__E
.L__sub__E:
  ret


mul:
.L__mul__S:
.L__mul__1:
  mov %edi, %eax
  mul %esi
  jmp .L__mul__E
.L__mul__E:
  ret


div:
.L__div__S:
.L__div__1:
  mov %edi, %eax
  cltd
  idiv %esi
  jmp .L__div__E
.L__div__E:
  ret


mod:
.L__mod__S:
.L__mod__1:
  mov %edi, %eax
  cltd
  idiv %esi
  mov %edx, %eax
  jmp .L__mod__E
.L__mod__E:
  ret
