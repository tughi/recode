.globl main
main:
.L__main__S:
.L__main__1:
  call get_answer
  cmp $0x2a, %eax
  setne %cl
  cmp $0x0, %cl
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  movl $0x1, %eax
  jmp .L__main__E
.L__main__3:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__E:
  ret


get_answer:
.L__get_answer__S:
.L__get_answer__1:
  movl $0x2a, %edi
  call echo_value
  jmp .L__get_answer__E
.L__get_answer__E:
  ret


echo_value:
.L__echo_value__S:
.L__echo_value__1:
  movl %edi, %eax
  jmp .L__echo_value__E
.L__echo_value__E:
  ret
