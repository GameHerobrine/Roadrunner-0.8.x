#include "item.hpp"
#include "shovelitem.hpp"
#include "pickaxeitem.hpp"
#include "hatchetitem.hpp"

using namespace RoadRunner::items;
Item* Item::items[512];

Item* Item::shovel_iron;
Item* Item::pickAxe_iron;
Item* Item::hatchet_iron;
Item* Item::flintAndSteel;
Item* Item::apple;
Item* Item::bow;
Item* Item::arrow;
Item* Item::coal;
Item* Item::diamond;
Item* Item::ironIngot;
Item* Item::goldIngot;
Item* Item::sword_iron;
Item* Item::sword_wood;
Item* Item::shovel_wood;
Item* Item::pickAxe_wood;
Item* Item::hatchet_wood;
Item* Item::sword_stone;
Item* Item::shovel_stone;
Item* Item::pickAxe_stone;
Item* Item::hatchet_stone;
Item* Item::sword_diamond;
Item* Item::shovel_diamond;
Item* Item::pickAxe_diamond;
Item* Item::hatchet_diamond;
Item* Item::stick;
Item* Item::bowl;
Item* Item::mushroomStew;
Item* Item::sword_gold;
Item* Item::shovel_gold;
Item* Item::pickAxe_gold;
Item* Item::hatchet_gold;
Item* Item::string;
Item* Item::feather;
Item* Item::sulphur;
Item* Item::hoe_wood;
Item* Item::hoe_stone;
Item* Item::hoe_iron;
Item* Item::hoe_diamond;
Item* Item::hoe_gold;
Item* Item::seeds_wheat;
Item* Item::wheat;
Item* Item::bread;
Item* Item::helmet_cloth;
Item* Item::chestplate_cloth;
Item* Item::leggings_cloth;
Item* Item::boots_cloth;
Item* Item::helmet_chain;
Item* Item::chestplate_chain;
Item* Item::leggings_chain;
Item* Item::boots_chain;
Item* Item::helmet_iron;
Item* Item::chestplate_iron;
Item* Item::leggings_iron;
Item* Item::boots_iron;
Item* Item::helmet_diamond;
Item* Item::chestplate_diamond;
Item* Item::leggings_diamond;
Item* Item::boots_diamond;
Item* Item::helmet_gold;
Item* Item::chestplate_gold;
Item* Item::leggings_gold;
Item* Item::boots_gold;
Item* Item::flint;
Item* Item::porkChop_raw;
Item* Item::porkChop_cooked;
Item* Item::painting;
Item* Item::sign;
Item* Item::door_wood;
Item* Item::bucket;
Item* Item::minecart;
Item* Item::saddle;
Item* Item::door_iron;
Item* Item::redStone;
Item* Item::snowBall;
Item* Item::leather;
Item* Item::brick;
Item* Item::clay;
Item* Item::reeds;
Item* Item::paper;
Item* Item::book;
Item* Item::slimeBall;
Item* Item::egg;
Item* Item::compass;
Item* Item::clock;
Item* Item::yellowDust;
Item* Item::dye_powder;
Item* Item::bone;
Item* Item::sugar;
Item* Item::cake;
Item* Item::bed;
Item* Item::shears;
Item* Item::melon;
Item* Item::seeds_pumpkin;
Item* Item::seeds_melon;
Item* Item::beef_raw;
Item* Item::beef_cooked;
Item* Item::chicken_raw;
Item* Item::chicken_cooked;
Item* Item::mobPlacer;
Item* Item::carrot;
Item* Item::potato;
Item* Item::potatoBaked;
Item* Item::pumpkinPie;
Item* Item::netherbrick;
Item* Item::netherQuartz;
Item* Item::camera;
Item* Item::beetroot;
Item* Item::seeds_beetroot;
Item* Item::beetrootSoup;

Item::Tier Item::Tier::WOOD(0, 59, 2.0f, 0);
Item::Tier Item::Tier::STONE(1, 131, 4.0f, 1);
Item::Tier Item::Tier::IRON(2, 250, 6.0f, 2);
Item::Tier Item::Tier::DIAMOND(3, 1561, 8.0f, 3);
Item::Tier Item::Tier::GOLD(0, 32, 12.0f, 0);

void Item::initItems(){
	Item::shovel_iron = new ShovelItem(0, &Item::Tier::IRON);
	Item::pickAxe_iron = new PickaxeItem(1, &Item::Tier::IRON);
	Item::hatchet_iron = new HatchetItem(2, &Item::Tier::IRON);
	//TODO Item::flintAndSteel;
	//TODO Item::apple;
	//TODO Item::bow;
	//TODO Item::arrow;
	//TODO Item::coal;
	//TODO Item::diamond;
	//TODO Item::ironIngot;
	//TODO Item::goldIngot;
	//TODO Item::sword_iron;
	//TODO Item::sword_wood;
	Item::shovel_wood = new ShovelItem(13, &Item::Tier::WOOD);
	Item::pickAxe_wood = new PickaxeItem(14, &Item::Tier::WOOD);
	Item::hatchet_wood = new HatchetItem(15, &Item::Tier::WOOD);
	//TODO Item::sword_stone;
	Item::shovel_stone = new ShovelItem(17, &Item::Tier::STONE);
	Item::pickAxe_stone = new PickaxeItem(18, &Item::Tier::STONE);
	Item::hatchet_stone = new HatchetItem(19, &Item::Tier::STONE);
	//TODO Item::sword_diamond;
	Item::shovel_diamond = new ShovelItem(21, &Item::Tier::DIAMOND);
	Item::pickAxe_diamond = new PickaxeItem(22, &Item::Tier::DIAMOND);
	Item::hatchet_diamond = new HatchetItem(23, &Item::Tier::DIAMOND);
	//TODO Item::stick;
	//TODO Item::bowl;
	//TODO Item::mushroomStew;
	//TODO Item::sword_gold;
	Item::shovel_gold = new ShovelItem(28, &Item::Tier::GOLD);
	Item::pickAxe_gold = new PickaxeItem(29, &Item::Tier::GOLD);
	Item::hatchet_gold = new HatchetItem(30, &Item::Tier::GOLD);
	//TODO Item::string;
	//TODO Item::feather;
	//TODO Item::sulphur;
	//TODO Item::hoe_wood;
	//TODO Item::hoe_stone;
	//TODO Item::hoe_iron;
	//TODO Item::hoe_diamond;
	//TODO Item::hoe_gold;
	//TODO Item::seeds_wheat;
	//TODO Item::wheat;
	//TODO Item::bread;
	//TODO Item::helmet_cloth;
	//TODO Item::chestplate_cloth;
	//TODO Item::leggings_cloth;
	//TODO Item::boots_cloth;
	//TODO Item::helmet_chain;
	//TODO Item::chestplate_chain;
	//TODO Item::leggings_chain;
	//TODO Item::boots_chain;
	//TODO Item::helmet_iron;
	//TODO Item::chestplate_iron;
	//TODO Item::leggings_iron;
	//TODO Item::boots_iron;
	//TODO Item::helmet_diamond;
	//TODO Item::chestplate_diamond;
	//TODO Item::leggings_diamond;
	//TODO Item::boots_diamond;
	//TODO Item::helmet_gold;
	//TODO Item::chestplate_gold;
	//TODO Item::leggings_gold;
	//TODO Item::boots_gold;
	//TODO Item::flint;
	//TODO Item::porkChop_raw;
	//TODO Item::porkChop_cooked;
	//TODO Item::painting;
	//TODO Item::sign;
	//TODO Item::door_wood;
	//TODO Item::bucket;
	//TODO Item::minecart;
	//TODO Item::saddle;
	//TODO Item::door_iron;
	//TODO Item::redStone;
	//TODO Item::snowBall;
	//TODO Item::leather;
	//TODO Item::brick;
	//TODO Item::clay;
	//TODO Item::reeds;
	//TODO Item::paper;
	//TODO Item::book;
	//TODO Item::slimeBall;
	//TODO Item::egg;
	//TODO Item::compass;
	//TODO Item::clock;
	//TODO Item::yellowDust;
	//TODO Item::dye_powder;
	//TODO Item::bone;
	//TODO Item::sugar;
	//TODO Item::cake;
	//TODO Item::bed;
	//TODO Item::shears;
	//TODO Item::melon;
	//TODO Item::seeds_pumpkin;
	//TODO Item::seeds_melon;
	//TODO Item::beef_raw;
	//TODO Item::beef_cooked;
	//TODO Item::chicken_raw;
	//TODO Item::chicken_cooked;
	//TODO Item::mobPlacer;
	//TODO Item::carrot;
	//TODO Item::potato;
	//TODO Item::potatoBaked;
	//TODO Item::pumpkinPie;
	//TODO Item::netherbrick;
	//TODO Item::netherQuartz;
	//TODO Item::camera;
	//TODO Item::beetroot;
	//TODO Item::seeds_beetroot;
	//TODO Item::beetrootSoup;
}
