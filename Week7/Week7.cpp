#include <iostream>
#include "Day1_DesignPatterns.cpp"
#include "Day2_MiniEngine.cpp"

int main() {

  std::cout << "=== WEEK 7: DESIGN PATTERNS & MINI ENGINE ===" << std::endl << std::endl;
  std::cout << "[1] For Running Day 1: Design Patterns." << std::endl;
  std::cout << "[2] For Running Day 2: Mini Engine." << std::endl;

  int choice;
  std::cin >> choice; // Get user choice

  if(choice == 1)
    Day1_DesignPatterns::Execute();
  else if(choice == 2)
    Day2_MiniEngine::Execute();

  return 0;
}