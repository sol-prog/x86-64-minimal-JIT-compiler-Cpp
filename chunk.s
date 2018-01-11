# Enforce Intel syntax
.intel_syntax noprefix

# Call the "write" system function (man 2 write)
# ssize_t write(int fd, const void *buf, size_t count);
mov rax, 1							# Store the "write" system call number 0x1 for Linux or 0x2000004 for macOS
# Put the function arguments in the rdi, rsi, rdx, r10, r8, r9 registers
mov rdi, 1							# Store where to write stdin which is 0x1 for Linux and macOS
lea rsi, [rip + 0xa]				# Store the location of the string to write (0xa instructions from the current instruction pointer)
mov rdx, 17							# Store the length of the string
# Call the function
syscall
ret
.string "Hello, Your Name\n"
