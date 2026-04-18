cmake_minimum_required(VERSION 3.20)
project(MDAI VERSION 1.0.0 LANGUAGES CXX)

# Создаем статическую библиотеку
add_library(MDAI STATIC
    src/BehaviorTree/InverterNode.cpp
    src/BehaviorTree/RunWhileConditionDecorator.cpp
    src/BehaviorTree/SelectorNode.cpp
    src/BehaviorTree/SequenceNode.cpp
    src/BehaviorTree/WhileSuccessDecorator.cpp
)

# Указываем стандарта C++17 (нужен для твоих fold expressions)
target_compile_features(MDAI PUBLIC cxx_std_17)

# Папка src становится корневой для инклудов этой библиотеки
target_include_directories(MDAI PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)