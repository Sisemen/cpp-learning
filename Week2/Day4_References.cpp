#include <iostream>

// Function using REFERENCE
void AddByReference(int& x)
{
    x = x + 10;
}

// Function using POINTER
void AddByPointer(int* x)
{
    if (x != nullptr)
    {
        *x = *x + 10;
    }
}

void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void Swap(int* a, int* b)
{
    if (a != nullptr && b != nullptr)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

int main()
{
    // Exercise 1: References basic
    std::cout << "=== REFERENCES ===" << std::endl;

    int x = 5;
    int& ref = x;  // ref is an alias for x

    std::cout << "x: " << x << std::endl;
    std::cout << "ref: " << ref << std::endl;  // No * needed!

    ref = 20;  // Modify x through ref
    std::cout << "After ref = 20: x = " << x << std::endl;

    std::cout << std::endl;

    // Exercise 2: References in functions
    std::cout << "=== REFERENCES IN FUNCTIONS ===" << std::endl;

    int value = 100;
    std::cout << "Before: " << value << std::endl;
    AddByReference(value);
    std::cout << "After AddByReference: " << value << std::endl;

    std::cout << std::endl;

    // Exercise 3: Pointers in functions
    std::cout << "=== POINTERS IN FUNCTIONS ===" << std::endl;

    int health = 50;
    std::cout << "Before: " << health << std::endl;
    AddByPointer(&health);  // Must pass address
    std::cout << "After AddByPointer: " << health << std::endl;

    std::cout << std::endl;

    // Exercise 4: Reference vs Pointer comparison
    std::cout << "=== COMPARISON ===" << std::endl;

    int score = 100;
    int& score_ref = score;
    int* score_ptr = &score;

    std::cout << "score: " << score << std::endl;
    std::cout << "score_ref: " << score_ref << " (no * needed)" << std::endl;
    std::cout << "score_ptr: " << score_ptr << " (address)" << std::endl;
    std::cout << "*score_ptr: " << *score_ptr << " (* needed)" << std::endl;

    // Both can modify
    score_ref = 200;
    std::cout << "After score_ref = 200: " << score << std::endl;

    *score_ptr = 300;
    std::cout << "After *score_ptr = 300: " << score << std::endl;

    // Exercise 5: Swap function
    std::cout << "=== SWAP FUNCTION ===" << std::endl;

    int a = 10;
    int b = 20;

    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    Swap(a, b);
    std::cout << "After swap (by reference): a = " << a << ", b = " << b << std::endl;

    Swap(&a, &b);
    std::cout << "After swap (by pointer): a = " << a << ", b = " << b << std::endl;

    return 0;
}