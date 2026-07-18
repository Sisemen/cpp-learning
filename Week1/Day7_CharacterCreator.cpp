#include <iostream>

// Functions
void PrintWelcome();
int GetPlayerInput(std::string prompt);
void CreateCharacter(std::string name, int level);
void PrintCharacterStats(std::string name, int level, int health, int mana, int defense);

int main()
{
    PrintWelcome();

    // Get player input
    std::cout << "Enter your character name: ";
    std::string name;
    std::cin >> name;  // NEW! Read from keyboard

    std::cout << "Enter starting level (1-10): ";
    int level;
    std::cin >> level;

    while (level < 1 || level > 10) {
        std::cout << "Invalid level. Please enter a level between 1 and 10: ";
        std::cin >> level;
    }

    // Create character
    CreateCharacter(name, level);

    // Calculate stats based on level
    int health = level * 10;  // Each level = 10 health
    int damage = level * 2;   // Each level = 2 damage
    int mana = level * 5;     // Each level = 5 mana
    int defense = level + 5;  // Each level = 1 defense

    std::cout << std::endl;
    PrintCharacterStats(name, level, health, mana, defense);
    std::cout << "Damage: " << damage << std::endl;

    return 0;
}

void PrintWelcome()
{
    std::cout << "===== CHARACTER CREATOR =====" << std::endl;
    std::cout << std::endl;
}

void CreateCharacter(std::string name, int level)
{
    std::cout << "Creating character: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
}

void PrintCharacterStats(std::string name, int level, int health, int mana, int defense)
{
    std::cout << "===== CHARACTER STATS =====" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Mana: " << mana << std::endl;
    std::cout << "Defense: " << defense << std::endl;
}