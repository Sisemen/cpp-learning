#include "Day1_DesignPatterns.h"
#include <iostream>

class WeaponComponent : public Day1_DesignPatterns::Component
{
public:
  int damage;
  int range;

  WeaponComponent(int dg, int rng) : damage(dg), range(rng) {
  }

  void Update(float dt) {

  }

  void AttackEntity(Day1_DesignPatterns::Entity& target) {
    auto health = target.GetComponent<Day1_DesignPatterns::HealthComponent>();
    if (health) {
      health->TakeDamage(damage);
      std::cout << "  [Weapon] Attacked " << target.GetName() << " for " << damage << " damage." << std::endl;
    }
  }
};
