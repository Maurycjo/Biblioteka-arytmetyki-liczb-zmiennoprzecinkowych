	.file	"inc_ass.cpp"
	.intel_syntax noprefix
 # GNU C++14 (MinGW.org GCC Build-2) version 9.2.0 (mingw32)
 #	compiled by GNU C version 9.2.0, GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.21-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed:  -iprefix c:\mingw\bin\../lib/gcc/mingw32/9.2.0/
 # .\inc_ass.cpp -masm=intel -mtune=generic -march=i586 -Og -fverbose-asm
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
LFB2384:
	.cfi_startproc
	cmp	eax, 1	 # tmp84,
	je	L7	 #,
L4:
	ret	
L7:
 # .\inc_ass.cpp:19: }
	cmp	edx, 65535	 # __priority,
	jne	L4	 #,
 # .\inc_ass.cpp:19: }
	sub	esp, 28	 #,
	.cfi_def_cfa_offset 32
 # c:\mingw\lib\gcc\mingw32\9.2.0\include\c++\iostream:74:   static ios_base::Init __ioinit;
	mov	ecx, OFFSET FLAT:__ZStL8__ioinit	 #,
	call	__ZNSt8ios_base4InitC1Ev	 #
	mov	DWORD PTR [esp], OFFSET FLAT:___tcf_0	 #,
	call	_atexit	 #
 # .\inc_ass.cpp:19: }
	add	esp, 28	 #,
	.cfi_def_cfa_offset 4
	ret	
	.cfi_endproc
LFE2384:
	.def	___tcf_0;	.scl	3;	.type	32;	.endef
___tcf_0:
LFB2385:
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
LFE2385:
	.globl	__Z11incSevBytesRSt6vectorIhSaIhEE
	.def	__Z11incSevBytesRSt6vectorIhSaIhEE;	.scl	2;	.type	32;	.endef
__Z11incSevBytesRSt6vectorIhSaIhEE:
LFB1914:
	.cfi_startproc
	push	esi	 #
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	push	ebx	 #
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	mov	esi, DWORD PTR [esp+12]	 # number, number
 # c:\mingw\lib\gcc\mingw32\9.2.0\include\c++\bits\stl_vector.h:916:       { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
	mov	eax, DWORD PTR [esi+4]	 # _13, MEM[(const struct vector *)number_9(D)].D.39195._M_impl.D.38498._M_finish
 # c:\mingw\lib\gcc\mingw32\9.2.0\include\c++\bits\stl_vector.h:916:       { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
	sub	eax, DWORD PTR [esi]	 # _12, MEM[(const struct vector *)number_9(D)].D.39195._M_impl.D.38498._M_start
 # .\inc_ass.cpp:7: 	for (int i = number.size() - 1; i >= 0; i--)
	sub	eax, 1	 # i,
L13:
 # .\inc_ass.cpp:7: 	for (int i = number.size() - 1; i >= 0; i--)
	test	eax, eax	 # i
	js	L10	 #,
 # c:\mingw\lib\gcc\mingw32\9.2.0\include\c++\bits\stl_vector.h:1043: 	return *(this->_M_impl._M_start + __n);
	mov	edx, eax	 # _19, i
	add	edx, DWORD PTR [esi]	 # _19, number_9(D)->D.39195._M_impl.D.38498._M_start
 # .\inc_ass.cpp:9: 		if (uint8_t(number[i] + 1) > number[i])
	movzx	ebx, BYTE PTR [edx]	 # _3, *_19
	lea	ecx, [ebx+1]	 # _4,
 # .\inc_ass.cpp:9: 		if (uint8_t(number[i] + 1) > number[i])
	cmp	bl, cl	 # _3, _4
	jb	L15	 #,
 # .\inc_ass.cpp:16: 			number[i]++;
	mov	BYTE PTR [edx], cl	 # *_19, _4
 # .\inc_ass.cpp:7: 	for (int i = number.size() - 1; i >= 0; i--)
	sub	eax, 1	 # i,
	jmp	L13	 #
L15:
 # .\inc_ass.cpp:11: 			number[i]++;
	mov	BYTE PTR [edx], cl	 # *_19, _4
L10:
 # .\inc_ass.cpp:19: }
	pop	ebx	 #
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	pop	esi	 #
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret	
	.cfi_endproc
LFE1914:
	.def	__GLOBAL__sub_I__Z11incSevBytesRSt6vectorIhSaIhEE;	.scl	3;	.type	32;	.endef
__GLOBAL__sub_I__Z11incSevBytesRSt6vectorIhSaIhEE:
LFB2386:
	.cfi_startproc
	sub	esp, 12	 #,
	.cfi_def_cfa_offset 16
 # .\inc_ass.cpp:19: }
	mov	edx, 65535	 #,
	mov	eax, 1	 #,
	call	__Z41__static_initialization_and_destruction_0ii	 #
	add	esp, 12	 #,
	.cfi_def_cfa_offset 4
	ret	
	.cfi_endproc
LFE2386:
	.section	.ctors,"w"
	.align 4
	.long	__GLOBAL__sub_I__Z11incSevBytesRSt6vectorIhSaIhEE
.lcomm __ZStL8__ioinit,1,1
	.ident	"GCC: (MinGW.org GCC Build-2) 9.2.0"
	.def	__ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	_atexit;	.scl	2;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
