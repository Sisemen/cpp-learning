#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>

int main()
{
  std::cout << "=== STL CONTAINERS ===" << std::endl << std::endl;

  // Exercise 1: Map (key-value)
  std::cout << "--- std::map (Inventory) ---" << std::endl;
  {
    std::unordered_map<std::string, int> inventory;

    inventory["Health Potion"] = 5;
    inventory["Mana Potion"] = 3;
    inventory["Iron Sword"] = 1;
    inventory["Gold"] = 250;

    std::cout << "Inventory:" << std::endl;
    for (const auto& [item, quantity] : inventory)
    {
      std::cout << "  " << item << ": " << quantity << std::endl;
    }

    std::cout << "\nHealth Potions: " << inventory["Health Potion"] << std::endl;

    inventory["Health Potion"]--;
    std::cout << "After using one: " << inventory["Health Potion"] << std::endl;

    if (inventory.count("Iron Sword"))
    {
      std::cout << "We have the Iron Sword!" << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 2: Set (unique values)
  std::cout << "--- std::set (Seen Levels) ---" << std::endl;
  {
    std::set<int> seen_levels;

    seen_levels.insert(1);
    seen_levels.insert(5);
    seen_levels.insert(3);
    seen_levels.insert(1);  // Duplicate
    seen_levels.insert(5);  // Duplicate

    std::cout << "Levels completed (sorted, no duplicates):" << std::endl;
    for (int level : seen_levels)
    {
      std::cout << "  Level " << level << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 3: Queue (FIFO)
  std::cout << "--- std::queue (Event Queue) ---" << std::endl;
  {
    std::queue<std::string> events;

    events.push("PlayerDamaged");
    events.push("EnemySpawned");
    events.push("ItemCollected");

    std::cout << "Processing events:" << std::endl;
    while (!events.empty())
    {
      std::string event = events.front();
      events.pop();
      std::cout << "  - " << event << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 4: Stack (LIFO - undo/redo)
  std::cout << "--- std::stack (Undo Stack) ---" << std::endl;
  {
    std::stack<std::string> undo_stack;

    undo_stack.push("Moved to position (10, 5)");
    undo_stack.push("Attacked enemy");
    undo_stack.push("Used health potion");

    std::cout << "Undoing actions:" << std::endl;
    while (!undo_stack.empty())
    {
      std::string action = undo_stack.top();
      undo_stack.pop();
      std::cout << "  - Undo: " << action << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 5: Game config (map of settings)
  std::cout << "--- Game Config ---" << std::endl;
  {
    std::map<std::string, int> config;

    config["MaxPlayers"] = 4;
    config["DifficultyLevel"] = 2;
    config["ScreenWidth"] = 1920;
    config["ScreenHeight"] = 1080;
    config["MasterVolume"] = 80;

    std::cout << "Game Configuration:" << std::endl;
    for (const auto& [setting, value] : config)
    {
      std::cout << "  " << setting << " = " << value << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Exercise 6: Asset manager pattern
  std::cout << "--- Asset Manager (Map of Pointers) ---" << std::endl;
  {
    std::unordered_map<std::string, int> assets;
    assets["player_texture"] = 1024;
    assets["enemy_texture"] = 512;
    assets["background_music"] = 4096;

    std::cout << "Loaded assets:" << std::endl;
    for (const auto& [name, size] : assets)
    {
      std::cout << "  " << name << ": " << size << " KB" << std::endl;
    }

    // Find asset
    std::string look_for = "enemy_texture";
    if (assets.find(look_for) != assets.end())
    {
      std::cout << "\nFound asset: " << look_for
        << " (Size: " << assets[look_for] << " KB)" << std::endl;
    }

    std::cout << std::endl;
  }

  // Task:
  std::cout << "--- std::map (Enemy Difficulties) ---" << std::endl;
  {
    std::unordered_map<std::string, std::string> enemies;

    enemies["Goblin"] = "Easy";
    enemies["Troll"] = "Deadly";
    enemies["Beast"] = "Hard";
    enemies["Humanoid"] = "Normal";

    std::cout << "Enemies:" << std::endl;
    for (const auto& [item, quantity] : enemies)
    {
      std::cout << "  " << item << ": " << quantity << std::endl;
    }

    std::cout << "\nGoblin Difficulty level: " << enemies["Goblin"] << std::endl;
    std::cout << "\nHumanoid Difficulty level: " << enemies["Humanoid"] << std::endl;

    for (const auto& [enemy, difficulty] : enemies)
    {
      if (difficulty == "Deadly")
        std::cout << "\nDeadliest Enemy is: " << enemy << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << "=== END ===" << std::endl;

  return 0;
}