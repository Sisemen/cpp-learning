#include "Day2_MiniEngine.h"
#include <iostream>

using namespace Day1_DesignPatterns;

namespace Day2_MiniEngine
{
  void Engine::Initialize()
  {
    events.Subscribe([](const std::string& name, int dmg) {
      std::cout << "  [Engine Log] " << name << " took " << dmg << " damage" << std::endl;
      });

    std::cout << "Engine initialized." << std::endl;
  }

  void Engine::SpawnEntity(std::unique_ptr<Entity> entity)
  {
    std::cout << "Spawning: " << entity->GetName() << std::endl;
    entities.push_back(std::move(entity));
  }

  Entity* Engine::FindEntity(const std::string& name)
  {
    for (auto& e : entities)
    {
      if (e->GetName() == name)
        return e.get();
    }
    return nullptr;
  }

  void Engine::DealDamage(const std::string& name, int amount)
  {
    Entity* entity = FindEntity(name);
    if (entity)
    {
      HealthComponent* health = entity->GetComponent<HealthComponent>();
      if (health)
      {
        health->TakeDamage(amount);
        events.NotifyDamage(name, amount);
      }
    }
  }

  void Engine::Update(float deltaTime)
  {
    for (auto& entity : entities)
    {
      entity->Update(deltaTime);
    }
  }

  void Engine::Run(int numFrames)
  {
    std::cout << "\n--- Running " << numFrames << " frames ---" << std::endl;
    for (int frame = 0; frame < numFrames; frame++)
    {
      std::cout << "\nFrame " << frame + 1 << ":" << std::endl;
      Update(0.016f);
    }
  }

  size_t Engine::GetEntityCount() const
  {
    return entities.size();
  }

  void Execute()
  {
    std::cout << "=== MINI GAME ENGINE ===" << std::endl << std::endl;

    Engine engine;
    engine.Initialize();

    std::cout << std::endl;

    // Spawn entities using factory (ownership transferred to engine)
    engine.SpawnEntity(EntityFactory::CreatePlayer("Hero"));
    engine.SpawnEntity(EntityFactory::CreateEnemy("Goblin"));
    engine.SpawnEntity(EntityFactory::CreateEnemy("Orc"));

    std::cout << "\nTotal entities: " << engine.GetEntityCount() << std::endl;

    // Deal some damage - engine finds entity, modifies it, fires event
    std::cout << "\n--- Combat ---" << std::endl;
    engine.DealDamage("Goblin", 30);
    engine.DealDamage("Hero", 10);

    // Run the game loop for a few frames
    engine.Run(3);

    std::cout << "\n=== END ===" << std::endl;

    return;
  }
} // namespace Day2_MiniEngine
