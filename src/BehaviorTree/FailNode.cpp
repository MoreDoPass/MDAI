#include "FailNode.h"

namespace bt
{
    NodeStatus FailNode::tick(BTContext & /*context*/)
    {
        return NodeStatus::Failure;
    }
}