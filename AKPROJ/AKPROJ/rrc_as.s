	.file	"assembly.cpp"
	.intel_syntax noprefix
 # GNU C++14 (MinGW.org GCC Build-2) version 9.2.0 (mingw32)
 #	compiled by GNU C version 9.2.0, GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.21-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed:  -iprefix c:\mingw\bin\../lib/gcc/mingw32/9.2.0/
 # .\assembly.cpp -masm=intel -mtune=generic -march=i586 -Og -fverbose-asm
 # options enabled:  -faggressive-loop-optimizations -fassume-phsa
 # -fasynchronous-unwind-tables -fauto-inc-dec -fcombine-stack-adjustments
 # -fcommon -fcompare-elim -fcprop-registers -fdefer-pop
 # -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
 # -feliminate-unused-debug-types -fexceptions -fforward-propagate
 # -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm -fgnu-runtime
 # -fgnu-unique -fguess-branch-probability -fident -finline
 # -finline-atomics -fipa-profile -fipa-pure-const -fipa-reference
 # -fipa-reference-addressable -fipa-stack-alignment -fira-hoist-pressure
 # -fira-share-save-slots -fira-share-spill-slots -fivopts
 # -fkeep-inline-dllexport -fkeep-static-consts -fleading-underscore
 # -flifetime-dse -flto-odr-type-merging -fmath-errno -fmerge-constants
 # -fmerge-debug-strings -fomit-frame-pointer -fpeephole -fplt
 # -fprefetch-loop-arrays -freg-struct-return -freorder-blocks
 # -fsched-critical-path-heuristic -fsched-dep-count-heuristic
 # -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
 # -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
 # -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
 # -fset-stack-executable -fshow-column -fshrink-wrap
 # -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
 # -fsplit-wide-types -fssa-backprop -fstdarg-opt
 # -fstrict-volatile-bitfields -fsync-libcalls -ftoplevel-reorder
 # -ftrapping-math -ftree-builtin-call-dce -ftree-ccp -ftree-ch
 # -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim -ftree-dce
 # -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
 # -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
 # -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
 # -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-ter
 # -funit-at-a-time -funwind-tables -fverbose-asm -fzero-initialized-in-bss
 # -m32 -m80387 -m96bit-long-double -maccumulate-outgoing-args
 # -malign-double -malign-stringops -mavx256-split-unaligned-load
 # -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387
 # -mieee-fp -mlong-double-80 -mms-bitfields -mno-red-zone -mno-sse4
 # -mpush-args -msahf -mstack-arg-probe -mstv -mvzeroupper

	.text
	.def	__Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
__Z41__static_initialization_and_destruction_0ii:
LFB2024:
	.cfi_startproc
	cmp	eax, 1	 # tmp84,
	je	L7	 #,
L4:
	ret	
L7:
 # .\assembly.cpp:28: }
	cmp	edx, 65535	 # __priority,
	jne	L4	 #,
 # .\assembly.cpp:28: }
	sub	esp, 28	 #,
	.cfi_def_cfa_offset 32
 # c:\mingw\lib\gcc\mingw32\9.2.0\include\c++\iostream:74:   static ios_base::Init __ioinit;
	mov	ecx, OFFSET FLAT:__ZStL8__ioinit	 #,
	call	__ZNSt8ios_base4InitC1Ev	 #
	mov	DWORD PTR [esp], OFFSET FLAT:___tcf_0	 #,
	call	_atexit	 #
 # .\assembly.cpp:28: }
	add	esp, 28	 #,
	.cfi_def_cfa_offset 4
	ret	
	.cfi_endproc
LFE2024:
	.def	___tcf_0;	.scl	3;	.type	32;	.endef
___tcf_0:
LFB2025:
	.cfi_startproc
	sub	esp, 12	 #,
	.cfi_def_cfa_offset 16
 # c:\mingw\lib\gcc\mingw32\9.2.0\include\c++\iostream:74:   static ios_base::Init __ioinit;
	mov	ecx, OFFSET FLAT:__ZStL8__ioinit	 #,
	call	__ZNSt8ios_base4InitD1Ev	 #
	add	esp, 12	 #,
	.cfi_def_cfa_offset 4
	ret	
	.cfi_endproc
LFE2025:
	.globl	__Z3rrcRhS_
	.def	__Z3rrcRhS_;	.scl	2;	.type	32;	.endef
__Z3rrcRhS_:
LFB1556:
	.cfi_startproc
	mov	eax, DWORD PTR [esp+4]	 # byte, byte
	mov	edx, DWORD PTR [esp+8]	 # rotCarry, rotCarry
 # .\assembly.cpp:5: 	if (rotCarry == 0)
	cmp	BYTE PTR [edx], 0	 # *rotCarry_17(D),
	jne	L11	 #,
 # .\assembly.cpp:7: 		if (byte % 2 == 1)
	test	BYTE PTR [eax], 1	 # *byte_18(D),
	je	L12	 #,
 # .\assembly.cpp:9: 			rotCarry = 1;
	mov	BYTE PTR [edx], 1	 # *rotCarry_17(D),
L13:
 # .\assembly.cpp:14: 		byte >>= 1;
	movzx	edx, BYTE PTR [eax]	 # *byte_18(D), *byte_18(D)
	sar	edx	 # tmp100
	mov	BYTE PTR [eax], dl	 # *byte_18(D), tmp100
	ret	
L12:
 # .\assembly.cpp:12: 			rotCarry = 0;
	mov	BYTE PTR [edx], 0	 # *rotCarry_17(D),
	jmp	L13	 #
L11:
 # .\assembly.cpp:18: 		if (byte % 2 == 1)
	test	BYTE PTR [eax], 1	 # *byte_18(D),
	je	L15	 #,
 # .\assembly.cpp:20: 			rotCarry = 1;
	mov	BYTE PTR [edx], 1	 # *rotCarry_17(D),
L16:
 # .\assembly.cpp:25: 		byte >>= 1;
	movzx	edx, BYTE PTR [eax]	 # *byte_18(D), *byte_18(D)
	sar	edx	 # tmp103
 # .\assembly.cpp:26: 		byte += 0b10000000;
	add	edx, -128	 # tmp104,
	mov	BYTE PTR [eax], dl	 # *byte_18(D), tmp104
 # .\assembly.cpp:28: }
	ret	
L15:
 # .\assembly.cpp:23: 			rotCarry = 0;
	mov	BYTE PTR [edx], 0	 # *rotCarry_17(D),
	jmp	L16	 #
	.cfi_endproc
LFE1556:
	.def	__GLOBAL__sub_I__Z3rrcRhS_;	.scl	3;	.type	32;	.endef
__GLOBAL__sub_I__Z3rrcRhS_:
LFB2026:
	.cfi_startproc
	sub	esp, 12	 #,
	.cfi_def_cfa_offset 16
 # .\assembly.cpp:28: }
	mov	edx, 65535	 #,
	mov	eax, 1	 #,
	call	__Z41__static_initialization_and_destruction_0ii	 #
	add	esp, 12	 #,
	.cfi_def_cfa_offset 4
	ret	
	.cfi_endproc
LFE2026:
	.section	.ctors,"w"
	.align 4
	.long	__GLOBAL__sub_I__Z3rrcRhS_
.lcomm __ZStL8__ioinit,1,1
	.ident	"GCC: (MinGW.org GCC Build-2) 9.2.0"
	.def	__ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	_atexit;	.scl	2;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
