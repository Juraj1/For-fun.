FILE=string

do:
	as -gstabs+ "${FILE}.asm" -o "${FILE}.o"
	ld "${FILE}.o" -o strlen
	rm "${FILE}.o"

clean:
	rm -rf strlen
