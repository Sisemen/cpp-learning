#include <iostream>
#include <memory>

struct Player
{
  std::string name;
  int health;

  Player(const std::string& n, int h)
    : name(n), health(h)
  {
    std::cout << "Player created: " << name << std::endl;
  }

  ~Player()
  {
    std::cout << "Player destroyed: " << name << std::endl;
  }

  void TakeDamage(int damage)
  {
    health -= damage;
    std::cout << name << " took " << damage << " damage. Health: " << health << std::endl;
  }
};

struct Enemy
{
  int health;
  Enemy(int h) : health(h)
  {
    std::cout << "Enemy created with health: " << health << std::endl;
  }
  ~Enemy()
  {
    std::cout << "Enemy destroyed" << std::endl;
  }
};

void DoSmartPointer()
{
  std::cout << "================== Smart Pointer Exercises ==================" << std::endl;
  std::cout << "Add a new struct Enemy with health" << std::endl;
  std::cout << "Create multiple unique_ptrs to Enemy" << std::endl;
  std::cout << "Use std::move to transfer ownership" << std::endl;
  std::cout << "Try shared_ptr with multiple references" << std::endl;
  std::cout << std::endl;

  auto enemy1 = std::make_unique<Enemy>(50);
  auto enemy2 = std::make_unique<Enemy>(75);

  auto enemy3 = std::move(enemy1); // Transfer ownership from enemy1 to enemy3

  if (enemy1 == nullptr)
  {
    std::cout << "enemy1 is now nullptr (ownership transferred)" << std::endl;
  }

  auto sharedEnemy = std::make_shared<Enemy>(100);
  {
    auto sharedEnemyCopy = sharedEnemy; // Shared ownership

    std::cout << "Shared enemy health: " << sharedEnemyCopy->health << std::endl;
  }

  std::cout << "Shared enemy still alive after inner scope: " << sharedEnemy->health << std::endl;
  std::cout << std::endl;
}

int main()
{
  std::cout << "=== UNIQUE_PTR EXAMPLES ===" << std::endl << std::endl;

  // Exercise 1: Basic unique_ptr
  {
    std::cout << "Creating unique_ptr:" << std::endl;
    auto player = std::make_unique<Player>("Hero", 100);
    player->TakeDamage(10);
    std::cout << "Scope ending..." << std::endl;
  }  // Player automatically destroyed here!
  std::cout << std::endl;

  // Exercise 2: Multiple unique_ptrs
  std::cout << "=== MULTIPLE UNIQUE_PTRS ===" << std::endl;
  {
    auto hero = std::make_unique<Player>("Hero", 100);
    auto enemy = std::make_unique<Player>("Enemy", 50);

    hero->TakeDamage(20);
    enemy->TakeDamage(15);

    std::cout << "Both destroyed at scope end:" << std::endl;
  }
  std::cout << std::endl;

  // Exercise 3: Array unique_ptr
  std::cout << "=== UNIQUE_PTR ARRAY ===" << std::endl;
  {
    auto values = std::make_unique<int[]>(5);
    values[0] = 10;
    values[1] = 20;
    values[2] = 30;

    std::cout << "Array values: ";
    for (int i = 0; i < 3; i++)
    {
      std::cout << values[i] << " ";
    }
    std::cout << "\n(Auto-cleaned)" << std::endl;
  }
  std::cout << std::endl;

  // Exercise 4: Move semantics
  std::cout << "=== MOVE SEMANTICS ===" << std::endl;
  {
    auto player1 = std::make_unique<Player>("Player1", 100);

    std::cout << "Moving player1 to player2..." << std::endl;
    auto player2 = std::move(player1);

    // player1 is now nullptr
    // player2 owns the Player

    if (player1 == nullptr)
    {
      std::cout << "player1 is now nullptr (ownership transferred)" << std::endl;
    }

    player2->TakeDamage(5);
    std::cout << "Only player2 destroyed:" << std::endl;
  }
  std::cout << std::endl;

  // Exercise 5: Shared_ptr
  std::cout << "=== SHARED_PTR ===" << std::endl;
  {
    auto player = std::make_shared<Player>("Shared", 100);

    {
      auto copy = player;  // Shared ownership
      copy->TakeDamage(10);
      std::cout << "Inner scope ending..." << std::endl;
    }  // copy destroyed but Player still alive (player owns it)

    std::cout << "Outer scope ending..." << std::endl;
  }  // Both destroyed, Player finally cleaned up
  std::cout << std::endl;

  DoSmartPointer();

  std::cout << "=== PROGRAM END ===" << std::endl;

  DoSmartPointer();

  return 0;
}