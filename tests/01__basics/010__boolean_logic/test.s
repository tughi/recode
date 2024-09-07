.globl main
main:
.L__main__S:
  sub $0x10, %rsp
.L__main__1:
  # %check1.ptr: ptr<bool> = alloc bool
  # %1: bool = const true
  # store %check1.ptr %1
  movb $0x1, 15(%rsp)
  # %check2.ptr: ptr<bool> = alloc bool
  # %2: bool = const false
  # store %check2.ptr %2
  movb $0x0, 14(%rsp)
  # %check3.ptr: ptr<bool> = alloc bool
  # %3: bool = const true
  # store %check3.ptr %3
  movb $0x1, 13(%rsp)
  # %check4.ptr: ptr<bool> = alloc bool
  # %4: bool = const false
  # store %check4.ptr %4
  movb $0x0, 12(%rsp)
  # %check5.ptr: ptr<bool> = alloc bool
  # %5: bool = const true
  # store %check5.ptr %5
  movb $0x1, 11(%rsp)
  # %check6.ptr: ptr<bool> = alloc bool
  # %6: bool = const false
  # store %check6.ptr %6
  movb $0x0, 10(%rsp)
  # %check1.1: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.1 @2 @3
  cmp $0x0, %al
  jne .L__main__2
  jmp .L__main__3
.L__main__2:
  # jmp @4
  jmp .L__main__4
.L__main__3:
  # %7: i32 = const 1
  # ret %7
  movl $0x1, %eax
  jmp .L__main__E
.L__main__4:
  # %check1.2: bool = load %check1.ptr
  movb 15(%rsp), %al
  # %8: bool = not %check1.2
  movb %al, %cl
  xor $0x1, %cl
  # br %8 @5 @6
  cmp $0x0, %cl
  jne .L__main__5
  jmp .L__main__6
.L__main__5:
  # %9: i32 = const 2
  # ret %9
  movl $0x2, %eax
  jmp .L__main__E
.L__main__6:
  # %check2.1: bool = load %check2.ptr
  movb 14(%rsp), %al
  # br %check2.1 @7 @8
  cmp $0x0, %al
  jne .L__main__7
  jmp .L__main__8
.L__main__7:
  # %10: i32 = const 3
  # ret %10
  movl $0x3, %eax
  jmp .L__main__E
.L__main__8:
  # %check2.2: bool = load %check2.ptr
  movb 14(%rsp), %al
  # %11: bool = not %check2.2
  movb %al, %cl
  xor $0x1, %cl
  # br %11 @9 @10
  cmp $0x0, %cl
  jne .L__main__9
  jmp .L__main__10
.L__main__9:
  # jmp @11
  jmp .L__main__11
.L__main__10:
  # %12: i32 = const 4
  # ret %12
  movl $0x4, %eax
  jmp .L__main__E
.L__main__11:
  # %check1.3: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.3 @14 @15
  cmp $0x0, %al
  jne .L__main__14
  jmp .L__main__15_F_11
.L__main__14:
  # %check2.3: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @15
  jmp .L__main__15_F_14
.L__main__15:
  # %13: bool = phi @11 %check1.3 @14 %check2.3
  # br %13 @12 @13
  cmp $0x0, %al
  jne .L__main__12
  jmp .L__main__13
.L__main__15_F_11:
  jmp .L__main__15
.L__main__15_F_14:
  movb %cl, %al
  jmp .L__main__15
.L__main__12:
  # %14: i32 = const 5
  # ret %14
  movl $0x5, %eax
  jmp .L__main__E
.L__main__13:
  # %check1.4: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.4 @19 @20
  cmp $0x0, %al
  jne .L__main__19
  jmp .L__main__20_F_13
.L__main__19:
  # %check2.4: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @20
  jmp .L__main__20_F_19
.L__main__20:
  # %15: bool = phi @13 %check1.4 @19 %check2.4
  # %16: bool = not %15
  movb %al, %cl
  xor $0x1, %cl
  # br %16 @16 @17
  cmp $0x0, %cl
  jne .L__main__16
  jmp .L__main__17
.L__main__20_F_13:
  jmp .L__main__20
.L__main__20_F_19:
  movb %cl, %al
  jmp .L__main__20
.L__main__16:
  # jmp @18
  jmp .L__main__18
.L__main__17:
  # %17: i32 = const 6
  # ret %17
  movl $0x6, %eax
  jmp .L__main__E
.L__main__18:
  # %check1.5: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.5 @24 @25
  cmp $0x0, %al
  jne .L__main__24
  jmp .L__main__25_F_18
.L__main__24:
  # %check2.5: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @25
  jmp .L__main__25_F_24
.L__main__25:
  # %18: bool = phi @18 %check1.5 @24 %check2.5
  # %19: bool = not %18
  movb %al, %cl
  xor $0x1, %cl
  # %20: bool = not %19
  movb %cl, %al
  xor $0x1, %al
  # br %20 @21 @22
  cmp $0x0, %al
  jne .L__main__21
  jmp .L__main__22
.L__main__25_F_18:
  jmp .L__main__25
.L__main__25_F_24:
  movb %cl, %al
  jmp .L__main__25
.L__main__21:
  # %21: i32 = const 7
  # ret %21
  movl $0x7, %eax
  jmp .L__main__E
.L__main__22:
  # jmp @23
  jmp .L__main__23
.L__main__23:
  # %check1.6: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.6 @30 @29
  cmp $0x0, %al
  jne .L__main__30_F_23
  jmp .L__main__29
.L__main__30:
  # %22: bool = phi @23 %check1.6 @29 %check2.6
  # br %22 @26 @27
  cmp $0x0, %al
  jne .L__main__26
  jmp .L__main__27
.L__main__30_F_23:
  jmp .L__main__30
.L__main__29:
  # %check2.6: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @30
  jmp .L__main__30_F_29
.L__main__26:
  # jmp @28
  jmp .L__main__28
.L__main__27:
  # %23: i32 = const 8
  # ret %23
  movl $0x8, %eax
  jmp .L__main__E
.L__main__28:
  # %check1.7: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.7 @35 @34
  cmp $0x0, %al
  jne .L__main__35_F_28
  jmp .L__main__34
.L__main__35:
  # %24: bool = phi @28 %check1.7 @34 %check2.7
  # %25: bool = not %24
  movb %al, %cl
  xor $0x1, %cl
  # br %25 @31 @32
  cmp $0x0, %cl
  jne .L__main__31
  jmp .L__main__32
.L__main__35_F_28:
  jmp .L__main__35
.L__main__34:
  # %check2.7: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @35
  jmp .L__main__35_F_34
.L__main__31:
  # %26: i32 = const 9
  # ret %26
  movl $0x9, %eax
  jmp .L__main__E
.L__main__32:
  # jmp @33
  jmp .L__main__33
.L__main__33:
  # %check1.8: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.8 @38 @39
  cmp $0x0, %al
  jne .L__main__38
  jmp .L__main__39_F_33
.L__main__38:
  # %check2.8: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @39
  jmp .L__main__39_F_38
.L__main__39:
  # %27: bool = phi @33 %check1.8 @38 %check2.8
  # br %27 @41 @40
  cmp $0x0, %al
  jne .L__main__41_F_39
  jmp .L__main__40
.L__main__39_F_33:
  jmp .L__main__39
.L__main__39_F_38:
  movb %cl, %al
  jmp .L__main__39
.L__main__41:
  # %29: bool = phi @39 %27 @43 %28
  # br %29 @36 @37
  cmp $0x0, %al
  jne .L__main__36
  jmp .L__main__37
.L__main__41_F_39:
  jmp .L__main__41
.L__main__40:
  # %check3.1: bool = load %check3.ptr
  movb 13(%rsp), %cl
  # br %check3.1 @42 @43
  cmp $0x0, %cl
  jne .L__main__42
  jmp .L__main__43_F_40
.L__main__36:
  # %30: i32 = const 10
  # ret %30
  movl $0xa, %eax
  jmp .L__main__E
.L__main__37:
  # %check2.9: bool = load %check2.ptr
  movb 14(%rsp), %al
  # br %check2.9 @47 @48
  cmp $0x0, %al
  jne .L__main__47
  jmp .L__main__48_F_37
.L__main__47:
  # %check4.2: bool = load %check4.ptr
  movb 12(%rsp), %cl
  # jmp @48
  jmp .L__main__48_F_47
.L__main__48:
  # %31: bool = phi @37 %check2.9 @47 %check4.2
  # br %31 @50 @49
  cmp $0x0, %al
  jne .L__main__50_F_48
  jmp .L__main__49
.L__main__48_F_37:
  jmp .L__main__48
.L__main__48_F_47:
  movb %cl, %al
  jmp .L__main__48
.L__main__50:
  # %33: bool = phi @48 %31 @52 %32
  # br %33 @44 @45
  cmp $0x0, %al
  jne .L__main__44
  jmp .L__main__45
.L__main__50_F_48:
  jmp .L__main__50
.L__main__49:
  # %check1.9: bool = load %check1.ptr
  movb 15(%rsp), %cl
  # br %check1.9 @51 @52
  cmp $0x0, %cl
  jne .L__main__51
  jmp .L__main__52_F_49
.L__main__44:
  # jmp @46
  jmp .L__main__46
.L__main__45:
  # %34: i32 = const 11
  # ret %34
  movl $0xb, %eax
  jmp .L__main__E
.L__main__46:
  # %check1.10: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.10 @56 @57
  cmp $0x0, %al
  jne .L__main__56
  jmp .L__main__57_F_46
.L__main__56:
  # %check2.10: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # br %check2.10 @59 @58
  cmp $0x0, %cl
  jne .L__main__59_F_56
  jmp .L__main__58
.L__main__57:
  # %36: bool = phi @46 %check1.10 @59 %35
  # br %36 @60 @61
  cmp $0x0, %al
  jne .L__main__60
  jmp .L__main__61_F_57
.L__main__57_F_46:
  jmp .L__main__57
.L__main__59:
  # %35: bool = phi @56 %check2.10 @58 %check3.3
  # jmp @57
  jmp .L__main__57_F_59
.L__main__59_F_56:
  jmp .L__main__59
.L__main__58:
  # %check3.3: bool = load %check3.ptr
  movb 13(%rsp), %al
  # jmp @59
  jmp .L__main__59_F_58
.L__main__57_F_59:
  movb %cl, %al
  jmp .L__main__57
.L__main__60:
  # %check4.3: bool = load %check4.ptr
  movb 12(%rsp), %cl
  # jmp @61
  jmp .L__main__61_F_60
.L__main__61:
  # %37: bool = phi @57 %36 @60 %check4.3
  # br %37 @53 @54
  cmp $0x0, %al
  jne .L__main__53
  jmp .L__main__54
.L__main__61_F_57:
  jmp .L__main__61
.L__main__61_F_60:
  movb %cl, %al
  jmp .L__main__61
.L__main__53:
  # %38: i32 = const 12
  # ret %38
  movl $0xc, %eax
  jmp .L__main__E
.L__main__54:
  # jmp @55
  jmp .L__main__55
.L__main__55:
  # %check1.11: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.11 @66 @65
  cmp $0x0, %al
  jne .L__main__66_F_55
  jmp .L__main__65
.L__main__66:
  # %39: bool = phi @55 %check1.11 @65 %check2.11
  # br %39 @67 @68
  cmp $0x0, %al
  jne .L__main__67
  jmp .L__main__68_F_66
.L__main__66_F_55:
  jmp .L__main__66
.L__main__65:
  # %check2.11: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @66
  jmp .L__main__66_F_65
.L__main__67:
  # %check3.4: bool = load %check3.ptr
  movb 13(%rsp), %cl
  # br %check3.4 @70 @69
  cmp $0x0, %cl
  jne .L__main__70_F_67
  jmp .L__main__69
.L__main__68:
  # %41: bool = phi @66 %39 @70 %40
  # br %41 @62 @63
  cmp $0x0, %al
  jne .L__main__62
  jmp .L__main__63
.L__main__68_F_66:
  jmp .L__main__68
.L__main__70:
  # %40: bool = phi @67 %check3.4 @69 %check4.4
  # jmp @68
  jmp .L__main__68_F_70
.L__main__70_F_67:
  jmp .L__main__70
.L__main__69:
  # %check4.4: bool = load %check4.ptr
  movb 12(%rsp), %al
  # jmp @70
  jmp .L__main__70_F_69
.L__main__68_F_70:
  movb %cl, %al
  jmp .L__main__68
.L__main__62:
  # jmp @64
  jmp .L__main__64
.L__main__63:
  # %42: i32 = const 13
  # ret %42
  movl $0xd, %eax
  jmp .L__main__E
.L__main__64:
  # %check1.12: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.12 @75 @74
  cmp $0x0, %al
  jne .L__main__75_F_64
  jmp .L__main__74
.L__main__75:
  # %43: bool = phi @64 %check1.12 @74 %check4.5
  # br %43 @76 @77
  cmp $0x0, %al
  jne .L__main__76
  jmp .L__main__77_F_75
.L__main__75_F_64:
  jmp .L__main__75
.L__main__74:
  # %check4.5: bool = load %check4.ptr
  movb 12(%rsp), %cl
  # jmp @75
  jmp .L__main__75_F_74
.L__main__76:
  # %check2.12: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # br %check2.12 @79 @78
  cmp $0x0, %cl
  jne .L__main__79_F_76
  jmp .L__main__78
.L__main__77:
  # %45: bool = phi @75 %43 @79 %44
  # br %45 @71 @72
  cmp $0x0, %al
  jne .L__main__71
  jmp .L__main__72
.L__main__77_F_75:
  jmp .L__main__77
.L__main__79:
  # %44: bool = phi @76 %check2.12 @78 %check3.5
  # jmp @77
  jmp .L__main__77_F_79
.L__main__79_F_76:
  jmp .L__main__79
.L__main__78:
  # %check3.5: bool = load %check3.ptr
  movb 13(%rsp), %al
  # jmp @79
  jmp .L__main__79_F_78
.L__main__77_F_79:
  movb %cl, %al
  jmp .L__main__77
.L__main__71:
  # jmp @73
  jmp .L__main__73
.L__main__72:
  # %46: i32 = const 14
  # ret %46
  movl $0xe, %eax
  jmp .L__main__E
.L__main__73:
  # %check2.13: bool = load %check2.ptr
  movb 14(%rsp), %al
  # br %check2.13 @84 @83
  cmp $0x0, %al
  jne .L__main__84_F_73
  jmp .L__main__83
.L__main__84:
  # %48: bool = phi @73 %check2.13 @86 %47
  # br %48 @88 @87
  cmp $0x0, %al
  jne .L__main__88_F_84
  jmp .L__main__87
.L__main__84_F_73:
  jmp .L__main__84
.L__main__83:
  # %check3.6: bool = load %check3.ptr
  movb 13(%rsp), %cl
  # br %check3.6 @85 @86
  cmp $0x0, %cl
  jne .L__main__85
  jmp .L__main__86_F_83
.L__main__88:
  # %49: bool = phi @84 %48 @87 %check5.1
  # br %49 @80 @81
  cmp $0x0, %al
  jne .L__main__80
  jmp .L__main__81
.L__main__88_F_84:
  jmp .L__main__88
.L__main__87:
  # %check5.1: bool = load %check5.ptr
  movb 11(%rsp), %cl
  # jmp @88
  jmp .L__main__88_F_87
.L__main__80:
  # jmp @82
  jmp .L__main__82
.L__main__81:
  # %50: i32 = const 15
  # ret %50
  movl $0xf, %eax
  jmp .L__main__E
.L__main__82:
  # %check1.13: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.13 @92 @93
  cmp $0x0, %al
  jne .L__main__92
  jmp .L__main__93_F_82
.L__main__92:
  # %check2.14: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @93
  jmp .L__main__93_F_92
.L__main__93:
  # %51: bool = phi @82 %check1.13 @92 %check2.14
  # br %51 @95 @94
  cmp $0x0, %al
  jne .L__main__95_F_93
  jmp .L__main__94
.L__main__93_F_82:
  jmp .L__main__93
.L__main__93_F_92:
  movb %cl, %al
  jmp .L__main__93
.L__main__95:
  # %53: bool = phi @93 %51 @97 %52
  # br %53 @98 @99
  cmp $0x0, %al
  jne .L__main__98
  jmp .L__main__99_F_95
.L__main__95_F_93:
  jmp .L__main__95
.L__main__94:
  # %check3.7: bool = load %check3.ptr
  movb 13(%rsp), %cl
  # br %check3.7 @96 @97
  cmp $0x0, %cl
  jne .L__main__96
  jmp .L__main__97_F_94
.L__main__98:
  # %check5.2: bool = load %check5.ptr
  movb 11(%rsp), %cl
  # jmp @99
  jmp .L__main__99_F_98
.L__main__99:
  # %54: bool = phi @95 %53 @98 %check5.2
  # br %54 @101 @100
  cmp $0x0, %al
  jne .L__main__101_F_99
  jmp .L__main__100
.L__main__99_F_95:
  jmp .L__main__99
.L__main__99_F_98:
  movb %cl, %al
  jmp .L__main__99
.L__main__101:
  # %55: bool = phi @99 %54 @100 %check6.1
  # br %55 @89 @90
  cmp $0x0, %al
  jne .L__main__89
  jmp .L__main__90
.L__main__101_F_99:
  jmp .L__main__101
.L__main__100:
  # %check6.1: bool = load %check6.ptr
  movb 10(%rsp), %cl
  # jmp @101
  jmp .L__main__101_F_100
.L__main__89:
  # %56: i32 = const 16
  # ret %56
  movl $0x10, %eax
  jmp .L__main__E
.L__main__90:
  # jmp @91
  jmp .L__main__91
.L__main__91:
  # %check1.14: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.14 @104 @105
  cmp $0x0, %al
  jne .L__main__104
  jmp .L__main__105_F_91
.L__main__104:
  # %check2.15: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # jmp @105
  jmp .L__main__105_F_104
.L__main__105:
  # %57: bool = phi @91 %check1.14 @104 %check2.15
  # br %57 @107 @106
  cmp $0x0, %al
  jne .L__main__107_F_105
  jmp .L__main__106
.L__main__105_F_91:
  jmp .L__main__105
.L__main__105_F_104:
  movb %cl, %al
  jmp .L__main__105
.L__main__107:
  # %61: bool = phi @105 %57 @113 %60
  # br %61 @102 @103
  cmp $0x0, %al
  jne .L__main__102
  jmp .L__main__103
.L__main__107_F_105:
  jmp .L__main__107
.L__main__106:
  # %check3.8: bool = load %check3.ptr
  movb 13(%rsp), %cl
  # br %check3.8 @108 @109
  cmp $0x0, %cl
  jne .L__main__108
  jmp .L__main__109_F_106
.L__main__102:
  # %62: i32 = const 17
  # ret %62
  movl $0x11, %eax
  jmp .L__main__E
.L__main__103:
  # %check1.15: bool = load %check1.ptr
  movb 15(%rsp), %al
  # br %check1.15 @117 @118
  cmp $0x0, %al
  jne .L__main__117
  jmp .L__main__118_F_103
.L__main__117:
  # %check2.16: bool = load %check2.ptr
  movb 14(%rsp), %cl
  # %63: bool = not %check2.16
  movb %cl, %al
  xor $0x1, %al
  # jmp @118
  jmp .L__main__118_F_117
.L__main__118:
  # %64: bool = phi @103 %check1.15 @117 %63
  # br %64 @114 @115
  cmp $0x0, %al
  jne .L__main__114
  jmp .L__main__115
.L__main__118_F_103:
  jmp .L__main__118
.L__main__118_F_117:
  jmp .L__main__118
.L__main__114:
  # jmp @116
  jmp .L__main__116
.L__main__115:
  # %65: i32 = const 18
  # ret %65
  movl $0x12, %eax
  jmp .L__main__E
.L__main__116:
  # %check1.16: bool = load %check1.ptr
  movb 15(%rsp), %al
  # %66: bool = not %check1.16
  movb %al, %cl
  xor $0x1, %cl
  # br %66 @122 @121
  cmp $0x0, %cl
  jne .L__main__122_F_116
  jmp .L__main__121
.L__main__122:
  # %67: bool = phi @116 %66 @121 %check2.17
  # br %67 @119 @120
  cmp $0x0, %cl
  jne .L__main__119
  jmp .L__main__120
.L__main__122_F_116:
  jmp .L__main__122
.L__main__121:
  # %check2.17: bool = load %check2.ptr
  movb 14(%rsp), %al
  # jmp @122
  jmp .L__main__122_F_121
.L__main__119:
  # %68: i32 = const 19
  # ret %68
  movl $0x13, %eax
  jmp .L__main__E
.L__main__120:
  # %69: i32 = const 0
  # ret %69
  movl $0x0, %eax
  jmp .L__main__E
.L__main__122_F_121:
  movb %al, %cl
  jmp .L__main__122
.L__main__108:
  # %check4.8: bool = load %check4.ptr
  movb 12(%rsp), %al
  # jmp @109
  jmp .L__main__109_F_108
.L__main__109:
  # %58: bool = phi @106 %check3.8 @108 %check4.8
  # br %58 @111 @110
  cmp $0x0, %cl
  jne .L__main__111_F_109
  jmp .L__main__110
.L__main__109_F_106:
  jmp .L__main__109
.L__main__109_F_108:
  movb %al, %cl
  jmp .L__main__109
.L__main__111:
  # %59: bool = phi @109 %58 @110 %check6.2
  # br %59 @112 @113
  cmp $0x0, %cl
  jne .L__main__112
  jmp .L__main__113_F_111
.L__main__111_F_109:
  jmp .L__main__111
.L__main__110:
  # %check6.2: bool = load %check6.ptr
  movb 10(%rsp), %al
  # jmp @111
  jmp .L__main__111_F_110
.L__main__112:
  # %check5.3: bool = load %check5.ptr
  movb 11(%rsp), %al
  # jmp @113
  jmp .L__main__113_F_112
.L__main__113:
  # %60: bool = phi @111 %59 @112 %check5.3
  # jmp @107
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
  # %check4.7: bool = load %check4.ptr
  movb 12(%rsp), %al
  # jmp @97
  jmp .L__main__97_F_96
.L__main__97:
  # %52: bool = phi @94 %check3.7 @96 %check4.7
  # jmp @95
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
  # %check4.6: bool = load %check4.ptr
  movb 12(%rsp), %al
  # jmp @86
  jmp .L__main__86_F_85
.L__main__86:
  # %47: bool = phi @83 %check3.6 @85 %check4.6
  # jmp @84
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
  # %check3.2: bool = load %check3.ptr
  movb 13(%rsp), %al
  # jmp @52
  jmp .L__main__52_F_51
.L__main__52:
  # %32: bool = phi @49 %check1.9 @51 %check3.2
  # jmp @50
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
  # %check4.1: bool = load %check4.ptr
  movb 12(%rsp), %al
  # jmp @43
  jmp .L__main__43_F_42
.L__main__43:
  # %28: bool = phi @40 %check3.1 @42 %check4.1
  # jmp @41
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
