#include <iostream>
#include <tuple>
#include <cstdlib>

struct Player
{
  std::string name;
  int health;
  int mana;
  std::string role;
};

void LogPlayerStats(Player* playerPtr)
{
  std::cout << "Player name: " << playerPtr->name << "; Health: " << playerPtr->health << "; Mana: " << playerPtr->mana << ";" << std::endl;
}

void HealPlayer(Player* playerPtr)
{
  playerPtr->health = playerPtr->health + 10;
}

bool HealByHealer(Player* healer, Player* player)
{
  if (healer->mana - 5 >= 0)
  {
    healer->mana -= 5;
    player->health += 10;

    return true;
  }
  else
  {
    std::cout << "Healer is out of mana!!!" << std::endl;
    LogPlayerStats(healer);

    return false;
  }
}

void DoPlayerStatusManager()
{
  std::cout << "================== Player Status Manager ==================" << std::endl;
  std::cout << "Your tasks:" << std::endl;
  std::cout << "1. Create 3 players on the STACK" << std::endl;
  std::cout << "2. Create a pointer to the first player" << std::endl;
  std::cout << "3. Use pointer arithmetic to iterate through all 3" << std::endl;
  std::cout << "4. Print each player's stats using pointer" << std::endl;
  std::cout << "5. Create a function that takes a Player* and heals them by 10" << std::endl;
  std::cout << "6. Call that function using pointers" << std::endl;
  std::cout << std::endl;

  // Your tasks:
  // 1. Create 3 players on the STACK
  Player players[3] =
  {
    {"Nemesis", 100, 40, "Damage Dealer"},
    {"Deathanger", 120, 30, "Tank"},
    {"Wolfspirit", 80, 50, "Healer"}
  };

  // 2. Create a pointer to the first player
  Player* playerPtr = &players[0];

  // 3. Use pointer arithmetic to iterate through all 3
  for (int i = 0; i < 3; i++) {
    // 4. Print each player's stats using pointer
    LogPlayerStats(playerPtr);

    playerPtr++;
  }

  std::cout << std::endl;

  // 5. Create a function that takes a Player* and heals them by 10
  // 6. Call that function using pointers

  playerPtr = &players[1];

  HealPlayer(playerPtr);
  LogPlayerStats(playerPtr);

  std::cout << std::endl;

  Player* healerPtr = &players[2];

  playerPtr = &players[0];

  while (HealByHealer(healerPtr, playerPtr))
  {
    LogPlayerStats(playerPtr);
  }

  std::cout << std::endl;
}

std::tuple<int, int, int> FindMinMax(int* arrayPtr, int* arrayEnd)
{
  int i = 0;
  int min = *arrayPtr;
  int max = *arrayPtr;
  int sum = 0;

  while (arrayPtr <= arrayEnd) {
    if (*arrayPtr > max) max = *arrayPtr;
    if (*arrayPtr < min) min = *arrayPtr;

    sum += *arrayPtr;

    arrayPtr++;
  }

  return { min, max, sum };
}

void DoDynamicArrayManagement()
{
  std::cout << "================== Dynamic Array Management ==================" << std::endl;
  std::cout << "1. Dynamically allocate array of 10 integers" << std::endl;
  std::cout << "2. Initialize all values using pointer arithmetic" << std::endl;
  std::cout << "3. Find max using pointer iteration" << std::endl;
  std::cout << "4. Find min using pointer iteration" << std::endl;
  std::cout << "5. Calculate sum using pointer iteration" << std::endl;
  std::cout << "6. Properly cleanup" << std::endl;
  std::cout << std::endl;

  int* numbersArray = new int[10];
  int* numberPtr = &numbersArray[0];

  for (int i = 0; i < 10; i++) {
    *numberPtr = rand() % 1001;
    numberPtr++;
  }
  
  numberPtr = &numbersArray[0];

  std::cout << "Array: ";
  for (int i = 0; i < 10; i++) {
    std::cout << *numberPtr << (i < 9 ? ", " : "");
    numberPtr++;
  }


  std::cout << std::endl;
  int min, max, sum;
  std::tie(min, max, sum) = FindMinMax(&numbersArray[0], &numbersArray[9]);
  std::cout << "Minimume: " << min << ", Maximume: " << max << ", Sum: " << sum << std::endl;

  delete numbersArray;
  
  std::cout << std::endl;
}

void DoStringReversal()
{
  std::cout << "================== String Reversal ==================" << std::endl;
  std::cout << "1. Take a string input" << std::endl;
  std::cout << "2. Reverse it using pointer arithmetic" << std::endl;
  std::cout << "3. Print both original and reversed" << std::endl;
  std::cout << "4. Do NOT use std::reverse or built-in functions" << std::endl;
  std::cout << "5. Use only pointer operations" << std::endl;
  std::cout << std::endl;

  std::string inputText;
  std::cout << "Please enter a string: ";
  std::cin >> inputText;

  int ln = inputText.length();
  char* startPtr = &inputText[0];
  char* ptr = &inputText[ln - 1];

  std::cout << "The revers of your string is:" << std::endl;

  while (ptr >= startPtr)
  {
    std::cout << *ptr;
    ptr--;
  }

  std::cout << std::endl;
  std::cout << std::endl;
}

int main()
{
  DoPlayerStatusManager();

  DoDynamicArrayManagement();

  DoStringReversal();

  return 0;
}