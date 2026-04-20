#pragma once
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <map>
#include <functional>
#include "BTNode.h"

namespace bt
{

    using json = nlohmann::json;

    /**
     * @class BTBuilder
     * @brief Класс для рекурсивной сборки дерева поведения из JSON.
     */
    class BTBuilder
    {
    public:
        // Функция-создатель узла. Принимает JSON-объект с параметрами узла.
        using NodeCreator = std::function<std::unique_ptr<BTNode>(const json &)>;

        BTBuilder();

        /**
         * @brief Регистрирует новый тип узла.
         * @param type Строковое имя типа (например, "CastSpell")
         * @param creator Лямбда, которая создаст объект этого класса
         */
        void registerNode(const std::string &type, NodeCreator creator);

        /**
         * @brief Строит узел (и всю его ветку) из JSON
         */
        std::unique_ptr<BTNode> buildFromJson(const json &data);

        /**
         * @brief Загружает JSON из файла и строит дерево
         */
        std::unique_ptr<BTNode> loadFromFile(const std::string &filename);

    private:
        std::map<std::string, NodeCreator> m_registry;

        // Регистрация узлов самого фреймворка (Sequence, Selector и т.д.)
        void registerStandardNodes();
    };

} // namespace bt