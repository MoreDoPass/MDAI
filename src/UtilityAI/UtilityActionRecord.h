#pragma once
#include <memory>
#include <vector>
#include "IUtilityAction.h"
#include "IUtilityScorer.h"

namespace uai
{
    // Контейнер, который связывает 1 Действие и список его Оценщиков
    class UtilityActionRecord
    {
    public:
        explicit UtilityActionRecord(std::unique_ptr<IUtilityAction> action)
            : m_action(std::move(action)) {}

        void addScorer(std::unique_ptr<IUtilityScorer> scorer)
        {
            m_scorers.push_back(std::move(scorer));
        }

        // Главная математика Utility AI
        float evaluate(BTContext &context)
        {
            float finalScore = 1.0f; // Базовый вес
            for (auto &scorer : m_scorers)
            {
                finalScore *= scorer->score(context); // Умножаем вес на все оценки

                // Оптимизация: если какой-то оценщик вернул 0 (например, спелл на КД), дальше не считаем
                if (finalScore <= 0.0001f)
                    break;
            }
            return finalScore;
        }

        IUtilityAction *getAction() const { return m_action.get(); }

    private:
        std::unique_ptr<IUtilityAction> m_action;
        std::vector<std::unique_ptr<IUtilityScorer>> m_scorers;
    };
} // namespace uai