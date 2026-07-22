#include <iostream>
#include <memory>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>

class GameObject
{
private:
  std::string id;
  bool active;

public:
  GameObject(const std::string& id)
    : id(id), active(true)
  {
    std::cout << "GameObject created: " << id << std::endl;
  }

  GameObject(const GameObject& obj)
    : id(obj.id), active(true)
  {
    std::cout << "GameObject created2: " << id << std::endl;
  }

  ~GameObject()
  {
    std::cout << "GameObject destroyed: " << id << std::endl;
  }
};

void DoGameObjectManager()
{
  std::cout << "================== Game Object Manager ==================" << std::endl;
  std::cout << "1. Create vector of unique_ptr<GameObject>" << std::endl;
  std::cout << "2. Add 5 objects to vector" << std::endl;
  std::cout << "3. Remove objects (they auto-destruct)" << std::endl;
  std::cout << "4. Watch cleanup order" << std::endl;
  std::cout << std::endl;

  std::vector<std::unique_ptr<GameObject>> vec;

  vec.emplace_back(std::make_unique<GameObject>("1"));
  vec.emplace_back(std::make_unique<GameObject>("2"));
  vec.emplace_back(std::make_unique<GameObject>("3"));
  vec.emplace_back(std::make_unique<GameObject>("4"));
  vec.emplace_back(std::make_unique<GameObject>("5"));

  vec.clear();

  if (vec.empty()) std::cout << "Vectore is empty now!" << std::endl;
}

class FileManager
{
private:
  FILE* fileHandler;

public:
  FileManager(const std::string& filename)
  {
    fileHandler = fopen(filename.c_str(), "w+");

    if (!fileHandler)
    {
      std::perror("File opening failed");
    }
  }

  ~FileManager()
  {
    if (fileHandler)
    {
      fclose(fileHandler);
      std::cout << "File is closed!!!" << std::endl;
    }
  }

  void Write(const std::string& content)
  {
    if (fileHandler)
    {
      std::fputs(content.c_str(), fileHandler);
    }
  }

  void Read()
  {
    if (!fileHandler) return;

    std::rewind(fileHandler);

    int c;
    while ((c = std::fgetc(fileHandler)) != EOF)
    {
      std::putchar(c);
    }
  }
};

void DoResourceManager()
{
  std::cout << "================== Resource Manager ==================" << std::endl;
  std::cout << "Create a class that manages a file-like resource" << std::endl;
  std::cout << "Constructor: \"opens\" file" << std::endl;
  std::cout << "Destructor: \"closes\" file" << std::endl;
  std::cout << "Methods: Read, Write" << std::endl;
  std::cout << "Guarantee with RAII that file is always closed" << std::endl;
  std::cout << "Even if exception thrown!" << std::endl;


  auto file = std::make_unique<FileManager>("C:\\Temp\\temp1.txt");

  file->Write("Hello from FileManager!\nThis content was written and read back.\n");

  std::cout << "\n--- File Content ---" << std::endl;
  file->Read();
  std::cout << "--------------------" << std::endl;
}

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

void DoGameEntitySystem()
{
  std::cout << "================== Game Entity System ==================" << std::endl;
  std::cout << "Create multiple entity types:" << std::endl;
  std::cout << "- Player (unique_ptr, only one)" << std::endl;
  std::cout << "- Enemy (unique_ptr in vector, many)" << std::endl;
  std::cout << "- Item (unique_ptr in inventory)" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Demonstrate:" << std::endl;
  std::cout << "- Creating entities" << std::endl;
  std::cout << "- Interacting between them" << std::endl;
  std::cout << "- Automatic cleanup" << std::endl;
  std::cout << "- No memory leaks" << std::endl;
  std::cout << std::endl;


}

int main()
{
  DoGameObjectManager();

  DoResourceManager();

  return 0;
}