#include <iostream>
#include <memory>
#include <vector>

// Abstract base class - cannot instantiate directly
class GameObject
{
protected:
  std::string name;
  int health;

public:
  GameObject(const std::string& n, int h = 100)
    : name(n), health(h)
  {
    std::cout << "[CREATE] " << name << std::endl;
  }

  virtual ~GameObject() = default;

  // Pure virtual - MUST implement in derived class
  virtual void Update() = 0;
  virtual void Draw() = 0;

  // Regular virtual - can override but has default
  virtual void TakeDamage(int amount)
  {
    health -= amount;
    std::cout << name << " takes " << amount << " damage (HP: " << health << ")" << std::endl;
  }

  virtual bool IsAlive() const
  {
    return health > 0;
  }

  const std::string& GetName() const
  {
    return name;
  }
};

// Concrete class 1
class Player : public GameObject
{
private:
  int level;
  int experience;

public:
  Player(const std::string& n)
    : GameObject(n, 150), level(1), experience(0)
  {
    std::cout << "  -> Player ready!" << std::endl;
  }

  void Update() override
  {
    std::cout << "[PLAYER] " << name << " (Lvl " << level << ") moves forward" << std::endl;
  }

  void Draw() override
  {
    std::cout << "[DRAW] Player: " << name << " | HP: " << health << std::endl;
  }

  void GainExperience(int xp)
  {
    experience += xp;
    std::cout << name << " gained " << xp << " XP! Total: " << experience << std::endl;

    if (experience >= 100)
    {
      LevelUp();
    }
  }

  void LevelUp()
  {
    level++;
    experience = 0;
    health += 50;
    std::cout << "*** " << name << " LEVELED UP to " << level << "! ***" << std::endl;
  }
};

// Concrete class 2
class Enemy : public GameObject
{
private:
  int damage;
  std::string type;

public:
  Enemy(const std::string& n, const std::string& t, int dmg)
    : GameObject(n, 75), damage(dmg), type(t)
  {
    std::cout << "  -> " << type << " spawned!" << std::endl;
  }

  void Update() override
  {
    std::cout << "[ENEMY] " << type << " " << name << " attacks!" << std::endl;
  }

  void Draw() override
  {
    std::cout << "[DRAW] Enemy: " << name << " (" << type << ") | HP: " << health << std::endl;
  }

  int GetDamage() const
  {
    return damage;
  }

  const std::string& GetType() const
  {
    return type;
  }
};

// Concrete class 3
class Projectile : public GameObject
{
private:
  int speed;
  int damage;

public:
  Projectile(const std::string& n, int spd, int dmg)
    : GameObject(n, 1), speed(spd), damage(dmg)  // Projectiles don't have health usually
  {
    std::cout << "  -> Projectile fired!" << std::endl;
  }

  void Update() override
  {
    std::cout << "[PROJECTILE] " << name << " flying at speed " << speed << std::endl;
  }

  void Draw() override
  {
    std::cout << "[DRAW] Projectile: " << name << " (Speed: " << speed << ")" << std::endl;
  }

  int GetDamage() const
  {
    return damage;
  }
};

class Particle : public GameObject
{
private:
  std::string visualEffect;
public:
  Particle(const std::string& n, const std::string& ve)
    : GameObject(n, 1), visualEffect(ve)  // Particles don't have health usually
  {
    std::cout << "  -> Particle spreaded!" << std::endl;
  }

  void Update() override
  {
    std::cout << "[PARTICLE] " << name << " throw with visual effect " << visualEffect << std::endl;
  }

  void Draw() override
  {
    std::cout << "[DRAW] Particle: " << name << " (Visual Effect: " << visualEffect << ")" << std::endl;
  }

  void Throw() {
    std::cout << "[Throw] Collision throws particles " << name << " Visual Effect: " << visualEffect << std::endl;
  }
};

bool CheckCollision(GameObject* first, GameObject* second)
{
  auto obj1 = dynamic_cast<Projectile*>(first);
  auto obj2 = dynamic_cast<Particle*>(second);

  if (obj1 && obj2)
  {
    obj2->Throw();
    return true;
  }

  return false;
}

int main()
{
  std::cout << "=== ABSTRACT CLASSES & GAME ARCHITECTURE ===" << std::endl << std::endl;

  // Exercise 1: Cannot create abstract class
  std::cout << "--- Abstract Classes ---" << std::endl;
  // GameObject obj;  // COMPILE ERROR! Abstract class
  std::cout << "Cannot create GameObject directly (abstract)" << std::endl << std::endl;

  // Exercise 2: Can create concrete classes
  std::cout << "--- Creating Concrete Objects ---" << std::endl;
  {
    auto player = std::make_unique<Player>("Hero");
    auto goblin = std::make_unique<Enemy>("Grok", "Goblin", 12);
    auto arrow = std::make_unique<Projectile>("Arrow", 50, 15);

    player->Update();
    goblin->Update();
    arrow->Update();

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 3: Game scene - polymorphic collection
  std::cout << "--- Game Scene: Mixed Objects ---" << std::endl;
  {
    std::vector<std::unique_ptr<GameObject>> scene;

    // Add various game objects
    scene.push_back(std::make_unique<Player>("Warrior"));
    scene.push_back(std::make_unique<Enemy>("Orc1", "Orc", 18));
    scene.push_back(std::make_unique<Enemy>("Orc2", "Orc", 18));
    scene.push_back(std::make_unique<Projectile>("Fireball", 40, 25));
    scene.push_back(std::make_unique<Player>("Mage"));
    scene.push_back(std::make_unique<Particle>("Potato", "Fried"));

    std::cout << "Scene has " << scene.size() << " objects\n" << std::endl;

    // Update all
    std::cout << "Updating scene:" << std::endl;
    for (auto& obj : scene)
    {
      obj->Update();
    }

    std::cout << std::endl;

    // Draw all
    std::cout << "Drawing scene:" << std::endl;
    for (auto& obj : scene)
    {
      obj->Draw();
    }

    std::cout << std::endl;

    // Damage all
    std::cout << "All objects take 20 damage:" << std::endl;
    for (auto& obj : scene)
    {
      obj->TakeDamage(20);
    }

    std::cout << std::endl;

    // Check alive
    std::cout << "Objects still alive:" << std::endl;
    for (auto& obj : scene)
    {
      if (obj->IsAlive())
      {
        std::cout << "  - " << obj->GetName() << std::endl;
      }
    }

    std::cout << std::endl;
  }

  // Exercise 4: Dynamic casting
  std::cout << "--- Finding Specific Objects ---" << std::endl;
  {
    std::vector<std::unique_ptr<GameObject>> scene;
    scene.push_back(std::make_unique<Player>("Hero"));
    scene.push_back(std::make_unique<Enemy>("Goblin", "Goblin", 10));
    scene.push_back(std::make_unique<Projectile>("Arrow", 50, 15));
    scene.push_back(std::make_unique<Particle>("Potato", "Fried"));

    std::cout << "Looking for players:" << std::endl;
    for (auto& obj : scene)
    {
      Player* player = dynamic_cast<Player*>(obj.get());
      if (player)
      {
        std::cout << "  Found player: " << player->GetName() << std::endl;
        player->GainExperience(50);
      }
    }

    std::cout << std::endl;

    std::cout << "Looking for enemies:" << std::endl;
    for (auto& obj : scene)
    {
      Enemy* enemy = dynamic_cast<Enemy*>(obj.get());
      if (enemy)
      {
        std::cout << "  Found " << enemy->GetType() << ": " << enemy->GetName()
          << " (DMG: " << enemy->GetDamage() << ")" << std::endl;
      }
    }
  }

  std::cout << "--- Check Collision ---" << std::endl;
  {
    std::vector<std::unique_ptr<GameObject>> scene;
    scene.push_back(std::make_unique<Player>("Hero"));
    scene.push_back(std::make_unique<Particle>("Water", "Splashed"));
    scene.push_back(std::make_unique<Enemy>("Goblin", "Goblin", 10));
    scene.push_back(std::make_unique<Projectile>("Arrow", 50, 15));
    scene.push_back(std::make_unique<Enemy>("Troll", "Troll", 10));
    scene.push_back(std::make_unique<Particle>("Potato", "Fried"));
    scene.push_back(std::make_unique<Enemy>("Orc", "Orc", 10));

    for (auto& first : scene) {
      for (auto& second : scene) {
        if (CheckCollision(first.get(), second.get()))
          std::cout << "Collision Happened!!!" << std::endl;
      }
    }
  }

  std::cout << "\n=== GAME SESSION END ===" << std::endl;

  return 0;
}