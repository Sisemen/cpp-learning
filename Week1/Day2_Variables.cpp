#include <iostream>

int main()
{
    // Exercise 1: Create variables
    int age = 34;
    double height = 6.5;
    bool isHero = true;
    std::string name = "Nemesis";
    int health = 100;
    auto score = 9999; // Using auto to let the compiler deduce the type

    // Exercise 2: Print them
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Is Hero: " << isHero << std::endl;
    std::cout << "Score: " << score << std::endl;

    std::cout << "\nSize of variables:" << std::endl;
    std::cout << "Size of age: " << sizeof(age) << " bytes" << std::endl;
    std::cout << "Size of height: " << sizeof(height) << " bytes" << std::endl;
    std::cout << "Size of isHero: " << sizeof(isHero) << " bytes" << std::endl;
    std::cout << "Size of name: " << sizeof(name) << " bytes" << std::endl;
    std::cout << "Size of health: " << sizeof(health) << " bytes" << std::endl;
    std::cout << "Size of score: " << sizeof(score) << " bytes" << std::endl;

    // Exercise 3: Modify values
    age = 26;
    height = 6.0;

    std::cout << "\nAfter updates:" << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << std::endl;

    return 0;
}