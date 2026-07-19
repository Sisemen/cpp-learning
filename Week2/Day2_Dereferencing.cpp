#include <iostream>

int main()
{
    // Exercise 1: Basic dereferencing
    int x = 100;
    int* ptr = &x;

    std::cout << "=== DEREFERENCING ===" << std::endl;
    std::cout << "x: " << x << std::endl;
    std::cout << "ptr: " << ptr << " (address)" << std::endl;
    std::cout << "*ptr: " << *ptr << " (value at address)" << std::endl;

    std::cout << std::endl;

    // Exercise 2: Modify through pointer
    std::cout << "=== MODIFY THROUGH POINTER ===" << std::endl;
    std::cout << "Before: x = " << x << std::endl;

    *ptr = 200;  // Change x through ptr

    std::cout << "After: x = " << x << std::endl;
    std::cout << "After: *ptr = " << *ptr << std::endl;

    std::cout << std::endl;

    // Exercise 3: Swap using pointers
    std::cout << "=== SWAP USING POINTERS ===" << std::endl;
    int a = 5;
    int b = 10;

    int* a_ptr = &a;
    int* b_ptr = &b;

    std::cout << "Before: a = " << a << ", b = " << b << std::endl;

    // Swap
    int temp = *a_ptr;
    *a_ptr = *b_ptr;
    *b_ptr = temp;

    std::cout << "After: a = " << a << ", b = " << b << std::endl;

    std::cout << std::endl;

    // Exercise 4: String through pointer
    std::cout << "=== STRING THROUGH POINTER ===" << std::endl;
    std::string name = "Hero";
    std::string* name_ptr = &name;

    std::cout << "name: " << name << std::endl;
    std::cout << "*name_ptr: " << *name_ptr << std::endl;

    *name_ptr = "Dragon Slayer";  // Modify through pointer
    std::cout << "After change: " << name << std::endl;

    // Exercise 5: Swap double values using pointers
    std::cout << "=== SWAP USING POINTERS ===" << std::endl;
    double ad = 5.5;
    double bd = 10.5;

    double* ad_ptr = &ad;
    double* bd_ptr = &bd;

    std::cout << "Before: a = " << ad << ", b = " << bd << std::endl;

    // Swap
    double temp_d = *ad_ptr;
    *ad_ptr = *bd_ptr;
    *bd_ptr = temp_d;

    std::cout << "After: a = " << ad << ", b = " << bd << std::endl;

    std::cout << std::endl;

    // Exercise 6: Swap health and mana values using pointers
    std::cout << "=== SWAP USING POINTERS ===" << std::endl;
    double health = 5.5;
    double mana = 10.5;

    double* health_ptr = &health;
    double* mana_ptr = &mana;

    std::cout << "Before: health = " << health << ", mana = " << mana << std::endl;

    // Swap
    double temp_health = *health_ptr;
    *health_ptr = *mana_ptr;
    *mana_ptr = temp_health;

    std::cout << "After: health = " << health << ", mana = " << mana << std::endl;

    std::cout << std::endl;

    // Exercise 7: Swap titles through pointer
    std::cout << "=== STRING THROUGH POINTER ===" << std::endl;
    std::string title1 = "Warchief";
    std::string title2 = "Knight";
    std::string* title1_ptr = &title1;
    std::string* title2_ptr = &title2;

    std::cout << "Before: title1 = " << title1 << ", title2 = " << title2 << std::endl;

    // Swap
    std::string temp_title = *title1_ptr;
    *title1_ptr = *title2_ptr;
    *title2_ptr = temp_title;

    std::cout << "After: title1 = " << title1 << ", title2 = " << title2 << std::endl;

    return 0;
}