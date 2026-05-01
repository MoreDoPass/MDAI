#pragma once
#include "BTNode.h"

namespace bt
{
    class SuccessNode : public BTNode
    {
    public:
        NodeStatus tick(BTContext &context) override;
    };
} // namespace bt