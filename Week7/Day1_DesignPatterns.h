#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <string>

namespace Day1_DesignPatterns
{
  // ============ COMPONENT PATTERN ============

  class Component
  {
  public:
    virtual ~Component() = default;
    virtual void Update(float dt) = 0;
    virtual std::string Save() const = 0;
    virtual void Load(const std::string& data) = 0;
  };

  class HealthComponent : public Component
  {
  public:
    int health;
    int maxHealth;

    HealthComponent(int hp);

    void Update(float dt) override;

    void TakeDamage(int amount);

    std::string Save() const override;
    void Load(const std::string& data) override;
  };

  class MovementComponent : public Component
  {
  public:
    float speed;
    float x = 0, y = 0;

    MovementComponent(float spd);

    void Update(float dt) override;

    std::string Save() const override;
    void Load(const std::string& data) override;
  };

  class DamageComponent : public Component
  {
  public:
    int attackPower;

    DamageComponent(int ap);

    void Update(float dt) override;

    int DoDamage() const;
    
    std::string Save() const override;
    void Load(const std::string& data) override;
  };

  class WeaponComponent : public Component
  {
  public:
    int damage;
    int range;

    WeaponComponent(int dg, int rng);

    void Update(float dt) override;

    std::string Save() const override;
    void Load(const std::string& data) override;
  };

  class Entity
  {
  private:
    std::string name;
    std::vector<std::unique_ptr<Component>> components;

  public:
    Entity(const std::string& n);

    void AddComponent(std::unique_ptr<Component> c);

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

    void Update(float dt);

    const std::string& GetName() const;

    virtual std::string Save() const;
    virtual void Load(const std::string& data);
  };

  // ============ OBSERVER PATTERN ============

  class EventSystem
  {
  public:
    using DamageCallback = std::function<void(const std::string&, int)>;
    std::vector<DamageCallback> listeners;

    void Subscribe(DamageCallback cb);

    void NotifyDamage(const std::string& entityName, int amount);
  };

  // ============ FACTORY PATTERN ============

  class EntityFactory
  {
  public:
    static std::unique_ptr<Entity> CreatePlayer(const std::string& name);

    static std::unique_ptr<Entity> CreateEnemy(const std::string& type);

    static std::unique_ptr<Entity> CreateBoss(const std::string& name);
  };

  // ============ DATA PASSING EXAMPLES ============

  // const& because we only read the entity
  void PrintEntityInfo(const Entity& entity);

  // & because we modify it
  void DamageEntity(Entity& entity, int amount);

  // unique_ptr because this function takes ownership
  void AddToScene(std::vector<std::unique_ptr<Entity>>& scene, std::unique_ptr<Entity> entity);

  Entity* FindEntityByName(const std::vector<std::unique_ptr<Entity>>& scene, const std::string& name);

  void Execute();
} // namespace Day1_DesignPatterns
