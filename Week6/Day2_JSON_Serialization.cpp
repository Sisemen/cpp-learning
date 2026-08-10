#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

// NOTE: If using nlohmann/json:
// #include <nlohmann/json.hpp>
// using json = nlohmann::json;

// For this exercise, we'll create a simple JSON-like format
// (In real project, use nlohmann/json library)

struct InventoryItem
{
  std::string name;
  int quantity;
};

struct Player
{
  std::string name;
  int level;
  int health;
  int experience;
  std::vector<InventoryItem> inventory;

  // Simple JSON-like save (without external library)
  void SaveToFile(const std::string& filename) const
  {
    std::ofstream file(filename);

    file << "{\n";
    file << "  \"player\": {\n";
    file << "    \"name\": \"" << name << "\",\n";
    file << "    \"level\": " << level << ",\n";
    file << "    \"health\": " << health << ",\n";
    file << "    \"experience\": " << experience << ",\n";
    file << "    \"inventory\": [\n";

    for (size_t i = 0; i < inventory.size(); i++)
    {
      file << "      {\n";
      file << "        \"name\": \"" << inventory[i].name << "\",\n";
      file << "        \"quantity\": " << inventory[i].quantity << "\n";
      file << "      }";

      if (i < inventory.size() - 1)
        file << ",";
      file << "\n";
    }

    file << "    ]\n";
    file << "  }\n";
    file << "}\n";

    std::cout << "[SAVE] Player saved to " << filename << std::endl;
  }

  void LoadFromFile(const std::string& filename)
  {
    std::ifstream file(filename);

    if (!file)
    {
      std::cout << "Error opening file!" << std::endl;
      return;
    }

    // Simple parsing (in real code, use json library)
    std::string line;
    int line_num = 0;

    while (std::getline(file, line))
    {
      line_num++;

      if (line.find("\"name\":") != std::string::npos && line_num < 10)
      {
        size_t start = line.find("\"") + 1;
        size_t end = line.rfind("\"");
        if (start != std::string::npos && end != std::string::npos && start < end)
        {
          name = line.substr(start, end - start);
        }
      }
      else if (line.find("\"level\":") != std::string::npos)
      {
        size_t start = line.find(":") + 1;
        level = std::stoi(line.substr(start));
      }
      else if (line.find("\"health\":") != std::string::npos)
      {
        size_t start = line.find(":") + 1;
        health = std::stoi(line.substr(start));
      }
      else if (line.find("\"experience\":") != std::string::npos)
      {
        size_t start = line.find(":") + 1;
        experience = std::stoi(line.substr(start));
      }
    }

    std::cout << "[LOAD] Player loaded from " << filename << std::endl;
  }

  void Display() const
  {
    std::cout << "Player: " << name
      << " | Level: " << level
      << " | Health: " << health
      << " | XP: " << experience << std::endl;

    std::cout << "Inventory:" << std::endl;
    for (const auto& item : inventory)
    {
      std::cout << "  - " << item.name << " x" << item.quantity << std::endl;
    }
  }
};

struct GameState
{
  std::string levelName;
  int playerLevel;
  std::vector<std::string> objectives;

  void SaveToFile(const std::string& filename) const
  {
    std::ofstream file(filename);

    file << "{\n";
    file << "  \"gameState\": {\n";
    file << "    \"level\": \"" << levelName << "\",\n";
    file << "    \"playerLevel\": " << playerLevel << ",\n";
    file << "    \"objectives\": [\n";

    for (size_t i = 0; i < objectives.size(); i++)
    {
      file << "      \"" << objectives[i] << "\"";
      if (i < objectives.size() - 1)
        file << ",";
      file << "\n";
    }

    file << "    ]\n";
    file << "  }\n";
    file << "}\n";

    std::cout << "[SAVE] Game state saved to " << filename << std::endl;
  }

  void Display() const
  {
    std::cout << "Level: " << levelName << " (Player Level: " << playerLevel << ")" << std::endl;
    std::cout << "Objectives:" << std::endl;
    for (const auto& obj : objectives)
    {
      std::cout << "  - " << obj << std::endl;
    }
  }
};

int main()
{
  std::cout << "=== JSON-LIKE SERIALIZATION ===" << std::endl << std::endl;

  // Exercise 1: Simple structured save
  std::cout << "--- Exercise 1: Game State Save ---" << std::endl;
  {
    GameState state;
    state.levelName = "Forest Level";
    state.playerLevel = 5;
    state.objectives = { "Find the treasure", "Defeat the boss", "Collect 10 gold" };

    std::cout << "Original state:" << std::endl;
    state.Display();
    std::cout << std::endl;

    state.SaveToFile("game_state.json");
    std::cout << std::endl;
  }

  // Exercise 2: Player with inventory
  std::cout << "--- Exercise 2: Player with Inventory ---" << std::endl;
  {
    Player player;
    player.name = "Hero";
    player.level = 5;
    player.health = 100;
    player.experience = 1500;

    player.inventory.reserve(6);
    player.inventory.push_back({ "Health Potion", 5 });
    player.inventory.push_back({ "Mana Potion", 3 });
    player.inventory.push_back({ "Iron Sword", 1 });
    player.inventory.push_back({ "Shield", 1 });
    player.inventory.push_back({ "Gold Coin", 250 });
    player.inventory.push_back({ "Magic Scroll", 2 });

    std::cout << "Original player:" << std::endl;
    player.Display();
    std::cout << std::endl;

    player.SaveToFile("player_save.json");
    std::cout << std::endl;
  }

  // Exercise 3: Display saved files
  std::cout << "--- Exercise 3: View Saved Files ---" << std::endl;
  {
    std::cout << "Game state file (game_state.json):" << std::endl;
    std::ifstream file("game_state.json");
    std::string line;
    while (std::getline(file, line))
    {
      std::cout << line << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Player file (player_save.json):" << std::endl;
    file.open("player_save.json");
    while (std::getline(file, line))
    {
      std::cout << line << std::endl;
    }
    std::cout << std::endl;
  }

  // Exercise 4: Multiple character saves
  std::cout << "--- Exercise 4: Multiple Characters ---" << std::endl;
  {
    std::vector<Player> characters;

    Player warrior;
    warrior.name = "Warrior";
    warrior.level = 10;
    warrior.health = 150;
    warrior.experience = 5000;
    warrior.inventory.push_back({ "Great Sword", 1 });
    warrior.inventory.push_back({ "Shield", 1 });

    Player mage;
    mage.name = "Mage";
    mage.level = 8;
    mage.health = 80;
    mage.experience = 3500;
    mage.inventory.push_back({ "Staff", 1 });
    mage.inventory.push_back({ "Spellbook", 1 });

    characters.push_back(warrior);
    characters.push_back(mage);

    std::cout << "Saving characters:" << std::endl;
    for (int i = 0; i < characters.size(); i++)
    {
      std::string filename = "character_" + std::to_string(i) + ".json";
      characters[i].SaveToFile(filename);
      std::cout << "  - " << characters[i].name << " -> " << filename << std::endl;
    }

    std::cout << std::endl;
  }

  // Exercise 5: Game progression
  std::cout << "--- Exercise 5: Game Progression ---" << std::endl;
  {
    GameState level1;
    level1.levelName = "Forest";
    level1.playerLevel = 2;
    level1.objectives = { "Collect mushrooms", "Find the exit" };

    GameState level2;
    level2.levelName = "Mountain";
    level2.playerLevel = 5;
    level2.objectives = { "Reach the summit", "Defeat dragon" };

    GameState level3;
    level3.levelName = "Castle";
    level3.playerLevel = 10;
    level3.objectives = { "Find the artifact", "Escape the castle" };

    GameState level4;
    level4.levelName = "Dungeon";
    level4.playerLevel = 15;
    level4.objectives = { "Defeat the boss", "Rescue the prisoner" };

    std::vector<GameState> levels = { level1, level2, level3, level4 };

    std::cout << "Saving all levels:" << std::endl;
    for (int i = 0; i < levels.size(); i++)
    {
      std::string filename = "level_" + std::to_string(i + 1) + ".json";
      levels[i].SaveToFile(filename);
      std::cout << "  - Level " << (i + 1) << " saved" << std::endl;
    }
  }

  std::cout << "\n=== END ===" << std::endl;
  std::cout << "\nNote: In real projects, use nlohmann/json library!" << std::endl;
  std::cout << "This exercise uses manual JSON formatting for learning." << std::endl;

  return 0;
}