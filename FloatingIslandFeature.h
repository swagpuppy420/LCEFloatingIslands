#pragma once
#include "Feature.h"

class FloatingIslandFeature : public Feature
{
public:
    virtual bool place(Level *level, Random *random, int x, int y, int z);
	WeighedTreasureArray RANDOM_BONUS_ITEMS;
    shared_ptr<ItemInstance> randomItem(Random *random);

};