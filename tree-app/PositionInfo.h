#pragma once

template <typename ElementIdType>
struct PositionInfo
{
    ElementIdType parentId_;
    ElementIdType prevElementId_;

    PositionInfo(ElementIdType parentId, ElementIdType prevElementId) :
        parentId_(parentId), prevElementId_(prevElementId)
    {

    }
};
