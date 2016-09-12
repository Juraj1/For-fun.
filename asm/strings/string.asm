.section .data
  string:
    .ascii "Random String\n"
    lenString = . - string
  
  delimiter:
    .ascii "**********\n"
    lenDelimiter = . - delimiter

.section .bss
  .lcomm outNumber 64 # vystupni cislo
  
  # macro for write out
  # usage: write $string, $size
  .macro write buff, buff_size
    # zaloha registru
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx 
    
    movl $1, %ebx         # stdout
    movl $4, %eax         # sys_call write
    movl \buff_size, %edx # velikost zpravy do registru
    movl \buff, %ecx      # zprava do registru
    int $0x80             # kernel call
    
    # obnova registru
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax 
  .endm
  
  # macro for read
  # usage: read $variable, $size
  .macro read buff, buff_size
    # zaloha registru
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx 
    
    movl $3, %eax         # read
    movl $2, %ebx         # stdin
    movl \buff, %ecx      # move buffer to ecx
    movl \buff_size, %edx # move size of the buffer to edx
    int $0x80             # kernel call

    # obnova registru
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax 

  .endm

.section .text
  .global _start

  _start:
  
#### strlen ####
  xorq %rcx, %rcx
  movl $string, %edi

strlenLoop:
  cmpb $10, (%edi)       # mam novy radek
  je strlenEnd 

  incq %rcx
  incl %edi
  write $string, $lenString
  jmp strlenLoop
strlenEnd:
  
  write $delimiter, $lenDelimiter

  movq $outNumber, %rsi   # hazim si alokovanou pamet do rsi
  movq %rcx, %rax         # hodim si citac do rax
  xor %rcx, %rcx          # vycistim rcx, pouziju jako citac iteraci
  movq $10, %rbx          # hodim si do rbx delitel: 10

conversionStart:
  xorq %rdx, %rdx               # cistim rdx
  divq %rbx                     # a delim
  cmp $0, %rax                  # kontrola vysledku na nulu => posunul jsem se na konec
  je conversionEnd              # skacu ven ze smycky
  addq $0x30, %rdx              # zbytek v rdx, prictu 0x30 (to je 0) a hazim do pameti
  movq %rdx, (%rcx,%rsi)        # hodim si char v rdx do pointru rsi s offsetem rcx
  write $delimiter, $lenDelimiter
  jmp conversionStart 
conversionEnd:
  
  # vypiseme vysledek
  write $outNumber, $64
  

  # ukoncovaci rutina
  _exit:
    movl $0, %ebx   # navratovy kod
    movl $1, %eax   # kernel call for exit
    int $0x80
