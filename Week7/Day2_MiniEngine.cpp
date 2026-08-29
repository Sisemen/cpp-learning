#pragma once

#include <iostream>
#include "Day1_DesignPatterns.cpp"
#include <vector>
#include <memory>
#include <fstream>

using namespace Day1_DesignPatterns;
namespace Day2_MiniEngine
{
  // Add this to your Day 1 code (or new file including it)

  class Engine
  {
  private:
    std::vector<std::unique_ptr<Entity>> entities;
    EventSystem events;

  public:
    void Initialize()
    {
      events.Subscribe([](const std::string& name, int dmg) {
        std::cout << "  [Engine Log] " << name << " took " << dmg << " damage" << std::endl;
        });

      std::cout << "Engine initialized." << std::endl;
    }

    // Takes ownership - engine now owns this entity
    void SpawnEntity(std::unique_ptr<Entity> entity)
    {
      std::cout << "Spawning: " << entity->GetName() << std::endl;
      entities.push_back(std::move(entity));
    }

    // Borrows - doesn't own the result, might not find it
    Entity* FindEntity(const std::string& name)
    {
      for (auto& e : entities)
      {
        if (e->GetName() == name)
          return e.get();
      }
      return nullptr;
    }

    void RemoveEntityByName(const std::string& name)
    {
      auto it = entities.begin();
      while (it != entities.end())
      {
        if ((*it)->GetName() == name)
        {
          std::cout << "Removing " << (*it)->GetName() << std::endl;
          it = entities.erase(it);
          return; // Exit after removing the first match
        }
        else
        {
          ++it;
        }
      }
    }

    void RemoveEntity(const std::string& name)
    {
      auto it = std::remove_if(entities.begin(), entities.end(),
        [&name](const std::unique_ptr<Entity>& e) { return e->GetName() == name; });
      if (it != entities.end())
      {
        std::cout << "Removing entity: " << name << std::endl;
        entities.erase(it);
      }
    }

    void DealDamage(const std::string& name, int amount)
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

    bool IsGameOver()
    {
      auto hero = FindEntity("Hero");
      if (hero)
      {
        auto health = hero->GetComponent<HealthComponent>();
        if (health && health->health <= 0)
        {
          std::cout << "Game Over! " << hero->GetName() << " has been defeated." << std::endl;
          return true;
        }
      }

      return false;
    }

    void Update(float deltaTime)
    {
      for (auto& entity : entities)
      {
        entity->Update(deltaTime);
      }
    }

    void Run(int numFrames)
    {
      std::cout << "\n--- Running " << numFrames << " frames ---" << std::endl;
      for (int frame = 0; frame < numFrames; frame++)
      {
        if (IsGameOver())
        {
          std::cout << "Stopping game loop due to game over." << std::endl;
          break;
        }

        std::cout << "\nFrame " << frame + 1 << ":" << std::endl;
        Update(0.016f);
      }
    }

    size_t GetEntityCount() const
    {
      return entities.size();
    }

    void SaveEntityList(const std::string& filename)
    {
      std::ofstream file(filename);

      if (file.is_open())
      {
        for (const auto& entity : entities)
        {
          file << "Name: " << entity->GetName()
            << " | Health: " << entity->GetComponent<HealthComponent>()->health << std::endl;
        }

        file.close();
      }
    }
  };

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
    
    // Save the list of entities to a file
    engine.SaveEntityList("entities.txt");

    std::cout << "\n=== END ===" << std::endl;

    return;
  }
} // namespace Day2_MiniEngine