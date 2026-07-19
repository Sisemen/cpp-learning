#include <iostream>

int Sum(int arr[5])
{
    int total = 0;
    int* ptr = &arr[0];  // Pointer to the first element
    int* end = &arr[5];  // Pointer to one past the last element

    while (ptr < end)
    {
        total += *ptr;
        ptr++;  // Move to next element
    }

    return total;
 }

int main()
{
    // Exercise 1: Basic pointer arithmetic
    std::cout << "=== POINTER ARITHMETIC ===" << std::endl;

    int arr[5] = { 10, 20, 30, 40, 50 };
    int* ptr = &arr[0];

    std::cout << "Array: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl << std::endl;

    // Exercise 2: Iterate using pointer arithmetic
    std::cout << "Iterate with pointer arithmetic:" << std::endl;
    ptr = &arr[0];  // Reset to beginning
    for (int i = 0; i < 5; i++)
    {
        std::cout << "ptr[" << i << "]: " << *ptr << std::endl;
        ptr++;  // Move to next
    }
    std::cout << std::endl;

    // Exercise 3: Pointer operations
    std::cout << "Pointer operations:" << std::endl;
    ptr = &arr[0];

    std::cout << "*ptr: " << *ptr << std::endl;           // 10
    std::cout << "*(ptr + 1): " << *(ptr + 1) << std::endl;  // 20
    std::cout << "*(ptr + 2): " << *(ptr + 2) << std::endl;  // 30
    std::cout << "*(ptr + 4): " << *(ptr + 4) << std::endl;  // 50
    std::cout << std::endl;

    // Exercise 4: Pointer vs array notation
    std::cout << "Pointer vs Array Notation:" << std::endl;
    ptr = &arr[0];

    std::cout << "arr[2] == " << arr[2] << std::endl;
    std::cout << "*(ptr + 2) == " << *(ptr + 2) << std::endl;
    std::cout << "(They're the same!)" << std::endl << std::endl;

    // Exercise 5: Pointer comparison (bounds checking)
    std::cout << "Iterate with bounds checking:" << std::endl;
    ptr = &arr[0];
    int* end = &arr[5];  // One past the last element

    while (ptr < end)
    {
        std::cout << *ptr << " ";
        ptr++;
    }
    std::cout << "\n(Safe iteration)" << std::endl;

    // Exercise 6: Iterate using pointer arithmetic
    std::cout << "Iterate with pointer arithmetic:" << std::endl;
    std::string strArr[5] = { "Alpha", "Beta", "Gamma", "Delta", "Epsilon" };
    std::string* strPtr = &strArr[0];  // Reset to beginning
    for (int i = 0; i < 5; i++)
    {
        std::cout << "strPtr[" << i << "]: " << *strPtr << std::endl;
        strPtr++;  // Move to next
    }
    std::cout << std::endl;

    // Exercise 7: Sum using pointer arithmetic
    std::cout << "Sum of array elements: " << Sum(arr) << std::endl;  // Call the function to sum the array elements)

    return 0;
}