#include <iostream>

// Function that uses stack
void StackExample()
{
    int x = 100;           // Stack
    std::string name = "Hero";  // Stack

    std::cout << "Inside StackExample: " << name << " = " << x << std::endl;
    // x and name are destroyed here
}

// Function that returns heap pointer (dangerous in old C++)
int* CreateHeapInt()
{
    int* ptr = new int(42);  // Heap - MUST cleanup outside
    return ptr;
}

std::string* CreateHeapString()
{
    std::string* ptr = new std::string("Hello, Heap!");  // Heap - MUST cleanup outside
    return ptr;
}

// Good function with smart pointer (Week 3 preview)
std::string DemonstrationFunction()
{
    std::string msg = "This will return properly";  // Stack
    return msg;  // Returned by value
}

void IncrementByReference(int& x)
{
    x++;
}

int main()
{
    std::cout << "=== STACK VS HEAP ===" << std::endl << std::endl;

    // Exercise 1: Stack allocation
    std::cout << "Exercise 1: Stack Allocation" << std::endl;
    StackExample();
    // x and name no longer exist, but no cleanup needed!
    std::cout << "(Variables auto-cleaned)" << std::endl << std::endl;

    // Exercise 2: Heap allocation
    std::cout << "Exercise 2: Heap Allocation" << std::endl;
    int* heap_value = CreateHeapInt();
    std::cout << "Heap value: " << *heap_value << std::endl;

    delete heap_value;  // MUST cleanup! (old way)
    heap_value = nullptr;  // Good practice
    std::cout << "(Manually cleaned up)" << std::endl << std::endl;

    // Exercise 3: Stack array
    std::cout << "Exercise 3: Stack Array (Small)" << std::endl;
    int arr_stack[5] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < 5; i++)
    {
        std::cout << arr_stack[i] << " ";
    }
    std::cout << "\n(Auto-cleaned)" << std::endl << std::endl;

    // Exercise 4: Heap array
    std::cout << "Exercise 4: Heap Array (Large)" << std::endl;
    int* arr_heap = new int[10];
    for (int i = 0; i < 10; i++)
    {
        arr_heap[i] = i * 10;
        std::cout << arr_heap[i] << " ";
    }

    delete[] arr_heap;  // MUST use delete[] for arrays!
    arr_heap = nullptr;
    std::cout << "\n(Manually cleaned)" << std::endl << std::endl;

    // Exercise 5: Sizes and addresses
    std::cout << "Exercise 5: Addresses" << std::endl;

    int stack_var = 100;
    int* heap_var = new int(100);

    std::cout << "Stack var address: " << &stack_var << std::endl;
    std::cout << "Heap var address: " << heap_var << std::endl;
    std::cout << "Notice: Heap addresses are completely different!" << std::endl;

    delete heap_var;

    // Exercise 6: String allocation to heap
    std::cout << "Exercise 6: String Allocation to Heap" << std::endl;
    std::string* heap_string = CreateHeapString();
    std::cout << "Heap string: " << *heap_string << std::endl;

    delete heap_string;  // MUST cleanup! (old way)
    heap_string = nullptr;  // Good practice
    std::cout << "(Manually cleaned up)" << std::endl << std::endl;

    // Exercise 7: Increment by reference
    std::cout << "Exercise 7: Increment by Reference" << std::endl;
    int value = 10;
    std::cout << "Before increment: " << value << std::endl;
    IncrementByReference(value);
    std::cout << "After increment: " << value << std::endl;

    return 0;
}