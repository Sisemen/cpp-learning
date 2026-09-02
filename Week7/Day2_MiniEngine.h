#pragma once

#include "Day1_DesignPatterns.h"
#include <vector>
#include <memory>
#include <string>

namespace Day2_MiniEngine
{
  class Engine
  {
  private:
    std::vector<std::unique_ptr<Day1_DesignPatterns::Entity>> entities;
    Day1_DesignPatterns::EventSystem events;

  public:
    void Initialize();

    // Takes ownership - engine now owns this entity
    void SpawnEntity(std::unique_ptr<Day1_DesignPatterns::Entity> entity);

    // Borrows - doesn't own the result, might not find it
    Day1_DesignPatterns::Entity* FindEntity(const std::string& name);

    void DealDamage(const std::string& name, int amount);

    void Update(float deltaTime);

    void Run(int numFrames);

    size_t GetEntityCount() const;
  };

  void Execute();
} // namespace Day2_MiniEngine
