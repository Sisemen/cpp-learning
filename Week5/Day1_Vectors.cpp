#include <iostream>
#include <vector>
#include <memory>

class GameObject
{
protected:
  std::string name;
  int health;

public:
  GameObject(const std::string& n, int h)
    : name(n), health(h)
  {
    std::cout << "[SPAWN] " << name << std::endl;
  }

  virtual ~GameObject() = default;

  void TakeDamage(int damage)
  {
    health -= damage;
    std::cout << name << " takes " << damage << " damage (HP: " << health << ")" << std::endl;
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

class Enemy : public GameObject
{
public:
  Enemy(const std::string& n, int h)
    : GameObject(n, h)
  {
  }

  ~Enemy()
  {
    std::cout << "[Enemy] [DEFEAT] " << name << std::endl;
  }
};

class Player : public GameObject
{
public:
  Player(const std::string& n, int h)
    : GameObject(n, h)
  {
  }

  ~Player()
  {
    std::cout << "[Player] [DEFEAT] " << name << std::endl;
  }
};

int main()
{
  std::cout << "=== VECTOR BASICS ===" << std::endl << std::endl;

  // Exercise 1: Basic vector operations
  std::cout << "--- Basic Operations ---" << std::endl;
  {
    std::vector<int> numbers;

    std::cout << "Adding numbers..." << std::endl;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);

    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "Capacity: " << numbers.capacity() << std::endl;

    std::cout << "First: " << numbers.front() << std::endl;
    std::cout << "Last: " << numbers.back() << std::endl;

    std::cout << "Access [2]: " << numbers[2] << std::endl;

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 2: Iterating vectors
  std::cout << "--- Iterating ---" << std::endl;
  {
    std::vector<std::string> items = { "Sword", "Shield", "Potion" };

    std::cout << "Items:" << std::endl;
    for (const auto& item : items)
    {
      std::cout << "  - " << item << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 3: Vector of objects
  std::cout << "--- Vector of Objects ---" << std::endl;
  {
    std::vector<std::unique_ptr<Enemy>> enemies;

    std::cout << "Spawning enemies:" << std::endl;
    enemies.push_back(std::make_unique<Enemy>("Goblin1", 50));
    enemies.push_back(std::make_unique<Enemy>("Goblin2", 50));
    enemies.push_back(std::make_unique<Enemy>("Orc", 75));

    std::cout << "\nEnemies in scene: " << enemies.size() << std::endl << std::endl;

    std::cout << "Dealing damage to all:" << std::endl;
    for (auto& enemy : enemies)
    {
      enemy->TakeDamage(30);
    }

    std::cout << "\nRemoving dead enemies:" << std::endl;
    auto it = enemies.begin();
    while (it != enemies.end())
    {
      if (!(*it)->IsAlive())
      {
        std::cout << "Removing " << (*it)->GetName() << std::endl;
        it = enemies.erase(it);
      }
      else
      {
        ++it;
      }
    }

    std::cout << "\nRemaining enemies: " << enemies.size() << std::endl << std::endl;
  }

  std::cout << std::endl;

  // Exercise 4: Vector performance - reserve
  std::cout << "--- Performance: reserve() ---" << std::endl;
  {
    std::vector<int> v1;
    std::cout << "Without reserve: " << std::endl;
    std::cout << "  Before: capacity=" << v1.capacity() << std::endl;

    for (int i = 0; i < 10; i++)
    {
      v1.push_back(i);
      if (i == 0 || i == 3 || i == 7 || i == 9)
        std::cout << "  After push " << i << ": capacity=" << v1.capacity() << std::endl;
    }

    std::cout << std::endl;

    std::vector<int> v2;
    std::cout << "With reserve(10): " << std::endl;
    v2.reserve(10);
    std::cout << "  Before: capacity=" << v2.capacity() << std::endl;

    for (int i = 0; i < 10; i++)
    {
      v2.push_back(i);
    }

    std::cout << "  After all pushes: capacity=" << v2.capacity() << std::endl;
    std::cout << "  (No reallocation needed!)" << std::endl;

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 5: Vector vs Array
  std::cout << "--- Vector vs Array ---" << std::endl;
  {
    // Fixed array
    int arr[5] = { 1, 2, 3, 4, 5 };
    std::cout << "Array: fixed size 5" << std::endl;

    // Vector
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::cout << "Vector: size " << vec.size() << ", capacity " << vec.capacity() << std::endl;

    vec.push_back(6);  // Easy!
    std::cout << "After push_back: size " << vec.size() << std::endl;

    // arr.push_back(6);  // Can't do this! Array is fixed

    std::cout << std::endl;
  }

  // Tasks:
  std::cout << "--- Player ---" << std::endl;
  {
    std::vector<std::unique_ptr<Player>> players;
    players.reserve(3);

    std::cout << "Spawning enemies:" << std::endl;
    players.push_back(std::make_unique<Player>("Nemesis", 50));
    players.push_back(std::make_unique<Player>("DeathAnger", 50));
    players.push_back(std::make_unique<Player>("Nooob", 20));
    players.push_back(std::make_unique<Player>("WolfSpirit", 75));

    std::cout << "\Players in scene: " << players.size() << std::endl << std::endl;

    std::cout << "Dealing damage to all:" << std::endl;
    for (auto& player : players)
    {
      player->TakeDamage(30);
    }

    std::cout << "\nRemoving dead players:" << std::endl;
    auto it = players.begin();
    while (it != players.end())
    {
      if (!(*it)->IsAlive())
      {
        std::cout << "Removing " << (*it)->GetName() << std::endl;
        it = players.erase(it);
      }
      else
      {
        ++it;
      }
    }

    std::cout << "\nRemaining players: " << players.size() << std::endl << std::endl;
  }

  std::cout << "=== END ===" << std::endl;

  return 0;
}