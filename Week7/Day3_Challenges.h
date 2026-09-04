#pragma once
#include <functional>
#include <string>
#include <vector>
#include <unordered_set>

namespace Day3_Challenges {
  class AchievementSystem
  {
  public:
    // entityName, damageAmount, currentHealth, maxHealth
    using DamageCallback = std::function<void(const std::string&, int, int, int)>;
    std::vector<DamageCallback> listeners;

    void SubscribeTo(DamageCallback cb);

    void NotifyDamage(const std::string& entityName, int amount, int currentHealth, int maxHealth);

    // Checks damage events for unlockable achievements.
    void OnDamage(const std::string& entityName, int amount, int currentHealth, int maxHealth);

  private:
    bool firstBloodUnlocked = false;
    std::unordered_set<std::string> survivorsUnlocked;
  };

  void Execute();
} // namespace Day3_Challenges
