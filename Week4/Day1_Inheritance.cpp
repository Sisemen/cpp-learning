#include <iostream>
#include <memory>
#include <vector>

// Base class
class GameObject
{
protected:  // Derived classes can access
  std::string name;
  int x, y;

public:
  GameObject(const std::string& n)
    : name(n), x(0), y(0)
  {
    std::cout << "[CREATE] " << name << std::endl;
  }

  virtual ~GameObject()  // CRITICAL: virtual destructor!
  {
    std::cout << "[DESTROY] " << name << std::endl;
  }

  virtual void Update()
  {
    std::cout << name << " updating..." << std::endl;
  }

  virtual void Draw()
  {
    std::cout << "Drawing " << name << " at (" << x << "," << y << ")" << std::endl;
  }

  virtual void TakeDamage(int amount)
  {
    std::cout << name << " takes " << amount << " damage" << std::endl;
  }
};

// Derived class 1
class Player : public GameObject
{
private:
  int level;
  int health;

public:
  Player(const std::string& n)
    : GameObject(n), level(1), health(100)
  {
    std::cout << "  -> Player ready for adventure!" << std::endl;
  }

  void Update() override
  {
    std::cout << "Player " << name << " is moving (Level " << level << ")" << std::endl;
  }

  void Draw() override
  {
    std::cout << "Drawing PLAYER " << name << " at (" << x << "," << y << ")" << std::endl;
  }

  void TakeDamage(int amount) override
  {
    health -= amount;
    std::cout << "PLAYER " << name << " takes " << amount << " damage! Health: " << health << std::endl;
  }

  void LevelUp()
  {
    level++;
    health += 20;
    std::cout << name << " leveled up to " << level << "!" << std::endl;
  }
};

// Derived class 2
class Enemy : public GameObject
{
private:
  int damage;
  int health;

public:
  Enemy(const std::string& n, int dmg)
    : GameObject(n), damage(dmg), health(50)
  {
    std::cout << "  -> Enemy spawned with " << damage << " damage!" << std::endl;
  }

  void Update() override
  {
    std::cout << "Enemy " << name << " is attacking with " << damage << " damage" << std::endl;
  }

  void Draw() override
  {
    std::cout << "Drawing ENEMY " << name << " at (" << x << "," << y << ")" << std::endl;
  }

  void TakeDamage(int amount) override
  {
    health -= amount;
    std::cout << "ENEMY " << name << " takes " << amount << " damage! Health: " << health << std::endl;
  }
};

// Derived class 3
class Item : public GameObject
{
private:
  std::string type;

public:
  Item(const std::string& n, const std::string& t)
    : GameObject(n), type(t)
  {
    std::cout << "  -> " << type << " created!" << std::endl;
  }

  void Update() override
  {
    // Items don't usually update
    std::cout << "Item " << name << " (type: " << type << ") waiting..." << std::endl;
  }

  void Draw() override
  {
    std::cout << "Drawing ITEM " << name << " (" << type << ")" << std::endl;
  }
};

class Projectile : public GameObject
{
private:
  std::string type;

public:
  Projectile(const std::string& n, const std::string& t)
    : GameObject(n), type(t)
  {
    std::cout << "  -> " << type << " created!" << std::endl;
  }

  void Update() override
  {
    // Items don't usually update
    std::cout << "Projectile " << name << " (type: " << type << ") waiting..." << std::endl;
  }

  void Draw() override
  {
    std::cout << "Drawing Projectile " << name << " (" << type << ")" << std::endl;
  }

};

void UpdateAll(const std::vector<std::unique_ptr<GameObject>>& objects)
{
  // Update all objects polymorphically
  std::cout << "Updating all objects:" << std::endl;
  for (auto& obj : objects)
  {
    obj->Update();  // Polymorphism! Calls correct method
  }

  std::cout << std::endl;
}

void DrawAll(const std::vector<std::unique_ptr<GameObject>>& objects)
{
  // Draw all objects
  std::cout << "Drawing all objects:" << std::endl;
  for (auto& obj : objects)
  {
    obj->Draw();
  }

  std::cout << std::endl;
}

int main()
{
  std::cout << "=== INHERITANCE & POLYMORPHISM ===" << std::endl << std::endl;

  // Exercise 1: Create individual objects
  std::cout << "--- Creating Individual Objects ---" << std::endl;
  {
    auto player = std::make_unique<Player>("Hero");
    auto enemy = std::make_unique<Enemy>("Goblin", 15);
    auto potion = std::make_unique<Item>("Health Potion", "Consumable");

    player->Update();
    enemy->Update();
    potion->Update();

    player->Draw();
    enemy->Draw();
    potion->Draw();

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 2: Polymorphism - store all in vector
  std::cout << "--- Polymorphism: All Objects in Vector ---" << std::endl;
  {
    std::vector<std::unique_ptr<GameObject>> objects;

    // Add different types
    objects.push_back(std::make_unique<Player>("Warrior"));
    objects.push_back(std::make_unique<Enemy>("Orc", 20));
    objects.push_back(std::make_unique<Player>("Mage"));
    objects.push_back(std::make_unique<Enemy>("Troll", 25));
    objects.push_back(std::make_unique<Item>("Sword", "Weapon"));
    objects.push_back(std::make_unique<Projectile>("Fire Bolt", "Magic Damage"));

    std::cout << "Objects in scene: " << objects.size() << std::endl << std::endl;

    UpdateAll(objects);

    DrawAll(objects);

    // Take damage polymorphically
    std::cout << "All objects take 10 damage:" << std::endl;
    for (auto& obj : objects)
    {
      obj->TakeDamage(10);
    }

    std::cout << std::endl << "Objects destroyed:" << std::endl;
  }

  std::cout << std::endl;

  // Exercise 3: Casting (advanced)
  std::cout << "--- Accessing Derived Class Methods ---" << std::endl;
  {
    std::vector<std::unique_ptr<GameObject>> objects;
    objects.push_back(std::make_unique<Player>("Hero"));
    objects.push_back(std::make_unique<Enemy>("Enemy", 15));

    // Find player and level up
    for (auto& obj : objects)
    {
      // Try to cast to Player
      Player* player = dynamic_cast<Player*>(obj.get());
      if (player != nullptr)
      {
        std::cout << "Found player! Leveling up..." << std::endl;
        player->LevelUp();
      }
    }
  }

  return 0;
}