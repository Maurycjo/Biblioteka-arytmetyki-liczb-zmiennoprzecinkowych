	.file	"add_asm.cpp"
	.intel_syntax noprefix
 # GNU C++14 (MinGW.org GCC Build-2) version 9.2.0 (mingw32)
 #	compiled by GNU C version 9.2.0, GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.21-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed:  -iprefix c:\mingw\bin\../lib/gcc/mingw32/9.2.0/
 # .\add_asm.cpp -masm=intel -mtune=generic -march=i586 -Og -fverbose-asm
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
 # .\add_asm.cpp:21: }
	cmp	edx, 65535	 # __priority,
	jne	L4	 #,
 # .\add_asm.cpp:21: }
	sub	esp, 28	 #,
	.cfi_def_cfa_offset 32
 # c:\mingw\lib\gcc\mingw32\9.2.0\include\c++\iostream:74:   static ios_base::Init __ioinit;
	mov	ecx, OFFSET FLAT:__ZStL8__ioinit	 #,
	call	__ZNSt8ios_base4InitC1Ev	 #
	mov	DWORD PTR [esp], OFFSET FLAT:___tcf_0	 #,
	call	_atexit	 #
 # .\add_asm.cpp:21: }
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
	.globl	__Z11addTwoByteshhRh
	.def	__Z11addTwoByteshhRh;	.scl	2;	.type	32;	.endef
__Z11addTwoByteshhRh:
LFB1556:
	.cfi_startproc
	mov	edx, DWORD PTR [esp+12]	 # carry, carry
 # .\add_asm.cpp:8: 	uint16_t tempResult = byteA + byteB + carry;
	movzx	eax, BYTE PTR [esp+4]	 # byteA, byteA
	movzx	ecx, BYTE PTR [esp+8]	 # byteB, byteB
	add	eax, ecx	 # _3, byteB
 # .\add_asm.cpp:8: 	uint16_t tempResult = byteA + byteB + carry;
	movzx	ecx, BYTE PTR [edx]	 # _5, *carry_11(D)
 # .\add_asm.cpp:8: 	uint16_t tempResult = byteA + byteB + carry;
	add	eax, ecx	 # tempResult, _5
 # .\add_asm.cpp:11: 	if ((tempResult & mask) == tempResult)
	movzx	ecx, al	 # _6, tempResult
 # .\add_asm.cpp:11: 	if ((tempResult & mask) == tempResult)
	cmp	cx, ax	 # _6, tempResult
	je	L13	 #,
 # .\add_asm.cpp:17: 		carry = 1;
	mov	BYTE PTR [edx], 1	 # *carry_11(D),
 # .\add_asm.cpp:21: }
	ret	
L13:
 # .\add_asm.cpp:13: 		carry = 0; // brak przeniesienia
	mov	BYTE PTR [edx], 0	 # *carry_11(D),
	ret	
	.cfi_endproc
LFE1556:
	.def	__GLOBAL__sub_I__Z11addTwoByteshhRh;	.scl	3;	.type	32;	.endef
__GLOBAL__sub_I__Z11addTwoByteshhRh:
LFB2026:
	.cfi_startproc
	sub	esp, 12	 #,
	.cfi_def_cfa_offset 16
 # .\add_asm.cpp:21: }
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
	.long	__GLOBAL__sub_I__Z11addTwoByteshhRh
.lcomm __ZStL8__ioinit,1,1
	.ident	"GCC: (MinGW.org GCC Build-2) 9.2.0"
	.def	__ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	_atexit;	.scl	2;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
