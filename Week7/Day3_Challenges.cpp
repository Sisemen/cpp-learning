#include "Day1_DesignPatterns.h"
#include "Day3_Challenges.h"
#include <iostream>

namespace Day3_Challenges {

  // ============ OBSERVER PATTERN ============

  void AchievementSystem::SubscribeTo(DamageCallback cb)
  {
    listeners.push_back(cb);
  }

  void AchievementSystem::NotifyDamage(const std::string& entityName, int amount, int currentHealth, int maxHealth)
  {
    for (auto& cb : listeners)
      cb(entityName, amount, currentHealth, maxHealth);
  }

  void AchievementSystem::OnDamage(const std::string& entityName, int amount, int currentHealth, int maxHealth)
  {
    if (!firstBloodUnlocked)
    {
      firstBloodUnlocked = true;
      std::cout << "  [Achievement] First Blood unlocked! " << entityName << " took the first hit." << std::endl;
    }

    if (currentHealth > 0 && maxHealth > 0 &&
        currentHealth < maxHealth * 0.2f &&
        survivorsUnlocked.find(entityName) == survivorsUnlocked.end())
    {
      survivorsUnlocked.insert(entityName);
      std::cout << "  [Achievement] Survivor unlocked! " << entityName << " survived dropping below 20% health." << std::endl;
    }
  }

  void AttackEntity(Day1_DesignPatterns::Entity& attacker, Day1_DesignPatterns::Entity& target, AchievementSystem& achievements) {
    auto weapon = attacker.GetComponent<Day1_DesignPatterns::WeaponComponent>();
    auto health = target.GetComponent<Day1_DesignPatterns::HealthComponent>();
    if (health && weapon) {
      std::cout << "  [Weapon] " << attacker.GetName() << " attacked " << target.GetName() << " for " << weapon->damage << " damage." << std::endl;
      health->TakeDamage(weapon->damage);
      achievements.NotifyDamage(target.GetName(), weapon->damage, health->health, health->maxHealth);
    }
  }

  void Execute() {
    using namespace Day1_DesignPatterns;

    auto player = EntityFactory::CreatePlayer("Hero");
    auto enemies = std::vector<std::unique_ptr<Entity>>();

    enemies.reserve(2);

    enemies.emplace_back(EntityFactory::CreateEnemy("Orc"));
    enemies.emplace_back(EntityFactory::CreateEnemy("Goblin"));

    player->AddComponent(std::make_unique<WeaponComponent>(45, 5));

    AchievementSystem achievements;
    achievements.SubscribeTo([&achievements](const std::string& entityName, int amount, int currentHealth, int maxHealth) {
      achievements.OnDamage(entityName, amount, currentHealth, maxHealth);
    });

    for (auto& enemy : enemies) {
      if (player && enemy) {
        AttackEntity(*player, *enemy, achievements);
      }
    }
  }
} // namespace Day3_Challenges