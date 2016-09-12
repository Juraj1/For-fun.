FILE=string

do:
	as -gstabs+ "${FILE}.asm" -o "${FILE}.o"
	ld "${FILE}.o" -o asd
	rm "${FILE}.o"
