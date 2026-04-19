#pragma once
class BTContext; // Используем тот же контекст, что и в Дереве!

namespace uai
{
    // Абстрактное действие, которое выберет Utility AI (например, "Уйти в гринд" или "Кастануть спелл")
    class IUtilityAction
    {
    public:
        virtual ~IUtilityAction() = default;

        // Этот метод вызовется, если действие победит в голосовании
        virtual void execute(BTContext &context) = 0;
    };
} // namespace uai