#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <string>

// ============ COMPONENT PATTERN ============

class Component
{
public:
  virtual ~Component() = default;
  virtual void Update(float dt) = 0;
};

class HealthComponent : public Component
{
public:
  int health;
  int maxHealth;

  HealthComponent(int hp) : health(hp), maxHealth(hp) {}

  void Update(float dt) override
  {
    // Regenerate slowly
  }

  void TakeDamage(int amount)
  {
    health -= amount;
    if (health < 0) health = 0;
    std::cout << "  [Health] Took " << amount << " damage, now " << health << "/" << maxHealth << std::endl;
  }
};

class MovementComponent : public Component
{
public:
  float speed;
  float x = 0, y = 0;

  MovementComponent(float spd) : speed(spd) {}

  void Update(float dt) override
  {
    x += speed * dt;
    std::cout << "  [Movement] Moved to x=" << x << std::endl;
  }
};

class DamageComponent : public Component
{
public:
  int attackPower;

  DamageComponent(int ap) : attackPower(ap) {}

  void Update(float dt) override
  {
    // Could implement attack logic here
  }

  int DoDamage() const { return attackPower; }
};

class Entity
{
private:
  std::string name;
  std::vector<std::unique_ptr<Component>> components;

public:
  Entity(const std::string& n) : name(n)
  {
    std::cout << "[CREATE] Entity: " << name << std::endl;
  }

  void AddComponent(std::unique_ptr<Component> c)
  {
    components.push_back(std::move(c));
  }

  template<typename T>
  T* GetComponent()
  {
    for (auto& c : components)
    {
      T* result = dynamic_cast<T*>(c.get());
      if (result) return result;
    }
    return nullptr;
  }

  void Update(float dt)
  {
    std::cout << "Updating " << name << ":" << std::endl;
    for (auto& c : components)
    {
      c->Update(dt);
    }
  }

  const std::string& GetName() const { return name; }
};

// ============ OBSERVER PATTERN ============

class EventSystem
{
public:
  using DamageCallback = std::function<void(const std::string&, int)>;
  std::vector<DamageCallback> listeners;

  void Subscribe(DamageCallback cb)
  {
    listeners.push_back(cb);
  }

  void NotifyDamage(const std::string& entityName, int amount)
  {
    for (auto& cb : listeners)
      cb(entityName, amount);
  }
};

// ============ FACTORY PATTERN ============

class EntityFactory
{
public:
  static std::unique_ptr<Entity> CreatePlayer(const std::string& name)
  {
    auto e = std::make_unique<Entity>(name);
    e->AddComponent(std::make_unique<HealthComponent>(150));
    e->AddComponent(std::make_unique<MovementComponent>(5.0f));
    e->AddComponent(std::make_unique<DamageComponent>(25));
    return e;
  }

  static std::unique_ptr<Entity> CreateEnemy(const std::string& type)
  {
    if (type == "Goblin")
    {
      auto e = std::make_unique<Entity>("Goblin");
      e->AddComponent(std::make_unique<HealthComponent>(50));
      e->AddComponent(std::make_unique<MovementComponent>(3.0f));
      return e;
    }
    if (type == "Orc")
    {
      auto e = std::make_unique<Entity>("Orc");
      e->AddComponent(std::make_unique<HealthComponent>(100));
      e->AddComponent(std::make_unique<MovementComponent>(2.0f));
      return e;
    }
    return nullptr;
  }

  static std::unique_ptr<Entity> CreateBoss(const std::string& name)
  {
    auto e = std::make_unique<Entity>(name);
    e->AddComponent(std::make_unique<HealthComponent>(1000));
    e->AddComponent(std::make_unique<MovementComponent>(7.0f));
    e->AddComponent(std::make_unique<DamageComponent>(100));
    return e;
  }
};

// ============ DATA PASSING EXAMPLES ============

// const& because we only read the entity
void PrintEntityInfo(const Entity& entity)
{
  std::cout << "Entity: " << entity.GetName() << std::endl;
}

// & because we modify it
void DamageEntity(Entity& entity, int amount)
{
  HealthComponent* health = entity.GetComponent<HealthComponent>();
  if (health)
  {
    health->TakeDamage(amount);
  }
}

// unique_ptr because this function takes ownership
void AddToScene(std::vector<std::unique_ptr<Entity>>& scene, std::unique_ptr<Entity> entity)
{
  scene.push_back(std::move(entity));
}

Entity* FindEntityByName(const std::vector<std::unique_ptr<Entity>>& scene, const std::string& name)
{
  for (const auto& entity : scene)
  {
    if (entity->GetName() == name)
    {
      std::cout << "Found entity: " << name << std::endl;
      return entity.get();
    }
  }
  std::cout << "Entity not found: " << name << std::endl;
  return nullptr;
}

int main()
{
  std::cout << "=== DESIGN PATTERNS ===" << std::endl << std::endl;

  // Exercise 1: Component Pattern
  std::cout << "--- Component Pattern ---" << std::endl;
  {
    auto player = EntityFactory::CreatePlayer("Hero");
    player->Update(1.0f);

    DamageEntity(*player, 20);  // Pass by reference to modify

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 2: Observer Pattern
  std::cout << "--- Observer Pattern (Events) ---" << std::endl;
  {
    EventSystem events;

    events.Subscribe([](const std::string& name, int dmg) {
      std::cout << "  [UI] Update health bar for " << name << " (-" << dmg << ")" << std::endl;
      });

    events.Subscribe([](const std::string& name, int dmg) {
      std::cout << "  [Sound] Playing hurt sound for " << name << std::endl;
      });

    events.Subscribe([](const std::string& name, int dmg) {
      std::cout << "  [Achievement] First Blood " << name << ": " << dmg << std::endl;
      });

    std::cout << "Player takes damage - notifying all systems:" << std::endl;
    events.NotifyDamage("Hero", 15);

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 3: Factory Pattern + Scene management
  std::cout << "--- Factory Pattern + Scene ---" << std::endl;
  {
    std::vector<std::unique_ptr<Entity>> scene;

    // Factory creates, AddToScene takes ownership
    AddToScene(scene, EntityFactory::CreatePlayer("Warrior"));
    AddToScene(scene, EntityFactory::CreateEnemy("Goblin"));
    AddToScene(scene, EntityFactory::CreateEnemy("Orc"));

    std::cout << "Scene has " << scene.size() << " entities\n" << std::endl;

    std::cout << "Reading entity info (const&, no ownership needed):" << std::endl;
    for (const auto& entity : scene)
    {
      PrintEntityInfo(*entity);
    }

    std::cout << std::endl;

    std::cout << "Updating all entities:" << std::endl;
    for (auto& entity : scene)
    {
      entity->Update(1.0f);
    }
  }

  std::cout << "\n=== END ===" << std::endl;

  return 0;
}