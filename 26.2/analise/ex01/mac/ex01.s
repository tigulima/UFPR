
ex01:	file format mach-o arm64

Disassembly of section __TEXT,__text:

0000000100000328 <_main>:
100000328: d10043ff    	sub	sp, sp, #0x10
10000032c: 52800000    	mov	w0, #0x0                ; =0
100000330: b9000fff    	str	wzr, [sp, #0xc]
100000334: 52999ba8    	mov	w8, #0xccdd             ; =52445
100000338: 72b55768    	movk	w8, #0xaabb, lsl #16
10000033c: b9000be8    	str	w8, [sp, #0x8]
100000340: 52824268    	mov	w8, #0x1213             ; =4627
100000344: 72a20228    	movk	w8, #0x1011, lsl #16
100000348: b90007e8    	str	w8, [sp, #0x4]
10000034c: b9400be8    	ldr	w8, [sp, #0x8]
100000350: b94007e9    	ldr	w9, [sp, #0x4]
100000354: 0b090108    	add	w8, w8, w9
100000358: b9000be8    	str	w8, [sp, #0x8]
10000035c: 910043ff    	add	sp, sp, #0x10
100000360: d65f03c0    	ret
