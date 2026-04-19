#pragma once
class BTContext;

namespace uai
{
    // Оценщик (Аналог Multiplier в mod-playerbots).
    class IUtilityScorer
    {
    public:
        virtual ~IUtilityScorer() = default;

        // Возвращает число (обычно от 0.0 до 1.0)
        virtual float score(BTContext &context) = 0;
    };
} // namespace uai