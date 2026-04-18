#pragma once

#include <memory>
#include <vector>
#include <utility>

#include "BTNode.h"
#include "SequenceNode.h"
#include "SelectorNode.h"
#include "InverterNode.h"

/**
 * @brief Внутренний хелпер. Безопасно добавляет узел в вектор.
 * Если передан nullptr (например, ветка отключена в настройках), он просто игнорируется.
 */
inline void AddValidNode(std::vector<std::unique_ptr<BTNode>>& vec, std::unique_ptr<BTNode> node)
{
    if (node)
    {
        vec.push_back(std::move(node));
    }
}

/**
 * @brief Создает SequenceNode (Логическое "И")
 * @param args Любое количество std::unique_ptr<BTNode>
 */
template <typename... Args>
std::unique_ptr<SequenceNode> Sequence(Args&&... args)
{
    std::vector<std::unique_ptr<BTNode>> children;
    // Магия C++17 (Fold Expression)
    (AddValidNode(children, std::forward<Args>(args)), ...);
    return std::make_unique<SequenceNode>(std::move(children));
}

/**
 * @brief Создает SelectorNode (Логическое "ИЛИ")
 * @param args Любое количество std::unique_ptr<BTNode>
 */
template <typename... Args>
std::unique_ptr<SelectorNode> Selector(Args&&... args)
{
    std::vector<std::unique_ptr<BTNode>> children;
    (AddValidNode(children, std::forward<Args>(args)), ...);
    return std::make_unique<SelectorNode>(std::move(children));
}

/**
 * @brief Создает InverterNode (Логическое "НЕ")
 * @param child Дочерний узел, результат которого будет инвертирован
 */
inline std::unique_ptr<InverterNode> Inverter(std::unique_ptr<BTNode> child)
{
    if (!child) return nullptr;
    return std::make_unique<InverterNode>(std::move(child));
}

/**
 * @brief Создает любое Действие (Action)
 * @param args Аргументы, которые требуются конструктору твоего Action
 */
template <typename T, typename... Args>
std::unique_ptr<T> Action(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

/**
 * @brief Создает любое Условие (Condition)
 * @param args Аргументы, которые требуются конструктору твоего Condition
 */
template <typename T, typename... Args>
std::unique_ptr<T> Condition(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

/**
 * @brief Создает Декоратор, оборачивая один дочерний узел
 * @param child Узел, который нужно обернуть
 * @param args Дополнительные аргументы для конструктора декоратора (если есть)
 */
template <typename DecoratorType, typename... Args>
std::unique_ptr<DecoratorType> Decorator(std::unique_ptr<BTNode> child, Args&&... args)
{
    if (!child) return nullptr;
    return std::make_unique<DecoratorType>(std::move(child), std::forward<Args>(args)...);
}