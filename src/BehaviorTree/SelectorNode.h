#pragma once
#include "BTNode.h"
#include <vector>
#include <memory>

/**
 * @brief Композитный узел "ИЛИ". Выполняет дочерние узлы по порядку,
 *        пока один из них не вернет Success или Running.

 * @return Success как только первый дочерний узел вернет Success.
 * @return Running как только первый дочерний узел вернет Running.
 * @return Failure только если ВСЕ дочерние узлы вернули Failure.
 **/
class SelectorNode : public BTNode
{
   public:
    /**
     * @brief Конструктор.
     * @param children Список дочерних узлов.
     */
    explicit SelectorNode(std::vector<std::unique_ptr<BTNode>> children);
    NodeStatus tick(BTContext& context) override;

   private:
    /// @brief Список дочерних узлов, которыми управляет этот узел.
    std::vector<std::unique_ptr<BTNode>> m_children;
};