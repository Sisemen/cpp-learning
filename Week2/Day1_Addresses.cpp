#include <iostream>

int main()
{
    // Exercise 1: Get addresses
    int age = 25;
    double height = 5.9;
    bool isAlive = true;
    std::string name = "Hero";
    int health = 100;

    // Print VALUES
    std::cout << "=== VALUES ===" << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Is Alive: " << isAlive << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Health: " << health << std::endl;

    std::cout << std::endl;

    // Print ADDRESSES using &
    std::cout << "=== ADDRESSES ===" << std::endl;
    std::cout << "Age address: " << &age << std::endl;
    std::cout << "Height address: " << &height << std::endl;
    std::cout << "Is Alive address: " << &isAlive << std::endl;
    std::cout << "Name address: " << &name << std::endl;
    std::cout << "Health address: " << &health << std::endl;

    std::cout << std::endl;

    // Exercise 2: Store addresses in pointers
    int* age_ptr = &age;
    double* height_ptr = &height;
    bool* alive_ptr = &isAlive;
    std::string* name_ptr = &name;
    int* health_ptr = &health;

    std::cout << "=== POINTERS ===" << std::endl;
    std::cout << "age_ptr: " << age_ptr << std::endl;
    std::cout << "height_ptr: " << height_ptr << std::endl;
    std::cout << "alive_ptr: " << alive_ptr << std::endl;
    std::cout << "name_ptr: " << name_ptr << std::endl;
    std::cout << "health_ptr: " << health_ptr << std::endl;

    std::cout << std::endl;

    std::cout << "=== POINTERS SIZE ===" << std::endl;
    std::cout << "sizeof(age_ptr): " << sizeof(age_ptr) << " bytes" << std::endl;
    std::cout << "sizeof(height_ptr): " << sizeof(height_ptr) << " bytes" << std::endl;
    std::cout << "sizeof(alive_ptr): " << sizeof(alive_ptr) << " bytes" << std::endl;
    std::cout << "sizeof(name_ptr): " << sizeof(name_ptr) << " bytes" << std::endl;
    std::cout << "sizeof(health_ptr): " << sizeof(health_ptr) << " bytes" << std::endl;

    // Exercise 3: Sizes
    std::cout << "=== SIZES ===" << std::endl;
    std::cout << "sizeof(int): " << sizeof(int) << " bytes" << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << " bytes" << std::endl;
    std::cout << "sizeof(bool): " << sizeof(bool) << " bytes" << std::endl;
    std::cout << "sizeof(int*): " << sizeof(int*) << " bytes" << std::endl;
    std::cout << "sizeof(double*): " << sizeof(double*) << " bytes" << std::endl;
    std::cout << "sizeof(bool*): " << sizeof(bool*) << " bytes" << std::endl;

    return 0;
}