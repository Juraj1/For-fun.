.section .data
  string:
    .ascii "Random String\n"
    lenString = . - string

.section .bss
  .lcomm outNumber 64 # vystupni cislo
  
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
  
#### strlen ####
  xorq %rcx, %rcx
  movl $string, %edi

strlenLoop:
  cmpb $0x0, (%edi)       # mam nulovy znak
  je strlenEnd 

  incq %rcx
  incl %edi
  write $string, $lenString
  jmp strlenLoop
strlenEnd:


  # ukoncovaci rutina
  _exit:
    movl $0, %ebx   # navratovy kod
    movl $1, %eax   # kernel call for exit
    int $0x80
