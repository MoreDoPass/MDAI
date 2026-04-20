#include "BTBuilder.h"
#include "SequenceNode.h"
#include "SelectorNode.h"
#include "InverterNode.h"
#include "WhileSuccessDecorator.h"
#include <fstream>
#include <stdexcept>

namespace bt
{

    BTBuilder::BTBuilder()
    {
        registerStandardNodes();
    }

    void BTBuilder::registerNode(const std::string &type, NodeCreator creator)
    {
        m_registry[type] = creator;
    }

    void BTBuilder::registerStandardNodes()
    {
        // Вспомогательная функция для парсинга детей
        auto parseChildren = [this](const json &j)
        {
            std::vector<std::unique_ptr<BTNode>> children;
            if (j.contains("children") && j["children"].is_array())
            {
                for (const auto &childJson : j["children"])
                {
                    children.push_back(buildFromJson(childJson));
                }
            }
            return children;
        };

        // SEQUENCE
        registerNode("Sequence", [parseChildren](const json &j)
                     { return std::make_unique<SequenceNode>(parseChildren(j)); });

        // SELECTOR
        registerNode("Selector", [parseChildren](const json &j)
                     { return std::make_unique<SelectorNode>(parseChildren(j)); });

        // INVERTER
        registerNode("Inverter", [this](const json &j)
                     {
        if (!j.contains("child")) throw std::runtime_error("Inverter must have a child");
        return std::make_unique<InverterNode>(buildFromJson(j["child"])); });

        // WHILE SUCCESS
        registerNode("WhileSuccess", [this](const json &j)
                     {
        if (!j.contains("child")) throw std::runtime_error("WhileSuccess must have a child");
        return std::make_unique<WhileSuccessDecorator>(buildFromJson(j["child"])); });
    }

    std::unique_ptr<BTNode> BTBuilder::buildFromJson(const json &j)
    {
        if (!j.contains("type"))
        {
            throw std::runtime_error("JSON node missing 'type' field");
        }

        std::string type = j["type"].get<std::string>();

        auto it = m_registry.find(type);
        if (it != m_registry.end())
        {
            return it->second(j);
        }

        throw std::runtime_error("Unknown BT node type: " + type);
    }

    std::unique_ptr<BTNode> BTBuilder::loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("BTBuilder: Could not open file " + filename);
        }

        json data;
        file >> data;
        return buildFromJson(data);
    }

} // namespace bt