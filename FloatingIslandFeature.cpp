#include "stdafx.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.tile.entity.h"
#include "FloatingIslandFeature.h"

//copyright frogmoney legit 2026

bool FloatingIslandFeature::place(Level *level, Random *random, int x, int y, int z)
{
    if (!level->isEmptyTile(x, y, z)) return false;
    //if (level->getTile(x, y + 1, z) != Tile::hellRock_Id) return false; //glowstone generate everywhere :D
	if (y < level->constSeaLevel+45) return false;
    level->setTile(x, y, z, Tile::dirt_Id);
	int radius = 7;
	int theta = 0;
	for (int ax = 0; ax < radius * 2; ax++){
		for (int ay = 0; ay < radius * 2; ay++){
			for (int az = 0; az < radius * 2; az++){
				int bx, by, bz;
				bx = ax - radius;
				by = ay - radius;
				bz = az - radius;
				if (bx * bx + by * by + bz * bz < radius * radius){
					level->setTile(x+bx, y+by, z+bz, Tile::dirt_Id);
				}
				if (by > 0){
					if (bx * bx + by * by + bz * bz == radius * radius){
						level->setTile(x+bx, y+by, z+bz, Tile::grass_Id);
					}
				}
			}
		}
	}
	level->setTile(x, y+radius, z, Tile::chest_Id);
			shared_ptr<ChestTileEntity> chest = dynamic_pointer_cast<ChestTileEntity >( level->getTileEntity(x, y+radius, z) );
			if (chest != NULL )
			{
				for (int j = 0; j < 8; j++)
				{
					shared_ptr<ItemInstance> item = randomItem(random);
					if (item != NULL) chest->setItem(random->nextInt(chest->getContainerSize()), item);
				}
			}
	//WeighedTreasure::addChestItems(random, RANDOM_BONUS_ITEMS, chest, 16);

	/*
    for (int i = 0; i < 1500; i++)
	{
        int x2 = x + random->nextInt(8) - random->nextInt(8);
        int y2 = y - random->nextInt(12);
        int z2 = z + random->nextInt(8) - random->nextInt(8);
        if (level->getTile(x2, y2, z2) != 0) continue;

        int count = 0;
        for (int t = 0; t < 6; t++)
		{
            int tile = 0;
            if (t == 0) tile = level->getTile(x2 - 1, y2, z2);
            if (t == 1) tile = level->getTile(x2 + 1, y2, z2);
            if (t == 2) tile = level->getTile(x2, y2 - 1, z2);
            if (t == 3) tile = level->getTile(x2, y2 + 1, z2);
            if (t == 4) tile = level->getTile(x2, y2, z2 - 1);
            if (t == 5) tile = level->getTile(x2, y2, z2 + 1);

            if (tile == Tile::dirt_Id) count++;
        }

        if (count == 1) level->setTile(x2, y2, z2, Tile::dirt_Id);
    }
	*/
    return true;
}

shared_ptr<ItemInstance> FloatingIslandFeature::randomItem(Random *random)
{
	int type = random->nextInt(12);
	if (type == 0) return shared_ptr<ItemInstance>( new ItemInstance(Item::saddle) );
	if (type == 1) return shared_ptr<ItemInstance>( new ItemInstance(Item::ironIngot, random->nextInt(4) + 1) );
	if (type == 2) return shared_ptr<ItemInstance>( new ItemInstance(Item::bread) );
	if (type == 3) return shared_ptr<ItemInstance>( new ItemInstance(Item::wheat, random->nextInt(4) + 1) );
	if (type == 4) return shared_ptr<ItemInstance>( new ItemInstance(Item::sulphur, random->nextInt(4) + 1) );
	if (type == 5) return shared_ptr<ItemInstance>( new ItemInstance(Item::string, random->nextInt(4) + 1) );
	if (type == 6) return shared_ptr<ItemInstance>( new ItemInstance(Item::bucket_empty) );
	if (type == 7 && random->nextInt(100) == 0) return shared_ptr<ItemInstance>( new ItemInstance(Item::apple_gold) );
	if (type == 8 && random->nextInt(2) == 0) return shared_ptr<ItemInstance>( new ItemInstance(Item::redStone, random->nextInt(4) + 1) );
	if (type == 9 && random->nextInt(10) == 0) return shared_ptr<ItemInstance>( new ItemInstance( Item::items[Item::record_01->id + random->nextInt(2)]) );
	if (type == 10) return shared_ptr<ItemInstance>( new ItemInstance(Item::dye_powder, 1, DyePowderItem::BROWN) );
	if (type == 11) return Item::enchantedBook->createForRandomLoot(random);

	return shared_ptr<ItemInstance>();
}