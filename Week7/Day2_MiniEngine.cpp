#include "Day2_MiniEngine.h"
#include <iostream>
#include <fstream>

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

  void Engine::SaveGameState(const std::string& filename) const
  {
    std::ofstream file(filename);
    if (!file)
    {
      std::cout << "Error opening file for saving!" << std::endl;
      return;
    }
    file << "<Engine> Entities: " << entities.size() << std::endl;
    for (const auto& entity : entities)
    {
      file << entity->Save() << std::endl;
    }
    std::cout << "[SAVE] Game state saved to " << filename << std::endl;
  }

  namespace
  {
    std::string Trim(const std::string& s)
    {
      size_t start = s.find_first_not_of(" \t\r\n");
      if (start == std::string::npos) return std::string();
      size_t end = s.find_last_not_of(" \t\r\n");
      return s.substr(start, end - start + 1);
    }

    std::unique_ptr<Component> CreateComponentByTag(const std::string& tag)
    {
      if (tag == "HealthComponent") return std::make_unique<HealthComponent>(0);
      if (tag == "MovementComponent") return std::make_unique<MovementComponent>(0.0f);
      if (tag == "DamageComponent") return std::make_unique<DamageComponent>(0);
      if (tag == "WeaponComponent") return std::make_unique<WeaponComponent>(0, 0);
      return nullptr;
    }
  }

  void Engine::LoadGameState(const std::string& filename)
  {
    std::ifstream file(filename);
    if (!file)
    {
      std::cout << "Error opening file for loading!" << std::endl;
      return;
    }

    entities.clear();

    std::unique_ptr<Entity> currentEntity;
    int componentsRemaining = 0;
    std::string line;

    while (std::getline(file, line))
    {
      std::string trimmed = Trim(line);
      if (trimmed.empty())
        continue;

      if (trimmed.rfind("<Engine>", 0) == 0)
        continue;

      if (trimmed.rfind("<Entity>", 0) == 0)
      {
        if (currentEntity)
          entities.push_back(std::move(currentEntity));

        std::string name = Trim(trimmed.substr(std::string("<Entity>").size()));
        currentEntity = std::make_unique<Entity>(name);
        componentsRemaining = 0;
        continue;
      }

      if (trimmed.rfind("Components:", 0) == 0)
      {
        componentsRemaining = std::stoi(Trim(trimmed.substr(std::string("Components:").size())));
        continue;
      }

      if (currentEntity && componentsRemaining > 0 && trimmed.front() == '<')
      {
        size_t tagEnd = trimmed.find('>');
        if (tagEnd != std::string::npos)
        {
          std::string tag = trimmed.substr(1, tagEnd - 1);
          std::string data = Trim(trimmed.substr(tagEnd + 1));

          auto component = CreateComponentByTag(tag);
          if (component)
          {
            component->Load(data);
            currentEntity->AddComponent(std::move(component));
          }
          componentsRemaining--;
        }
      }
    }

    if (currentEntity)
      entities.push_back(std::move(currentEntity));

    std::cout << "[LOAD] Game state loaded from " << filename << " (" << entities.size() << " entities)" << std::endl;
  }

  void Execute(bool saveGame)
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

    if (saveGame)
    {
      engine.SaveGameState("game_state.txt");
      std::cout << "\n[INFO] Game state saved to game_state.txt" << std::endl;
    }

    std::cout << "\n=== END ===" << std::endl;

    return;
  }

  void LoadAndExecute()
  {
    Engine engine;
    engine.Initialize();
    engine.LoadGameState("game_state.txt");
    engine.Run(3);
   
    std::cout << "\n=== END ===" << std::endl;
  }
} // namespace Day2_MiniEngine
