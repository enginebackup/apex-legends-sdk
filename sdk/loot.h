#pragma once

class c_loot {
public:
	enum class type
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

	typedef struct
	{
		std::string name;
		type type;
	}info, * pinfo;

	std::map<int, info> hash;

	void add(int id, std::string name, type type)
	{
		info hs;
		hs.name = name;
		hs.type = type;
		hash[id] = hs;
	}

	void init()
	{
		add(0, _("deathbox"), type::deathbox);

		add(182, _("special accelerator"), type::survival);
		add(280, _("heat shield"), type::survival);
		add(281, _("mobile revival beacon"), type::survival);
		add(284, _("evacuation tower"), type::survival);

		add(188, _("helmet 1"), type::survival);
		add(189, _("helmet 2"), type::survival);
		add(190, _("helmet 3"), type::survival);
		add(191, _("helmet 4"), type::survival);

		add(193, _("body shield 1"), type::survival);
		add(194, _("body shield 2"), type::survival);
		add(195, _("body shield 3"), type::survival);
		add(196, _("body shield 4"), type::survival);

		add(198, _("evo shield 1"), type::survival);
		add(199, _("evo shield 2"), type::survival);
		add(200, _("evo shield 3"), type::survival);
		add(201, _("evo shield 4"), type::survival);

		add(207, _("backpack 1"), type::survival);
		add(208, _("backpack 2"), type::survival);
		add(209, _("backpack 3"), type::survival);
		add(210, _("backpack 4"), type::survival);

		add(203, _("knockout shield 1"), type::survival);
		add(204, _("knockout shield 2"), type::survival);
		add(205, _("knockout shield 3"), type::survival);
		add(206, _("knockout shield 4"), type::survival);

		add(240, _("treasure pack"), type::survival);

		add(184, _("medkit"), type::medic);
		add(185, _("syringe"), type::medic);
		add(183, _("phoenix kit"), type::medic);
		add(186, _("shield battery"), type::medic);
		add(187, _("shield cell"), type::medic);

		add(212, _("thermite grenade"), type::grenade);
		add(213, _("frag grenade"), type::grenade);
		add(214, _("arc star"), type::grenade);

		add(1, _("kraber"), type::weapon);
		add(2, _("mastiff"), type::weapon);
		add(7, _("lstar"), type::weapon);
		add(12, _("gold lstar"), type::weapon);
		add(13, _("havoc rifle"), type::weapon);
		add(17, _("gold havoc rifle"), type::weapon);
		add(18, _("devotion"), type::weapon);
		add(23, _("triple take"), type::weapon);
		add(28, _("flatline"), type::weapon);
		add(33, _("hemlock"), type::weapon);
		add(106, _("wingman"), type::weapon);
		add(55, _("prowler"), type::weapon);
		add(60, _("volt"), type::weapon);
		add(111, _("p2020"), type::weapon);
		add(116, _("re45"), type::weapon);
		add(44, _("alternator"), type::weapon);
		add(49, _("r99"), type::weapon);
		add(80, _("r301"), type::weapon);
		add(75, _("spitfire"), type::weapon);
		add(39, _("g7 scout"), type::weapon);
		add(95, _("mozambique"), type::weapon);
		add(85, _("eva8 auto"), type::weapon);
		add(90, _("peacekeeper"), type::weapon);
		add(65, _("longbow"), type::weapon);
		add(70, _("charge rifle"), type::weapon);
		add(122, _("sentinel"), type::weapon);
		add(127, _("bocek"), type::weapon);
		add(135, _("nemesis"), type::weapon);
		add(129, _("30-30 rifle"), type::weapon);
		add(146, _("rampage"), type::weapon);
		add(151, _("c.a.r"), type::weapon);
		add(211, _("knife"), type::weapon);

		add(140, _("light ammo"), type::light_ammo);
		add(141, _("energy ammo"), type::energy_ammo);
		add(142, _("shotgun ammo"), type::shotgun_ammo);
		add(143, _("heavy ammo"), type::heavy_ammo);
		add(144, _("sniper ammo"), type::sniper_ammo);

		add(216, _("2x scope"), type::scope);
		add(218, _("1x2x scope"), type::scope);
		add(215, _("1x scope"), type::scope);
		add(217, _("1x holo scope"), type::scope);

		add(220, _("3x scope"), type::scope);
		add(221, _("2x4x scope"), type::scope);
		add(219, _("1x digital scope"), type::scope);

		add(222, _("6x scope"), type::scope);
		add(223, _("4x8x scope"), type::scope);
		add(224, _("4x10x digital scope"), type::scope);

		add(229, _("laser scope 1"), type::scope);
		add(230, _("laser scope 2"), type::scope);
		add(231, _("laser scope 3"), type::scope);

		add(225, _("barrel stabilizer 1"), type::modification);
		add(226, _("barrel stabilizer 2"), type::modification);
		add(227, _("barrel stabilizer 3"), type::modification);

		add(252, _("standard stock 1"), type::modification);
		add(253, _("standard stock 2"), type::modification);
		add(254, _("standard stock 3"), type::modification);

		add(255, _("sniper stock 1"), type::modification);
		add(256, _("sniper stock 2"), type::modification);
		add(257, _("sniper stock 3"), type::modification);

		add(232, _("light magazine 1"), type::modification);
		add(233, _("light magazine 2"), type::modification);
		add(234, _("light magazine 3"), type::modification);
		add(235, _("light magazine 4"), type::modification);

		add(236, _("heavy magazine 1"), type::modification);
		add(237, _("heavy magazine 2"), type::modification);
		add(238, _("heavy magazine 3"), type::modification);
		add(239, _("heavy magazine 4"), type::modification);

		add(244, _("sniper magazine 1"), type::modification);
		add(245, _("sniper magazine 2"), type::modification);
		add(246, _("sniper magazine 3"), type::modification);
		add(247, _("sniper magazine 4"), type::modification);

		add(240, _("energy magazine 1"), type::modification);
		add(241, _("energy magazine 2"), type::modification);
		add(242, _("energy magazine 3"), type::modification);
		add(243, _("energy magazine 4"), type::modification);

		add(248, _("shotgun bolt 1"), type::modification);
		add(249, _("shotgun bolt 2"), type::modification);
		add(250, _("shotgun bolt 3"), type::modification);
		add(251, _("shotgun bolt 4"), type::modification);

		add(260, _("skull slicer"), type::modification);
		add(258, _("turbocharger"), type::modification);
		add(263, _("threshing ammo"), type::modification);
		add(262, _("penetrating ammo"), type::modification);
	}

	uint64_t ptr;
	int id;
	c_vec3 origin;
	float distance;

	bool valid() {
		if ((this->ptr != 0) && 
			(this->origin.x != 0))
			return true;

		return false;
	}

	void get_data(uint64_t pointer) {
		this->ptr = pointer;
		this->id = read<int>(ptr + offsets::m_customScriptInt);
		this->origin = read<c_vec3>(ptr + offsets::m_vecAbsOrigin);
	}
} loot;