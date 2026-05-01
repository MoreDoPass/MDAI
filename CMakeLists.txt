cmake_minimum_required(VERSION 3.20)
project(MDAI VERSION 1.0.0 LANGUAGES CXX)

# Создаем статическую библиотеку
# Мы перечисляем и .cpp (для компиляции) и .h (для красоты в IDE)
add_library(MDAI STATIC
    # Behavior Tree Core
    src/BehaviorTree/InverterNode.cpp
    src/BehaviorTree/RunWhileConditionDecorator.cpp
    src/BehaviorTree/SelectorNode.cpp
    src/BehaviorTree/SequenceNode.cpp
    src/BehaviorTree/SuccessNode.cpp
    src/BehaviorTree/FailNode.cpp
    src/BehaviorTree/WhileSuccessDecorator.cpp
    
    # Зонтичные заголовки (Umbrella Headers)
    src/BehaviorTree/BehaviorTree.h
    src/UtilityAI/UtilityAI.h
    
    # Utility AI (пока только заголовки, поэтому просто для видимости в IDE)
    src/UtilityAI/IUtilityAction.h
    src/UtilityAI/IUtilityScorer.h
    src/UtilityAI/UtilityActionRecord.h
    src/UtilityAI/UtilityBrain.h
)

# Указываем стандарта C++17 (нужен для твоих fold expressions)
target_compile_features(MDAI PUBLIC cxx_std_17)

# Папка src становится корневой для инклудов этой библиотеки
target_include_directories(MDAI PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)