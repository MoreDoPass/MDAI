#pragma once
#include "BTNode.h"

namespace bt
{
    class FailNode : public BTNode
    {
    public:
        NodeStatus tick(BTContext &context) override;
    };
} // namespace bt