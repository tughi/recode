.globl main
main:
.L__main__1:
  mov $0, %edi
  call echo
  ret
echo:
.L__echo__1:
  mov %edi, %eax
  ret
