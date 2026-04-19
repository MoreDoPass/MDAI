#pragma once
#include <vector>
#include <memory>
#include "UtilityActionRecord.h"

namespace uai
{

    // Мозг Utility AI. Собирает все записи и выбирает лучшую.
    class UtilityBrain
    {
    public:
        void addRecord(std::unique_ptr<UtilityActionRecord> record)
        {
            m_records.push_back(std::move(record));
        }

        // Вызывается каждый тик
        void tick(BTContext &context)
        {
            float bestScore = 0.0f; // Ниже нуля не берем
            IUtilityAction *bestAction = nullptr;

            // Перебираем все возможные действия
            for (auto &record : m_records)
            {
                float currentScore = record->evaluate(context);
                if (currentScore > bestScore)
                {
                    bestScore = currentScore;
                    bestAction = record->getAction();
                }
            }

            // Выполняем то, что набрало больше всего баллов
            if (bestAction && bestScore > 0.0f)
            {
                bestAction->execute(context);
            }
        }

    private:
        std::vector<std::unique_ptr<UtilityActionRecord>> m_records;
    };
} // namespace uai