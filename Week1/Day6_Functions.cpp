#include <iostream>

// Function declarations (write them before main!)
int Add(int a, int b);
int Multiply(int a, int b);
bool IsEven(int num);
void PrintGreeting(std::string name);
int Square(int num);
bool IsPositive(int num);
void PrintStats(std::string name, int health);

int main()
{
    // Using functions
    int sum = Add(10, 5);
    std::cout << "10 + 5 = " << sum << std::endl;

    int product = Multiply(4, 7);
    std::cout << "4 * 7 = " << product << std::endl;

    if (IsEven(10))
    {
        std::cout << "10 is even" << std::endl;
    }
    else
    {
        std::cout << "10 is odd" << std::endl;
    }

    PrintGreeting("Adventurer");

    int squared = Square(6);
    std::cout << "6 squared = " << squared << std::endl;

    if (IsPositive(6))
    {
        std::cout << "Number is positive" << std::endl;
    }
    else
    {
        std::cout << "Number is not positive" << std::endl;
    }

    PrintStats("Adventurer", 100);

    return 0;
}

// Function implementations (write after main!)
int Add(int a, int b)
{
    return a + b;
}

int Multiply(int a, int b)
{
    return a * b;
}

bool IsEven(int num)
{
    return num % 2 == 0;
}

void PrintGreeting(std::string name)
{
    std::cout << "Hello, " << name << "!" << std::endl;
}

int Square(int num)
{
    return num * num;
}

bool IsPositive(int num)
{
    return num > 0;
}

void PrintStats(std::string name, int health)
{
    std::cout << "Name: " << name << ", Health: " << health << std::endl;
}