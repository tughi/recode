.globl main
main:
.L__main__1:
  mov $42, %edi
  mov $10, %esi
  call div
  mov %eax, %edi
  mov $2, %esi
  call add
  mov %eax, %ebx
  mov $42, %edi
  mov $10, %esi
  call mod
  mov %eax, %edi
  mov $5, %esi
  call add
  mov %ebx, %edi
  mov %eax, %esi
  call mul
  mov %eax, %edi
  mov $42, %esi
  call sub
  ret
add:
.L__add__1:
  mov %edi, %r11d
  add %esi, %r11d
  mov %r11d, %eax
  ret
sub:
.L__sub__1:
  mov %edi, %r11d
  sub %esi, %r11d
  mov %r11d, %eax
  ret
mul:
.L__mul__1:
  mov %edi, %eax
  mul %esi
  ret
div:
.L__div__1:
  mov %edi, %eax
  cltd
  idiv %esi
  ret
mod:
.L__mod__1:
  mov %edi, %eax
  cltd
  idiv %esi
  mov %edx, %eax
  ret
