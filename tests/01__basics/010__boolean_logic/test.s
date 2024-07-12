.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  movb $0x1, 15(%rsp)
  movb $0x0, 14(%rsp)
  movb $0x1, 13(%rsp)
  movb $0x0, 12(%rsp)
  movb $0x1, 11(%rsp)
  movb $0x0, 10(%rsp)
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  jmp .L__main__4
.L__main__3:
  movl $0x1, %eax
  jmp .L__main__E
.L__main__4:
  movb 15(%rsp), %al
  movb %al, %cl
  xor $0x1, %cl
  cmp $0x0, %cl
  jne .L__main__5
  jmp .L__main__6
.L__main__5:
  movl $0x2, %eax
  jmp .L__main__E
.L__main__6:
  movb 14(%rsp), %al
  cmp $0x0, %al
  jne .L__main__7
  jmp .L__main__8
.L__main__7:
  movl $0x3, %eax
  jmp .L__main__E
.L__main__8:
  movb 14(%rsp), %al
  movb %al, %cl
  xor $0x1, %cl
  cmp $0x0, %cl
  jne .L__main__9
  jmp .L__main__10
.L__main__9:
  jmp .L__main__11
.L__main__10:
  movl $0x4, %eax
  jmp .L__main__E
.L__main__11:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__14
  jmp .L__main__15_F_11
.L__main__14:
  movb 14(%rsp), %cl
  jmp .L__main__15_F_14
.L__main__15:
  cmp $0x0, %al
  jne .L__main__12
  jmp .L__main__13
.L__main__15_F_11:
  jmp .L__main__15
.L__main__15_F_14:
  movb %cl, %al
  jmp .L__main__15
.L__main__12:
  movl $0x5, %eax
  jmp .L__main__E
.L__main__13:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__19
  jmp .L__main__20_F_13
.L__main__19:
  movb 14(%rsp), %cl
  jmp .L__main__20_F_19
.L__main__20:
  movb %al, %cl
  xor $0x1, %cl
  cmp $0x0, %cl
  jne .L__main__16
  jmp .L__main__17
.L__main__20_F_13:
  jmp .L__main__20
.L__main__20_F_19:
  movb %cl, %al
  jmp .L__main__20
.L__main__16:
  jmp .L__main__18
.L__main__17:
  movl $0x6, %eax
  jmp .L__main__E
.L__main__18:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__24
  jmp .L__main__25_F_18
.L__main__24:
  movb 14(%rsp), %cl
  jmp .L__main__25_F_24
.L__main__25:
  movb %al, %cl
  xor $0x1, %cl
  movb %cl, %al
  xor $0x1, %al
  cmp $0x0, %al
  jne .L__main__21
  jmp .L__main__22
.L__main__25_F_18:
  jmp .L__main__25
.L__main__25_F_24:
  movb %cl, %al
  jmp .L__main__25
.L__main__21:
  movl $0x7, %eax
  jmp .L__main__E
.L__main__22:
  jmp .L__main__23
.L__main__23:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__30_F_23
  jmp .L__main__29
.L__main__30:
  cmp $0x0, %al
  jne .L__main__26
  jmp .L__main__27
.L__main__30_F_23:
  jmp .L__main__30
.L__main__29:
  movb 14(%rsp), %cl
  jmp .L__main__30_F_29
.L__main__26:
  jmp .L__main__28
.L__main__27:
  movl $0x8, %eax
  jmp .L__main__E
.L__main__28:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__35_F_28
  jmp .L__main__34
.L__main__35:
  movb %al, %cl
  xor $0x1, %cl
  cmp $0x0, %cl
  jne .L__main__31
  jmp .L__main__32
.L__main__35_F_28:
  jmp .L__main__35
.L__main__34:
  movb 14(%rsp), %cl
  jmp .L__main__35_F_34
.L__main__31:
  movl $0x9, %eax
  jmp .L__main__E
.L__main__32:
  jmp .L__main__33
.L__main__33:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__38
  jmp .L__main__39_F_33
.L__main__38:
  movb 14(%rsp), %cl
  jmp .L__main__39_F_38
.L__main__39:
  cmp $0x0, %al
  jne .L__main__41_F_39
  jmp .L__main__40
.L__main__39_F_33:
  jmp .L__main__39
.L__main__39_F_38:
  movb %cl, %al
  jmp .L__main__39
.L__main__41:
  cmp $0x0, %al
  jne .L__main__36
  jmp .L__main__37
.L__main__41_F_39:
  jmp .L__main__41
.L__main__40:
  movb 13(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__42
  jmp .L__main__43_F_40
.L__main__36:
  movl $0xa, %eax
  jmp .L__main__E
.L__main__37:
  movb 14(%rsp), %al
  cmp $0x0, %al
  jne .L__main__47
  jmp .L__main__48_F_37
.L__main__47:
  movb 12(%rsp), %cl
  jmp .L__main__48_F_47
.L__main__48:
  cmp $0x0, %al
  jne .L__main__50_F_48
  jmp .L__main__49
.L__main__48_F_37:
  jmp .L__main__48
.L__main__48_F_47:
  movb %cl, %al
  jmp .L__main__48
.L__main__50:
  cmp $0x0, %al
  jne .L__main__44
  jmp .L__main__45
.L__main__50_F_48:
  jmp .L__main__50
.L__main__49:
  movb 15(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__51
  jmp .L__main__52_F_49
.L__main__44:
  jmp .L__main__46
.L__main__45:
  movl $0xb, %eax
  jmp .L__main__E
.L__main__46:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__56
  jmp .L__main__57_F_46
.L__main__56:
  movb 14(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__59_F_56
  jmp .L__main__58
.L__main__57:
  cmp $0x0, %al
  jne .L__main__60
  jmp .L__main__61_F_57
.L__main__57_F_46:
  jmp .L__main__57
.L__main__59:
  jmp .L__main__57_F_59
.L__main__59_F_56:
  jmp .L__main__59
.L__main__58:
  movb 13(%rsp), %al
  jmp .L__main__59_F_58
.L__main__57_F_59:
  movb %cl, %al
  jmp .L__main__57
.L__main__60:
  movb 12(%rsp), %cl
  jmp .L__main__61_F_60
.L__main__61:
  cmp $0x0, %al
  jne .L__main__53
  jmp .L__main__54
.L__main__61_F_57:
  jmp .L__main__61
.L__main__61_F_60:
  movb %cl, %al
  jmp .L__main__61
.L__main__53:
  movl $0xc, %eax
  jmp .L__main__E
.L__main__54:
  jmp .L__main__55
.L__main__55:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__66_F_55
  jmp .L__main__65
.L__main__66:
  cmp $0x0, %al
  jne .L__main__67
  jmp .L__main__68_F_66
.L__main__66_F_55:
  jmp .L__main__66
.L__main__65:
  movb 14(%rsp), %cl
  jmp .L__main__66_F_65
.L__main__67:
  movb 13(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__70_F_67
  jmp .L__main__69
.L__main__68:
  cmp $0x0, %al
  jne .L__main__62
  jmp .L__main__63
.L__main__68_F_66:
  jmp .L__main__68
.L__main__70:
  jmp .L__main__68_F_70
.L__main__70_F_67:
  jmp .L__main__70
.L__main__69:
  movb 12(%rsp), %al
  jmp .L__main__70_F_69
.L__main__68_F_70:
  movb %cl, %al
  jmp .L__main__68
.L__main__62:
  jmp .L__main__64
.L__main__63:
  movl $0xd, %eax
  jmp .L__main__E
.L__main__64:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__75_F_64
  jmp .L__main__74
.L__main__75:
  cmp $0x0, %al
  jne .L__main__76
  jmp .L__main__77_F_75
.L__main__75_F_64:
  jmp .L__main__75
.L__main__74:
  movb 12(%rsp), %cl
  jmp .L__main__75_F_74
.L__main__76:
  movb 14(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__79_F_76
  jmp .L__main__78
.L__main__77:
  cmp $0x0, %al
  jne .L__main__71
  jmp .L__main__72
.L__main__77_F_75:
  jmp .L__main__77
.L__main__79:
  jmp .L__main__77_F_79
.L__main__79_F_76:
  jmp .L__main__79
.L__main__78:
  movb 13(%rsp), %al
  jmp .L__main__79_F_78
.L__main__77_F_79:
  movb %cl, %al
  jmp .L__main__77
.L__main__71:
  jmp .L__main__73
.L__main__72:
  movl $0xe, %eax
  jmp .L__main__E
.L__main__73:
  movb 14(%rsp), %al
  cmp $0x0, %al
  jne .L__main__84_F_73
  jmp .L__main__83
.L__main__84:
  cmp $0x0, %al
  jne .L__main__88_F_84
  jmp .L__main__87
.L__main__84_F_73:
  jmp .L__main__84
.L__main__83:
  movb 13(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__85
  jmp .L__main__86_F_83
.L__main__88:
  cmp $0x0, %al
  jne .L__main__80
  jmp .L__main__81
.L__main__88_F_84:
  jmp .L__main__88
.L__main__87:
  movb 11(%rsp), %cl
  jmp .L__main__88_F_87
.L__main__80:
  jmp .L__main__82
.L__main__81:
  movl $0xf, %eax
  jmp .L__main__E
.L__main__82:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__92
  jmp .L__main__93_F_82
.L__main__92:
  movb 14(%rsp), %cl
  jmp .L__main__93_F_92
.L__main__93:
  cmp $0x0, %al
  jne .L__main__95_F_93
  jmp .L__main__94
.L__main__93_F_82:
  jmp .L__main__93
.L__main__93_F_92:
  movb %cl, %al
  jmp .L__main__93
.L__main__95:
  cmp $0x0, %al
  jne .L__main__98
  jmp .L__main__99_F_95
.L__main__95_F_93:
  jmp .L__main__95
.L__main__94:
  movb 13(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__96
  jmp .L__main__97_F_94
.L__main__98:
  movb 11(%rsp), %cl
  jmp .L__main__99_F_98
.L__main__99:
  cmp $0x0, %al
  jne .L__main__101_F_99
  jmp .L__main__100
.L__main__99_F_95:
  jmp .L__main__99
.L__main__99_F_98:
  movb %cl, %al
  jmp .L__main__99
.L__main__101:
  cmp $0x0, %al
  jne .L__main__89
  jmp .L__main__90
.L__main__101_F_99:
  jmp .L__main__101
.L__main__100:
  movb 10(%rsp), %cl
  jmp .L__main__101_F_100
.L__main__89:
  movl $0x10, %eax
  jmp .L__main__E
.L__main__90:
  jmp .L__main__91
.L__main__91:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__104
  jmp .L__main__105_F_91
.L__main__104:
  movb 14(%rsp), %cl
  jmp .L__main__105_F_104
.L__main__105:
  cmp $0x0, %al
  jne .L__main__107_F_105
  jmp .L__main__106
.L__main__105_F_91:
  jmp .L__main__105
.L__main__105_F_104:
  movb %cl, %al
  jmp .L__main__105
.L__main__107:
  cmp $0x0, %al
  jne .L__main__102
  jmp .L__main__103
.L__main__107_F_105:
  jmp .L__main__107
.L__main__106:
  movb 13(%rsp), %cl
  cmp $0x0, %cl
  jne .L__main__108
  jmp .L__main__109_F_106
.L__main__102:
  movl $0x11, %eax
  jmp .L__main__E
.L__main__103:
  movb 15(%rsp), %al
  cmp $0x0, %al
  jne .L__main__117
  jmp .L__main__118_F_103
.L__main__117:
  movb 14(%rsp), %cl
  movb %cl, %al
  xor $0x1, %al
  jmp .L__main__118_F_117
.L__main__118:
  cmp $0x0, %al
  jne .L__main__114
  jmp .L__main__115
.L__main__118_F_103:
  jmp .L__main__118
.L__main__118_F_117:
  jmp .L__main__118
.L__main__114:
  jmp .L__main__116
.L__main__115:
  movl $0x12, %eax
  jmp .L__main__E
.L__main__116:
  movb 15(%rsp), %al
  movb %al, %cl
  xor $0x1, %cl
  cmp $0x0, %cl
  jne .L__main__122_F_116
  jmp .L__main__121
.L__main__122:
  cmp $0x0, %cl
  jne .L__main__119
  jmp .L__main__120
.L__main__122_F_116:
  jmp .L__main__122
.L__main__121:
  movb 14(%rsp), %al
  jmp .L__main__122_F_121
.L__main__119:
  movl $0x13, %eax
  jmp .L__main__E
.L__main__120:
  movl $0x0, %eax
  jmp .L__main__E
.L__main__122_F_121:
  movb %al, %cl
  jmp .L__main__122
.L__main__108:
  movb 12(%rsp), %al
  jmp .L__main__109_F_108
.L__main__109:
  cmp $0x0, %cl
  jne .L__main__111_F_109
  jmp .L__main__110
.L__main__109_F_106:
  jmp .L__main__109
.L__main__109_F_108:
  movb %al, %cl
  jmp .L__main__109
.L__main__111:
  cmp $0x0, %cl
  jne .L__main__112
  jmp .L__main__113_F_111
.L__main__111_F_109:
  jmp .L__main__111
.L__main__110:
  movb 10(%rsp), %al
  jmp .L__main__111_F_110
.L__main__112:
  movb 11(%rsp), %al
  jmp .L__main__113_F_112
.L__main__113:
  jmp .L__main__107_F_113
.L__main__113_F_111:
  jmp .L__main__113
.L__main__113_F_112:
  movb %al, %cl
  jmp .L__main__113
.L__main__107_F_113:
  movb %cl, %al
  jmp .L__main__107
.L__main__111_F_110:
  movb %al, %cl
  jmp .L__main__111
.L__main__101_F_100:
  movb %cl, %al
  jmp .L__main__101
.L__main__96:
  movb 12(%rsp), %al
  jmp .L__main__97_F_96
.L__main__97:
  jmp .L__main__95_F_97
.L__main__97_F_94:
  jmp .L__main__97
.L__main__97_F_96:
  movb %al, %cl
  jmp .L__main__97
.L__main__95_F_97:
  movb %cl, %al
  jmp .L__main__95
.L__main__88_F_87:
  movb %cl, %al
  jmp .L__main__88
.L__main__85:
  movb 12(%rsp), %al
  jmp .L__main__86_F_85
.L__main__86:
  jmp .L__main__84_F_86
.L__main__86_F_83:
  jmp .L__main__86
.L__main__86_F_85:
  movb %al, %cl
  jmp .L__main__86
.L__main__84_F_86:
  movb %cl, %al
  jmp .L__main__84
.L__main__79_F_78:
  movb %al, %cl
  jmp .L__main__79
.L__main__75_F_74:
  movb %cl, %al
  jmp .L__main__75
.L__main__70_F_69:
  movb %al, %cl
  jmp .L__main__70
.L__main__66_F_65:
  movb %cl, %al
  jmp .L__main__66
.L__main__59_F_58:
  movb %al, %cl
  jmp .L__main__59
.L__main__51:
  movb 13(%rsp), %al
  jmp .L__main__52_F_51
.L__main__52:
  jmp .L__main__50_F_52
.L__main__52_F_49:
  jmp .L__main__52
.L__main__52_F_51:
  movb %al, %cl
  jmp .L__main__52
.L__main__50_F_52:
  movb %cl, %al
  jmp .L__main__50
.L__main__42:
  movb 12(%rsp), %al
  jmp .L__main__43_F_42
.L__main__43:
  jmp .L__main__41_F_43
.L__main__43_F_40:
  jmp .L__main__43
.L__main__43_F_42:
  movb %al, %cl
  jmp .L__main__43
.L__main__41_F_43:
  movb %cl, %al
  jmp .L__main__41
.L__main__35_F_34:
  movb %cl, %al
  jmp .L__main__35
.L__main__30_F_29:
  movb %cl, %al
  jmp .L__main__30
.L__main__E:
  add $0x10, %rsp
  ret
