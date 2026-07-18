#include <iostream>

int main()
{
    // Simple RPG health check
    int health = 75;
    int maxHealth = 100;
    int armor = 10;

    std::cout << "Health: " << health << "/" << maxHealth << std::endl;
    std::cout << "Armor: " << armor << std::endl;

    if (health > 50 && armor > 5)
    {
        std::cout << "Status: Well Protected" << std::endl;
    }

    std::cout << "Is the player alive?" << std::endl << (health > 0 ? "Alive" : "Dead") << std::endl;

    // Check status
    if (health > 75)
    {
        std::cout << "Status: Excellent" << std::endl;
    }
    else if (health > 50)
    {
        std::cout << "Status: Good" << std::endl;
    }
    else if (health > 25)
    {
        std::cout << "Status: Wounded" << std::endl;
    }
    else if (health > 0)
    {
        std::cout << "Status: Critical!" << std::endl;
    }
    else
    {
        std::cout << "Status: Dead" << std::endl;
    }

    return 0;
}