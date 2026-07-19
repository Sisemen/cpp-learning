#include <iostream>

void safeDereference(int* ptr);

int main()
{
    // Exercise 1: Null pointer safety
    std::cout << "=== NULL POINTER SAFETY ===" << std::endl;

    int* ptr = nullptr;

    // WRONG - don't do this:
    // std::cout << *ptr;  // CRASH!

    // RIGHT - check first:
    if (ptr != nullptr)
    {
        std::cout << *ptr << std::endl;
    }
    else
    {
        std::cout << "Pointer is null, can't dereference" << std::endl;
    }

    std::cout << std::endl;

    // Exercise 2: Make it point to something
    std::cout << "=== POINTING TO SOMETHING ===" << std::endl;
    int value = 42;
    ptr = &value;  // Now it points to something

    if (ptr != nullptr)
    {
        std::cout << "ptr is now valid, value: " << *ptr << std::endl;
    }

    std::cout << std::endl;

    // Exercise 3: Pointer safety check
    std::cout << "=== SAFE POINTER FUNCTION ===" << std::endl;

    int x = 100;
    int* x_ptr = &x;

    // Safe function
    safeDereference(x_ptr);

    // Set to null
    x_ptr = nullptr;

    safeDereference(x_ptr);

    return 0;
}

void safeDereference(int* ptr)
{
    if (ptr != nullptr)
    {
        std::cout << "Value: " << *ptr << std::endl;
    }
    else
    {
        std::cout << "Pointer is null, can't dereference" << std::endl;
    }
}