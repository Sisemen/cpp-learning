#include <iostream>

int main()
{
    // Loop 1: Simple counting
    std::cout << "=== Counting 1 to 5 ===" << std::endl;
    for (int i = 1; i <= 5; i++)
    {
        std::cout << i << std::endl;
    }

    std::cout << std::endl;

    // Loop 2: Multiplication table
    std::cout << "=== 5 Multiplication Table ===" << std::endl;
    int num = 5;
    for (int i = 1; i <= 10; i++)
    {
        int result = num * i;
        std::cout << num << " x " << i << " = " << result << std::endl;
    }

    std::cout << std::endl;

    // Loop 3: Sum numbers
    std::cout << "=== Sum 1 to 50 ===" << std::endl;
    int sum = 0;
    for (int i = 1; i <= 50; i++)
    {
        sum += i;
    }
    std::cout << "Sum: " << sum << std::endl;

    std::cout << std::endl;

    std::cout << "=========== Multiplication Table ===========" << std::endl;
    for (int i = 0; i <= 10; i++)
    {
        for (int j = 0; j <= 10; j++)
        {
            int result = i * j;

            result = result == 0 ? (i + j) : result;

            if (result == 0)
            {
                std::cout << "    ";
                continue;
            }

            if (result < 10) std::cout << "   ";
            else if (result < 100) std::cout << "  ";
            else std::cout << " ";

            std::cout << result;
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (int i = 10; i >= 1; i--)
    {
        std::cout << "Countdown: " << i << std::endl;
    }

    std::cout << std::endl;

    for (int i = 1; i <= 20; i++)
    {
        if (i % 2 == 0)
        {
            std::cout << "Even: " << i << std::endl;
        }
    }

    return 0;
}