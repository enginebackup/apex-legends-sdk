#pragma once

class c_player {
public:
	std::string get_player_name(uint64_t ptr)
	{
		uint64_t name_index = read<uint64_t>(ptr + offsets::nameIndex);
		uint64_t name_ptr = read<uint64_t>(base + offsets::nameList + ((name_index - 1) << 4));
		std::string str = read_str(name_ptr, 64);

		if (str.empty())
			return _("npc");

		return str;
	}

	std::string get_weapon_name(uint64_t ptr)
	{
		uint64_t primary_weapons_latest = read<uint64_t>(ptr + offsets::m_latestPrimaryWeapons) & 0xFFFF;
		uint64_t primary_weapons_list = read<uint64_t>(base + offsets::cl_entitylist + (primary_weapons_latest * 0x20));
		int weapon_index = read<int>(primary_weapons_list + offsets::m_weaponNameIndex);
		switch (weapon_index)
		{
		case 0:
			return _("r301");
			break;
		case 2:
			return _("bocek");
			break;
		case 85:
			return _("havoc rifle");
			break;
		case 83:
			return _("devotion");
			break;
		case 92:
			return _("lstar");
			break;
		case 106:
			return _("triple take");
			break;
		case 109:
			return _("volt");
			break;
		case 112:
			return _("nemesis");
			break;
		case 87:
			return _("flatline");
			break;
		case 89:
			return _("hemlock");
			break;
		case 110:
			return _("30-30 rifle");
			break;
		case 20:
			return _("rampage");
			break;
		case 111:
			return _("c.a.r");
			break;
		case 104:
			return _("p2020");
			break;
		case 80:
			return _("re45");
			break;
		case 79:
			return _("alternator");
			break;
		case 103:
			return _("r99");
			break;
		case 105:
			return _("spitfire");
			break;
		case 88:
			return _("g7 scout");
			break;
		case 95:
			return _("mozambique");
			break;
		case 86:
			return _("eva8 auto");
			break;
		case 102:
			return _("peacekeeper");
			break;
		case 1:
			return _("sentinel");
			break;
		case 82:
			return _("charge rifle");
			break;
		case 84:
			return _("longbow");
			break;
		case 94:
			return _("mastiff");
			break;
		case 101:
			return _("prowler");
			break;
		case 108:
			return _("wingman");
			break;
		case 91:
			return _("kraber");
			break;
		case 158:
			return _("knife");
			break;
		}
		return "";
	}

	bool get_bone_pos(uint32_t bone_id, c_vec3& out)
	{
		uint64_t bone_array = read<uint64_t>(ptr + offsets::m_nForceBone);
		out.x = read<float>(bone_array + 0xCC + (bone_id * 0x30)) + origin.x;
		out.y = read<float>(bone_array + 0xDC + (bone_id * 0x30)) + origin.y;
		out.z = read<float>(bone_array + 0xEC + (bone_id * 0x30)) + origin.z;

		return true;
	}

	uint64_t ptr;
	int hp;
	int hp_max;
	int shield;
	int shield_max;
	int team;
	bool knocked;
	std::string name;
	std::string weapon_name;
	c_vec3 origin;
	c_vec3 head;
	float distance;
	c_vec3 min;
	c_vec3 max;

	bool valid() {
		if ((this->origin.x != 0) &&
			(this->team != 0) &&
			(this->hp > 0) &&
			(this->ptr != 0)) return true;

		return false;
	}

	void get_data(uint64_t pointer) {
		this->ptr = pointer;
		this->team = read<int>(ptr + offsets::m_iTeamNum);
		this->hp = read<int>(ptr + offsets::m_iHealth);
		this->hp_max = read<int>(ptr + offsets::m_iMaxHealth);
		this->shield = read<int>(ptr + offsets::m_shieldHealth);
		this->shield_max = read<int>(ptr + offsets::m_shieldHealthMax);
		this->knocked = read<int>(ptr + offsets::m_bleedoutState);
		this->name = player.get_player_name(ptr);
		this->weapon_name = player.get_weapon_name(ptr);
		this->origin = read<c_vec3>(ptr + offsets::m_vecAbsOrigin);
		get_bone_pos(bone_id::head, this->head);
		this->min = read<c_vec3>(ptr + offsets::vectorMin);
		this->max = read<c_vec3>(ptr + offsets::vectorMax);
	}
} player;