#include "SuccessNode.h"

namespace bt
{
    NodeStatus SuccessNode::tick(BTContext & /*context*/)
    {
        return NodeStatus::Success;
    }
}