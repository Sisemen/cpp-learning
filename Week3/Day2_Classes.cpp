#include <iostream>
#include <memory>
#include <cmath>

// Simple class with RAII
class Enemy
{
private:
  std::string name;
  int health;
  int level;

public:
  Enemy(const std::string& n, int lvl)
    : name(n), health(lvl * 10), level(lvl)
  {
    std::cout << "[SPAWN] " << name << " (Lvl " << level << ", HP " << health << ")" << std::endl;
  }

  ~Enemy()
  {
    std::cout << "[DEFEATED] " << name << std::endl;
  }

  void TakeDamage(int damage)
  {
    health -= damage;
    std::cout << name << " takes " << damage << " damage. HP: " << health << std::endl;

    if (health <= 0)
    {
      std::cout << name << " is defeated!" << std::endl;
    }
  }

  int GetHealth() const
  {
    return health;
  }

  bool IsAlive() const
  {
    return health > 0;
  }

  const std::string& GetName() const
  {
    return name;
  }
};

// Inventory system with RAII
class Item
{
private:
  std::string name;
  int quantity;

public:
  Item(const std::string& n, int q)
    : name(n), quantity(q)
  {
    std::cout << "[CREATE ITEM] " << name << " x" << quantity << std::endl;
  }

  ~Item()
  {
    std::cout << "[DESTROY ITEM] " << name << std::endl;
  }

  void Use(int amount)
  {
    quantity -= amount;
    std::cout << "Used " << amount << " " << name << ". Remaining: " << quantity << std::endl;
  }

  int GetQuantity() const
  {
    return quantity;
  }
};

class Player
{
private:
  std::string name;
  int health;
  double experience;
  int level;
  const double experienceRatio = 1.2; // Experience needed to level up

public:
  Player(const std::string& n, int h)
    : name(n), health(h), experience(0), level(1)
  {
    std::cout << "[PLAYER CREATED] " << name << " (HP " << health << ")" << std::endl;
  }

  ~Player()
  {
    std::cout << "[PLAYER DESTROYED] " << name << std::endl;
  }

  void TakeDamage(int damage)
  {
    health -= damage;
    std::cout << name << " takes " << damage << " damage. HP: " << health << std::endl;
    if (health <= 0)
    {
      std::cout << name << " has been defeated!" << std::endl;
    }
  }

  void GainExperience(int exp)
  {
    experience += exp;
    std::cout << name << " gains " << exp << " experience. Total EXP: " << experience << std::endl;
    if (experience >= std::pow(experienceRatio, level - 1) * level * 100)
    {
      LevelUp();
    }
  }

  int GetHealth() const
  {
    return health;
  }

  int GetLevel() const
  {
    return level;
  }

  double GetExperience() const
  {
    return experience;
  }

  const std::string& GetName() const
  {
    return name;
  }

private:
  void LevelUp()
  {
    level++;
    health = level * 10;
    std::cout << name << " leveled up! Now at level " << level << " with " << health << " HP." << std::endl;
  }
};

int main()
{
  std::cout << "=== GAME SESSION START ===" << std::endl << std::endl;

  // Exercise 1: Single enemy
  std::cout << "--- Battle 1 ---" << std::endl;
  {
    auto goblin = std::make_unique<Enemy>("Goblin", 1);
    goblin->TakeDamage(15);
    std::cout << std::endl;
  }  // Destructor called here

  std::cout << std::endl;

  // Exercise 2: Multiple enemies
  std::cout << "--- Battle 2: Group Fight ---" << std::endl;
  {
    auto orc = std::make_unique<Enemy>("Orc", 2);
    auto goblin = std::make_unique<Enemy>("Goblin", 1);

    orc->TakeDamage(30);
    goblin->TakeDamage(20);

    std::cout << std::endl;
  }  // Both destructors called in reverse order

  std::cout << std::endl;

  // Exercise 3: Inventory with RAII
  std::cout << "--- Inventory Management ---" << std::endl;
  {
    auto potion = std::make_unique<Item>("Health Potion", 5);
    auto sword = std::make_unique<Item>("Iron Sword", 1);

    potion->Use(2);

    std::cout << std::endl;
  }  // Items destroyed

  std::cout << std::endl;

  // Exercise 4: Combat simulation
  std::cout << "--- Combat Simulation ---" << std::endl;
  {
    auto player_weapon = std::make_unique<Item>("Sword", 1);
    auto boss = std::make_unique<Enemy>("Dragon", 5);

    std::cout << "Combat starts!" << std::endl;
    boss->TakeDamage(20);
    boss->TakeDamage(25);
    boss->TakeDamage(30);

    if (boss->IsAlive())
    {
      std::cout << "Boss is still alive with " << boss->GetHealth() << " HP" << std::endl;
    }

    std::cout << std::endl;
  }  // All cleanup automatic!

  std::cout << "--- Player vs Enemy ---" << std::endl;
  {
    auto player = std::make_unique<Player>("Hero", 100);
    auto enemy = std::make_unique<Enemy>("Troll", 3);
    player->TakeDamage(20);
    player->GainExperience(50);
    player->GainExperience(60); // Should trigger level up
    enemy->TakeDamage(25);
    enemy->TakeDamage(10);
    player->GainExperience(150);
    player->GainExperience(180);
    std::cout << std::endl;
  }

  std::cout << "=== GAME SESSION END ===" << std::endl;

  return 0;
}