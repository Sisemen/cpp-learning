#include <iostream>

int main()
{
    // Basic calculator
    int num1 = 234;
    int num2 = 17;

    std::cout << "Number 1: " << num1 << std::endl;
    std::cout << "Number 2: " << num2 << std::endl;
    std::cout << std::endl;

    // Math operations
    std::cout << "Addition: " << num1 + num2 << std::endl;
    std::cout << "Subtraction: " << num1 - num2 << std::endl;
    std::cout << "Multiplication: " << num1 * num2 << std::endl;
    std::cout << "Division (int): " << num1 / num2 << std::endl;
    std::cout << "Division (double): " << (double)num1 / num2 << std::endl;
    std::cout << "Remainder: " << num1 % num2 << std::endl;
    std::cout << "Double result: " << (double)num1 / num2 << std::endl;

    std::cout << "Remainder of 20 % 3: " << 20 % 3 << std::endl;
    std::cout << "Division of 20 / 3: " << 20 / 3 << std::endl;
    std::cout << "Division of 20.0 / 3.0: " << 20.0 / 3.0 << std::endl;

    return 0;
}