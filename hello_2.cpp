// hello_2.cpp
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

// Add the message size
void append_message_size(std::vector<uint8_t> &machine_code, const std::string &hello_name);

// Print the content of the machine_code vector for debugging purposes
void show_machine_code(const std::vector<uint8_t> &machine_code);


int main() {
    // Get the user name
    std::string name;
    std::cout << "What is your name?\n";
    std::getline(std::cin, name);
    std::string hello_name = "Hello, " + name + "!\n";

    // Store the machine code in memory
    std::vector<uint8_t> machine_code {
        #ifdef __linux__
        0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00,           //Store the "write" system call number 0x01 for Linux
        #elif __APPLE__
        0x48, 0xc7, 0xc0, 0x04, 0x00, 0x00, 0x02,           //Store the "write" system call number 0x02000004 for macOS
        #endif
        0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00,           //Store stdin file descriptor 0x01
        0x48, 0x8d, 0x35, 0x0a, 0x00, 0x00, 0x00,           //Store the location of the string to write (3 instructions from the current instruction pointer)
        0x48, 0xc7, 0xc2, 0x00, 0x00, 0x00, 0x00,           //Store the length of the string (initially zero)
        0x0f, 0x05,                                         //Execute the system call
        0xc3                                                //return instruction
    };

    // Add the message size
    append_message_size(machine_code, hello_name);

    //Append the message to the machine code vector:
    for(auto c : hello_name) {
        machine_code.push_back(c);
    }

    // Print the content of the machine_code vector for debugging purposes
    show_machine_code(machine_code);
}

// Add the message size
void append_message_size(std::vector<uint8_t> &machine_code, const std::string &hello_name) {
    size_t message_size = hello_name.length();

    machine_code[24] = (message_size & 0xFF) >> 0;
    machine_code[25] = (message_size & 0xFF00) >> 8;
    machine_code[26] = (message_size & 0xFF0000) >> 16;
    machine_code[27] = (message_size & 0xFF000000) >> 24;
}

// Print the content of the machine_code vector for debugging purposes
void show_machine_code(const std::vector<uint8_t> &machine_code) {
    int konto = 0;
    std::cout << "\nMachine code generated:\n";
    std::cout << std::hex;
    for(auto e : machine_code) {
        std::cout << (int)e << " ";
        konto++;
        if(konto % 7 == 0) {
            std::cout << '\n';
        }
    }
    std::cout << std::dec;
    std::cout << "\n\n";
}
