#pragma once

class c_loot {
public:
	enum type
	{
		deathbox,
		survival,
		medic,
		grenade,
		weapon,
		light_ammo,
		energy_ammo,
		shotgun_ammo,
		heavy_ammo,
		sniper_ammo,
		scope,
		modification
	};

	enum rarity 
	{ 
		common,
		rare,
		epic,
		legendary,
		heirloom,
	};

	struct info
	{
		std::string name;
		type type;
		rarity rarity;
	};

    std::map<int, info> table = {
        {0, {_("deathbox"), type::deathbox}},
        {182, {_("special accelerator"), type::survival}},
        {280, {_("heat shield"), type::survival}},
        {281, {_("mobile revival beacon"), type::survival}},
        {284, {_("evacuation tower"), type::survival}},
        {188, {_("helmet 1"), type::survival}},
        {189, {_("helmet 2"), type::survival}},
        {190, {_("helmet 3"), type::survival}},
        {191, {_("helmet 4"), type::survival}},
        {193, {_("body shield 1"), type::survival}},
        {194, {_("body shield 2"), type::survival}},
        {195, {_("body shield 3"), type::survival}},
        {196, {_("body shield 4"), type::survival}},
        {198, {_("evo shield 1"), type::survival}},
        {199, {_("evo shield 2"), type::survival}},
        {200, {_("evo shield 3"), type::survival}},
        {201, {_("evo shield 4"), type::survival}},
        {207, {_("backpack 1"), type::survival}},
        {208, {_("backpack 2"), type::survival}},
        {209, {_("backpack 3"), type::survival}},
        {210, {_("backpack 4"), type::survival}},
        {203, {_("knockout shield 1"), type::survival}},
        {204, {_("knockout shield 2"), type::survival}},
        {205, {_("knockout shield 3"), type::survival}},
        {206, {_("knockout shield 4"), type::survival}},
        {240, {_("treasure pack"), type::survival}},
        {184, {_("medkit"), type::medic}},
        {185, {_("syringe"), type::medic}},
        {183, {_("phoenix kit"), type::medic}},
        {186, {_("shield battery"), type::medic}},
        {187, {_("shield cell"), type::medic}},
        {212, {_("thermite grenade"), type::grenade}},
        {213, {_("frag grenade"), type::grenade}},
        {214, {_("arc star"), type::grenade}},
        {1, {_("kraber"), type::weapon}},
        {2, {_("mastiff"), type::weapon}},
        {7, {_("lstar"), type::weapon}},
        {12, {_("gold lstar"), type::weapon}},
        {13, {_("havoc rifle"), type::weapon}},
        {17, {_("gold havoc rifle"), type::weapon}},
        {18, {_("devotion"), type::weapon}},
        {23, {_("triple take"), type::weapon}},
        {28, {_("flatline"), type::weapon}},
        {33, {_("hemlock"), type::weapon}},
        {106, {_("wingman"), type::weapon}},
        {55, {_("prowler"), type::weapon}},
        {60, {_("volt"), type::weapon}},
        {111, {_("p2020"), type::weapon}},
        {116, {_("re45"), type::weapon}},
        {44, {_("alternator"), type::weapon}},
        {49, {_("r99"), type::weapon}},
        {80, {_("r301"), type::weapon}},
        {75, {_("spitfire"), type::weapon}},
        {39, {_("g7 scout"), type::weapon}},
        {95, {_("mozambique"), type::weapon}},
        {85, {_("eva8 auto"), type::weapon}},
        {90, {_("peacekeeper"), type::weapon}},
        {65, {_("longbow"), type::weapon}},
        {70, {_("charge rifle"), type::weapon}},
        {122, {_("sentinel"), type::weapon}},
        {127, {_("bocek"), type::weapon}},
        {135, {_("nemesis"), type::weapon}},
        {129, {_("30-30 rifle"), type::weapon}},
        {146, {_("rampage"), type::weapon}},
        {151, {_("c.a.r"), type::weapon}},
        {211, {_("knife"), type::weapon}},
        {140, {_("light ammo"), type::light_ammo}},
        {141, {_("energy ammo"), type::energy_ammo}},
        {142, {_("shotgun ammo"), type::shotgun_ammo}},
        {143, {_("heavy ammo"), type::heavy_ammo}},
        {144, {_("sniper ammo"), type::sniper_ammo}},
        {216, {_("2x scope"), type::scope}},
        {218, {_("1x2x scope"), type::scope}},
        {215, {_("1x scope"), type::scope}},
        {217, {_("1x holo scope"), type::scope}},
        {220, {_("3x scope"), type::scope}},
        {221, {_("2x4x scope"), type::scope}},
        {219, {_("1x digital scope"), type::scope}},
        {222, {_("6x scope"), type::scope}},
        {223, {_("4x8x scope"), type::scope}},
        {224, {_("4x10x digital scope"), type::scope}},
        {229, {_("laser scope 1"), type::scope}},
        {230, {_("laser scope 2"), type::scope}},
        {231, {_("laser scope 3"), type::scope}},
        {225, {_("barrel stabilizer 1"), type::modification}},
        {226, {_("barrel stabilizer 2"), type::modification}},
        {227, {_("barrel stabilizer 3"), type::modification}},
        {252, {_("standard stock 1"), type::modification}},
        {253, {_("standard stock 2"), type::modification}},
        {254, {_("standard stock 3"), type::modification}},
        {255, {_("sniper stock 1"), type::modification}},
        {256, {_("sniper stock 2"), type::modification}},
        {257, {_("sniper stock 3"), type::modification}},
        {232, {_("light magazine 1"), type::modification}},
        {233, {_("light magazine 2"), type::modification}},
        {234, {_("light magazine 3"), type::modification}},
        {235, {_("light magazine 4"), type::modification}},
        {236, {_("heavy magazine 1"), type::modification}},
        {237, {_("heavy magazine 2"), type::modification}},
        {238, {_("heavy magazine 3"), type::modification}},
        {239, {_("heavy magazine 4"), type::modification}},
        {244, {_("sniper magazine 1"), type::modification}},
        {245, {_("sniper magazine 2"), type::modification}},
        {246, {_("sniper magazine 3"), type::modification}},
        {247, {_("sniper magazine 4"), type::modification}},
        {240, {_("energy magazine 1"), type::modification}},
        {241, {_("energy magazine 2"), type::modification}},
        {242, {_("energy magazine 3"), type::modification}},
        {243, {_("energy magazine 4"), type::modification}},
        {248, {_("shotgun bolt 1"), type::modification}},
        {249, {_("shotgun bolt 2"), type::modification}},
        {250, {_("shotgun bolt 3"), type::modification}},
        {251, {_("shotgun bolt 4"), type::modification}},
        {260, {_("skull slicer"), type::modification}},
        {258, {_("turbocharger"), type::modification}},
        {263, {_("threshing ammo"), type::modification}},
        {262, {_("penetrating ammo"), type::modification}},
    };

	uint64_t ptr;
	int id;
	c_vec3 origin;
	float distance;

	bool valid() {
		return 
            this->ptr != 0 &&
            this->origin.x != 0;
	}

	void get_data(uint64_t pointer) {
		this->ptr = pointer;
		this->id = read<int>(ptr + offsets::m_customScriptInt);
		this->origin = read<c_vec3>(ptr + offsets::m_vecAbsOrigin);
	}
} loot;