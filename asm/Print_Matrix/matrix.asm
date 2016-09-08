# data part
.section .data
  msgRadky:
    .ascii "Pocet radku matice: \n"
    lenRadky = . - msgRadky

  msgSloupce:
    .ascii "Pocet sloupcu matice: \n"
    lenSloupce = . - msgSloupce

  writeOne:
    .ascii "1 "
    lenOne = . - writeOne

  writeZero:
    .ascii "0 "
    lenZero = . - writeZero

  writeNewLine:
    .ascii "\n"
    lenNewLine = . - writeNewLine

  bufferSize:
    .int 32

# static allocation of memory
.section .bss
  # hodnoty brany jako string
  .lcomm Lines 32         # allocation of 32 bytes of memory for line integer
  .lcomm Columns 32       # allocation of 32 bytes of memory for column integer
  # hodnoty jako int32_t
  .lcomm intRows 4        # allocation of 4 bytes for unsigned integer
  .lcomm intColumns 4     # allocation of 4 bytes for unsigned integer
  .lcomm multiplyNumber 1 # number which will multiply the character


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
  # vypisu dotaz na pocet radku
  write $msgRadky, $lenRadky

  # cteni 32 bytu
  read $Lines, $bufferSize

  # vypisu dotaz na pocet sloupcu
  write $msgSloupce, $lenSloupce

  # prectu 32 bytu
  read $Columns, $bufferSize

  # Precteno uz mam, tak is hezky prevedu chary na integer.
  # Musim iterovat prez promennou Lines a pokud je cislo mezi 0x30 a 0x39 vcetne,
  # tak od neho odectu 0x30 a mam integerovskou hodnotu. 
  # Kazdy posun o byte vlevo znamena, ze musim vynasobit cislo 10.
  
  xorq %rax, %rax         # nuluju RAX pro porovnavani
  xorq %rsi, %rsi         # vycistim si muj pointer na string
  xorb %cl, %cl           # vycistim si registr CL, bo to bude muj citac shiftu
  movl $Lines, %esi       # ulozim si pointer na string u radku

  movq 32(%rsi), %rax     # vytahnu si ascii hodnotu co tam je
  cmpq $0x0, %rax         # porovnam si esi na konec stringu

  #TODO dopsat iterace nad stringama a zbytek
  
  
  
  # ukoncovaci rutina
  _exit:
    movl $0, %ebx   # navratovy kod
    movl $1, %eax   # kernel call for exit
    int $0x80
