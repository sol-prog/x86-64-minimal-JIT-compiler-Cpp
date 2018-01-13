// hello_0.cpp
#include <iostream>
#include <string>

int main() {
    // Get the user name
    std::string name;
    std::cout << "What is your name?\n";
    std::getline(std::cin, name);
    std::string hello_name = "Hello, " + name + "!\n";

    // Greet the user
    std::cout << hello_name;
}
