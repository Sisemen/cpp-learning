#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>

struct PlayerStats
{
  int level;
  int experience;
  int health;
};

void DoTaskOne()
{
  std::cout << "Challenge:" << std::endl;
  std::cout << "1. Create map<string, PlayerStats> for multiple players" << std::endl;
  std::cout << "2. Add 3 players with different stats" << std::endl;
  std::cout << "3. Find player by name and level them up" << std::endl;
  std::cout << "4. Display all players sorted by level (hint: map is sorted!)" << std::endl;
  std::cout << std::endl << std::endl;

  std::map<std::string, PlayerStats> stats = {
    {"Hero", {1, 0, 50}},
    {"DeathAnger", {5, 200, 170}},
    {"WolfSpirit", {2, 50, 80}},
    {"DeathMiracle", {2, 50, 80}}
  };

  std::vector<const std::pair<const std::string, PlayerStats>*> sortedList;
  sortedList.reserve(stats.size());

  for (auto& entry : stats)
  {
    entry.second.level++;
    entry.second.experience += 50;
    entry.second.health += 30;
    std::cout << "Player: " << entry.first << " has been leveled up. Level: " << entry.second.level << std::endl;
    sortedList.emplace_back(&entry);
  }

  std::cout << "\nPlayers ordered by level:\n" << std::endl;

  std::sort(sortedList.begin(), sortedList.end(),
    [](const auto* a, const auto* b) {
      if (a->second.level != b->second.level)
        return a->second.level > b->second.level;
      return a->first < b->first;
    }
  );

  for (auto& item : sortedList)
  {
    std::cout << item->first << " is level: " << item->second.level << std::endl;
  }
}

void ConsumeItem(std::vector<std::string>& inventory, int slot) {
  slot--; // Adjust for 1-based indexing
  if (slot < 0 || slot >= inventory.size()) {
    std::cout << "Invalid slot number." << std::endl;
    return;
  }
  if (inventory[slot] == "Empty") {
    std::cout << "Slot " << slot + 1 << " is already empty." << std::endl;
    return;
  }
  std::cout << "Consuming item: " << inventory[slot] << " from slot " << slot + 1 << std::endl;
  inventory[slot] = "Empty";
}

void SwapItems(std::vector<std::string>& inventory, int slot1, int slot2) {
  slot1--; // Adjust for 1-based indexing
  slot2--; // Adjust for 1-based indexing
  if (slot1 < 0 || slot1 >= inventory.size() || slot2 < 0 || slot2 >= inventory.size()) {
    std::cout << "Invalid slot numbers." << std::endl;
    return;
  }
  std::swap(inventory[slot1], inventory[slot2]);
  std::cout << "Swapped items between slot " << slot1 + 1 << " and slot " << slot2 + 1 << std::endl;
}

void DisplayInventory(const std::vector<std::string>& inventory) {
  std::cout << "Inventory:" << std::endl;
  for (size_t i = 0; i < inventory.size(); ++i) {
    std::cout << "Slot " << i + 1 << ": " << inventory[i] << std::endl;
  }
}

void DoTaskTwo() {
  std::cout << "Challenge:" << std::endl;
  std::cout << "1. Create vector<string> of 10 inventory slots" << std::endl;
  std::cout << "2. Insert items at specific slots" << std::endl;
  std::cout << "3. Remove items from slots" << std::endl;
  std::cout << "4. Display inventory (show empty slots)" << std::endl;
  std::cout << "5. Swap items between slots" << std::endl;
  std::cout << std::endl;
  std::cout << "Bonus:" << std::endl;
  std::cout << "- Use unordered_map for quick item lookup" << std::endl;
  std::cout << "- Keep count of each item type" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::vector<std::string> inventory;

  inventory.reserve(10);

  inventory.emplace_back("Potion");
  inventory.emplace_back("Sword");
  inventory.emplace_back("Dagger");
  inventory.emplace_back("Bandage");
  inventory.emplace_back("Elixir");
  inventory.emplace_back("Havij");
  inventory.emplace_back("Bastani");
  inventory.emplace_back("Junk");
  inventory.emplace_back("Zahremari");
  inventory.emplace_back("Book");

  std::cout << "Initial Inventory:" << std::endl;
  DisplayInventory(inventory);
  std::cout << std::endl;

  ConsumeItem(inventory, 7);
  ConsumeItem(inventory, 3);

  std::cout << std::endl;

  std::cout << "Inventory after consuming items:" << std::endl;
  DisplayInventory(inventory);
  std::cout << std::endl;

  SwapItems(inventory, 1, 4);
  SwapItems(inventory, 9, 3);

  std::cout << std::endl;

  std::cout << "Inventory after swapping items:" << std::endl;
  DisplayInventory(inventory);
  std::cout << std::endl;
}

void DoTaskTwoBonus() {
  std::unordered_map<std::string, int> itemCount;
  std::vector<std::string> inventory = { "Potion", "Sword", "Dagger", "Potion", "Elixir", "Sword" };
  for (const auto& item : inventory) {
    itemCount[item]++;
  }
  std::cout << "Item counts in inventory:" << std::endl;
  for (const auto& pair : itemCount) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }
}

enum class EventType
{
  PlayerDamaged,
  EnemySpawned,
  ItemCollected,
  LevelUp
};

struct GameEvent
{
  EventType type;
  std::string data;
};

void EventHandler(const GameEvent& event, std::unordered_map<EventType, int>& eventsCounter, bool isPriority) {

  std::cout << (isPriority ? "Priority " : "") << "Event: " << event.data << std::endl;

  eventsCounter[event.type]++;
}

void DoTaskThree() {
  std::cout << "Challenge:" << std::endl;
  std::cout << "1. Create queue<GameEvent>" << std::endl;
  std::cout << "2. Simulate game events" << std::endl;
  std::cout << "3. Process events in order" << std::endl;
  std::cout << "4. Count each type of event" << std::endl;
  std::cout << "5. Create a priority queue (advanced)" << std::endl;
  std::cout << std::endl;

  std::unordered_map<EventType, int> eventsCounter = {
      {EventType::PlayerDamaged, 0},
      {EventType::EnemySpawned, 0},
      {EventType::ItemCollected, 0},
      {EventType::LevelUp, 0}
  };
  std::queue<GameEvent> priorityQueue;
  std::queue<GameEvent> gameEvents;

  gameEvents.push({ EventType::EnemySpawned, "New Enemy Spawned." });
  gameEvents.push({ EventType::PlayerDamaged, "Player Dealt 10 Damage." });
  gameEvents.push({ EventType::PlayerDamaged, "Player Dealt 10 Damage." });
  gameEvents.push({ EventType::ItemCollected, "Player Collected a Potion." });
  gameEvents.push({ EventType::PlayerDamaged, "Player Dealt 10 Damage." });
  gameEvents.push({ EventType::ItemCollected, "Player Collected a Sword." });
  gameEvents.push({ EventType::EnemySpawned, "New Enemy Spawned." });
  gameEvents.push({ EventType::PlayerDamaged, "Player Dealt 10 Damage." });
  gameEvents.push({ EventType::EnemySpawned, "New Enemy Spawned." });
  gameEvents.push({ EventType::PlayerDamaged, "Player Dealt 10 Damage." });

  while (!gameEvents.empty() || !priorityQueue.empty()) {
    while (!priorityQueue.empty()) {
      auto& event = priorityQueue.front();

      EventHandler(event, eventsCounter, true);

      priorityQueue.pop();
    }

    if (gameEvents.empty()) continue;

    auto& event = gameEvents.front();

    EventHandler(event, eventsCounter, false);

    if (event.type == EventType::PlayerDamaged) {
      priorityQueue.push({ EventType::LevelUp, "Player Leveled Up." });
    }

    gameEvents.pop();
  }

  std::cout << std::endl;

  for (const auto& [eventType, count] : eventsCounter) {
    std::cout << "Number of ";

    switch (eventType)
    {
    case EventType::PlayerDamaged:
      std::cout << "PlayerDamaged";
      break;
    case EventType::EnemySpawned:
      std::cout << "EnemySpawned";
      break;
    case EventType::ItemCollected:
      std::cout << "ItemCollected";
      break;
    case EventType::LevelUp:
      std::cout << "LevelUp";
      break;
    default:
      break;
    }

    std::cout << " Events: " << count << std::endl;
  }
}

int main()
{
  DoTaskOne();

  DoTaskTwo();

  DoTaskTwoBonus();

  DoTaskThree();

  return 0;
}