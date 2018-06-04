FILE=string

do:
	as -gstabs+ "${FILE}.asm" -o "${FILE}.o"
	ld "${FILE}.o" -o binary
	rm "${FILE}.o"

clean:
	rm -rf binary
