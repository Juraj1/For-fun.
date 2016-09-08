FILENAME=hello_world

ll:
	as -o  ${FILENAME}.o ${FILENAME}.asm
	ld -s -o ${FILENAME} ${FILENAME}.o

clean:
	rm -rf ${FILENAME}.o
	rm -rf ${FILENAME}
