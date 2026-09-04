#include <iostream>
#include "Day1_DesignPatterns.h"
#include "Day2_MiniEngine.h"
#include "Day3_Challenges.h"

int main() {

  std::cout << "=== WEEK 7: DESIGN PATTERNS & MINI ENGINE ===" << std::endl << std::endl;
  std::cout << "[1] For Running Day 1: Design Patterns." << std::endl;
  std::cout << "[2] For Running Day 2: Mini Engine." << std::endl;
  std::cout << "[3] For Running Day 3: Challenges." << std::endl;
  std::cout << "[4] Save the Game." << std::endl;
  std::cout << "[5] Load the Game." << std::endl;

  int choice;
  std::cin >> choice; // Get user choice

  if(choice == 1)
    Day1_DesignPatterns::Execute();
  else if(choice == 2)
    Day2_MiniEngine::Execute(false);
  else if (choice == 3)
    Day3_Challenges::Execute();
  else if (choice == 4) {
    Day2_MiniEngine::Execute(true);
  }
  else if (choice == 5) {
    Day2_MiniEngine::LoadAndExecute();
  }
  else
    std::cout << "Invalid choice. Exiting." << std::endl;

  return 0;
}