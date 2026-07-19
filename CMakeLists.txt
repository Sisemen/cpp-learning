cmake_minimum_required(VERSION 3.16)
project(WeekOneDayOne)
project(WeekOneDayTwo)
project(WeekOneDayThree)
project(WeekOneDayFour)
project(WeekOneDayFive)
project(WeekOneDaySix)
project(WeekOneDaySeven)

project(WeekTwoDayOne)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WeekOneDayOne Week1/Day1_HelloWorld.cpp "Week1/Day1_HelloWorld.cpp")
add_executable(WeekOneDayTwo Week1/Day2_Variables.cpp "Week1/Day2_Variables.cpp")
add_executable(WeekOneDayThree Week1/Day3_Math.cpp "Week1/Day3_Math.cpp")
add_executable(WeekOneDayFour Week1/Day4_IfElse.cpp "Week1/Day4_IfElse.cpp")
add_executable(WeekOneDayFive Week1/Day5_Loops.cpp "Week1/Day5_Loops.cpp")
add_executable(WeekOneDaySix Week1/Day6_Functions.cpp "Week1/Day6_Functions.cpp")
add_executable(WeekOneDaySeven Week1/Day7_CharacterCreator.cpp "Week1/Day7_CharacterCreator.cpp")

add_executable(WeekTwoDayOne Week2/Day1_Addresses.cpp "Week2/Day1_Addresses.cpp")
