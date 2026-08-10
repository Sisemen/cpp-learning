#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Player
{
  std::string name;
  std::string faction;
  int level;
  int health;
  int experience;

  void SaveToFile(const std::string& filename) const
  {
    std::ofstream file(filename);

    if (!file)
    {
      std::cout << "Error opening file for writing!" << std::endl;
      return;
    }

    file << name << std::endl;
    file << faction << std::endl;
    file << level << std::endl;
    file << health << std::endl;
    file << experience << std::endl;

    std::cout << "[SAVE] Player saved to " << filename << std::endl;
  }

  void LoadFromFile(const std::string& filename)
  {
    std::ifstream file(filename);

    if (!file)
    {
      std::cout << "Error opening file for reading!" << std::endl;
      return;
    }

    file >> name >> faction >> level >> health >> experience;

    std::cout << "[LOAD] Player loaded from " << filename << std::endl;
  }

  void Display() const
  {
    std::cout << "Player: " << name
      << " | Faction: " << faction
      << " | Level: " << level
      << " | Health: " << health
      << " | XP: " << experience << std::endl;
  }
};

struct Enemy
{
  std::string name;
  std::string race;
  int level;
  int health;

  void SaveToFile(const std::string& filename) const
  {
    std::ofstream file(filename);
    if (!file)
    {
      std::cout << "Error opening file!" << std::endl;
      return;
    }
    file << name << std::endl;
    file << race << std::endl;
    file << level << std::endl;
    file << health << std::endl;
    
    std::cout << "[SAVE] Enemy saved to " << filename << std::endl;
  }

  void LoadFromFile(const std::string& filename)
  {
    std::ifstream file(filename);
    if (!file)
    {
      std::cout << "Error opening file!" << std::endl;
      return;
    }

    file >> name >> race >> level >> health;

    std::cout << "[LOAD] Enemy loaded from " << filename << std::endl;
  }

  void Display() const
  {
    std::cout
      << "Enemy: " << name
      << " | Race: " << race
      << " | Level: " << level
      << " | Health: " << health << std::endl;
  }
};

struct GameState
{
  std::string levelName;
  int playerLevel;
  std::vector<std::string> inventory;

  void SaveToFile(const std::string& filename) const
  {
    std::ofstream file(filename);

    if (!file)
    {
      std::cout << "Error opening file!" << std::endl;
      return;
    }

    file << levelName << std::endl;
    file << playerLevel << std::endl;
    file << inventory.size() << std::endl;

    for (const auto& item : inventory)
    {
      file << item << std::endl;
    }

    std::cout << "[SAVE] Game state saved to " << filename << std::endl;
  }

  void LoadFromFile(const std::string& filename)
  {
    std::ifstream file(filename);

    if (!file)
    {
      std::cout << "Error opening file!" << std::endl;
      return;
    }

    file >> levelName >> playerLevel;

    int invSize;
    file >> invSize;

    inventory.clear();
    for (int i = 0; i < invSize; i++)
    {
      std::string item;
      file >> item;
      inventory.push_back(item);
    }

    std::cout << "[LOAD] Game state loaded from " << filename << std::endl;
  }

  void Display() const
  {
    std::cout << "Level: " << levelName << " | Player Level: " << playerLevel << std::endl;
    std::cout << "Inventory (" << inventory.size() << " items):" << std::endl;
    for (const auto& item : inventory)
    {
      std::cout << "  - " << item << std::endl;
    }
  }
};

int main()
{
  std::cout << "=== FILE I/O BASICS ===" << std::endl << std::endl;

  // Exercise 1: Write to file
  std::cout << "--- Exercise 1: Writing to File ---" << std::endl;
  {
    std::ofstream file("test.txt");

    file << "Hello, File I/O!" << std::endl;
    file << 42 << std::endl;
    file << 3.14 << std::endl;

    std::cout << "Data written to test.txt" << std::endl << std::endl;
  }

  // Exercise 2: Read from file
  std::cout << "--- Exercise 2: Reading from File ---" << std::endl;
  {
    std::ifstream file("test.txt");

    if (!file)
    {
      std::cout << "Error opening file!" << std::endl;
      return 1;
    }

    std::string line;
    std::cout << "File contents:" << std::endl;
    while (std::getline(file, line))
    {
      std::cout << "  " << line << std::endl;
    }

    std::cout << std::endl;
  }

  // Exercise 3: Player save/load
  std::cout << "--- Exercise 3: Save/Load Player ---" << std::endl;
  {
    Player player1;
    player1.name = "Hero";
    player1.faction = "Knights";
    player1.level = 5;
    player1.health = 100;
    player1.experience = 1500;

    std::cout << "Original player:" << std::endl;
    player1.Display();

    player1.SaveToFile("player_save.txt");
    std::cout << std::endl;

    // Load into new player
    Player player2;
    player2.LoadFromFile("player_save.txt");

    std::cout << "Loaded player:" << std::endl;
    player2.Display();

    std::cout << std::endl;
  }

  // Exercise 4: Game state save/load
  std::cout << "--- Exercise 4: Save/Load Game State ---" << std::endl;
  {
    GameState state;
    state.levelName = "Forest Level";
    state.playerLevel = 3;
    state.inventory = { "Sword", "Shield", "Health Potion", "Mana Potion" };

    std::cout << "Original game state:" << std::endl;
    state.Display();
    std::cout << std::endl;

    state.SaveToFile("gamestate.txt");
    std::cout << std::endl;

    // Load new state
    GameState loaded;
    loaded.LoadFromFile("gamestate.txt");

    std::cout << "Loaded game state:" << std::endl;
    loaded.Display();
    std::cout << std::endl;
  }

  // Exercise 5: Multiple saves
  std::cout << "--- Exercise 5: Multiple Save Slots ---" << std::endl;
  {
    std::vector<Player> players;

    Player p1;
    p1.name = "Warrior";
    p1.faction = "Barbarians";
    p1.level = 10;
    p1.health = 150;
    p1.experience = 5000;

    Player p2;
    p2.name = "Mage";
    p2.faction = "Wizards";
    p2.level = 8;
    p2.health = 80;
    p2.experience = 3500;

    players.push_back(p1);
    players.push_back(p2);

    std::cout << "Saving multiple players to different files:" << std::endl;
    for (int i = 0; i < players.size(); i++)
    {
      std::string filename = "save_slot_" + std::to_string(i) + ".txt";
      players[i].SaveToFile(filename);
    }

    std::cout << std::endl;

    std::cout << "Loading and displaying all saves:" << std::endl;
    for (int i = 0; i < 2; i++)
    {
      std::string filename = "save_slot_" + std::to_string(i) + ".txt";
      Player p;
      p.LoadFromFile(filename);
      p.Display();
    }
  }

  // Exercise 6: Multiple Enemies save/load
  std::cout << "--- Exercise 6: Multiple Enemies Save/Load ---" << std::endl;
  {
    std::vector<Enemy> enemies;
    enemies.reserve(2);

    Enemy e1{ "Black_Hand", "Orc", 2, 30 };
    enemies.emplace_back(e1);

    Enemy e2{ "White_Fang", "Wolf", 3, 50 };
    enemies.emplace_back(e2);
    
    for (auto& enemy : enemies)
    {
      enemy.Display();

      std::string filename = enemy.name + ".txt";
      enemy.SaveToFile(filename);
    }


    std::cout << "Loading enemies from files:" << std::endl;

    for (auto& enemy : enemies)
    {
      std::string filename = enemy.name + ".txt";
      Enemy loaded;

      loaded.LoadFromFile(filename);
      loaded.Display();
    }
  }

  std::cout << "\n=== END ===" << std::endl;

  return 0;
}