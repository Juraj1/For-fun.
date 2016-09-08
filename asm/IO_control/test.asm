.section .data
  msgWrite:
    .ascii "Zadejte cislo: \n"
    lenWrite = . - msgWrite 

  msgRead:
    .ascii "Zadane cislo: "
    lenRead = . - msgRead

.section .bss
  .lcomm buff 32 # allocating 32 bytes of memory
  
  # macro for write out
  # usage: write $string, $size
  .macro write buff, buff_size
    movl $1, %ebx         # stdout
    movl $4, %eax         # sys_call write
    movl \buff_size, %edx # velikost zpravy do registru
    movl \buff, %ecx      # zprava do registru
    int $0x80             # kernel call
  .endm
  
  # macro for read
  # usage: read $variable, $size
  .macro read buff, buff_size
    movl $3, %eax         # read
    movl $2, %ebx         # stdin
    movl \buff, %ecx      # move buffer to ecx
    movl \buff_size, %edx # move size of the buffer to edx
    int $0x80             # kernel call
  .endm

.section .text
  .global _start

  _start:

    # vypsani zadosi
    write $msgWrite, $lenWrite

    # cteni 32 bajtu
    read $buff, $32

    # vypsani odpovedi 
    write $msgRead, $lenRead
    
    # vypsani odpovedi 
    write $buff, $32
    
    # ukoncovaci rutina
  _exit:
    movl $0, %ebx   # navratovy kod
    movl $1, %eax   # kernel call for exit
    int $0x80

