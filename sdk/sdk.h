#pragma once

#include "driver.h"
#include "math.h"
#include "offsets.h"
#include "../core/utils.h"

class c_sdk {
private:
	uint64_t lplayer_ptr;
	std::vector<uint64_t> player_cache;
	std::vector<uint64_t> loot_cache;

	struct s_matrix
	{
		float matrix[16];
	};

	s_matrix get_view_matrix() {
		auto view_render = read<uint64_t>(base + offsets::ViewRender);
		if (!view_render)
			return s_matrix{};

		auto pview_matrix = read<uint64_t>(view_render + offsets::ViewMatrix);
		if (pview_matrix != 0)
			return read<s_matrix>(pview_matrix);

		return s_matrix{};
	}
public:
	bool is_in_game()
	{
		std::string ret = read_str(base + offsets::LevelName, 32);
		return !ret.empty() && ret != _("mp_lobby");
	}

	std::string get_entity_signifier(uint64_t ptr) {
		if (!ptr)
			return "";

		auto signifier_ptr = read<uint64_t>(ptr + offsets::m_iSignifierName);
		if (!signifier_ptr)
			return "";

		auto signifier = read_str(signifier_ptr, 64);
		if (signifier.empty())
			return "";

		return signifier;
	}

	uint64_t get_viewmodel_entity(uint64_t ptr) {
		if (!ptr)
			return 0;

		auto active_weapon_id = read<uint64_t>(ptr + offsets::m_hViewModels) & 0xffff;
		auto current_weapon = read<uint64_t>(base + offsets::cl_entitylist + (active_weapon_id << 5));
		if (!current_weapon)
			return 0;

		return current_weapon;
	}

	uint64_t get_weapon_entity(uint64_t ptr) {
		if (!ptr)
			return 0;

		auto weapon_pointer = read<uint64_t>(ptr + offsets::m_latestPrimaryWeapons) & 0xffff;
		auto weapon_entity = read<uint64_t>(base + offsets::cl_entitylist + (weapon_pointer << 5));
		if (weapon_entity <= 0)
			return 0;

		return weapon_entity;
	}

	void set_skin(uint64_t ptr, int id) {
		if (!ptr)
			return;

		write<int>(ptr + offsets::m_nSkin, id);
	}

	void control_recoil(float compensation) {
		static c_vec3 last_punch_angle;

		auto view_angles = read<c_vec3>(sdk.lplayer.ptr + offsets::viewangles);
		auto punch_angles = read<c_vec3>(sdk.lplayer.ptr + offsets::aimpunch) * (compensation / 100.0f);

		view_angles += last_punch_angle;
		view_angles -= punch_angles;
		view_angles.normalize();

		write<c_vec3>(sdk.lplayer.ptr + offsets::viewangles, view_angles);
		last_punch_angle = punch_angles;
	}

	void set_highlight(uint64_t entity, int contextID, int settingIndex, int visibilityType, char insideValue, char outlineValue, char outlineSize, std::array<float, 3> highlightParameter)
	{
		if (!entity)
			return;

		int currentContextID = read<int>(entity + offsets::HighlightCurrentContextId);
		int currentSettingIndex = read<int>(entity + offsets::HighlightServerActiveStates + contextID);
		int currentVisibilityType = read<int>(entity + offsets::HighlightVisibilityType);

		if (currentContextID != contextID)
			write<int>(entity + offsets::HighlightCurrentContextId, contextID);

		if (currentSettingIndex != settingIndex)
			write<int>(entity + offsets::HighlightServerActiveStates + contextID, settingIndex);

		if (currentVisibilityType != visibilityType)
			write<int>(entity + offsets::HighlightVisibilityType, visibilityType);

		uint64_t highlightSetting = read<uint64_t>(base + offsets::HighlightSettings);

		std::array<unsigned char, 4> highlightFunctionBits = {
			insideValue,    // (0 - 14)
			outlineValue,   // (? - ?)
			outlineSize,    // (0 - 255)
			64              // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7)
		};

		write<std::array<unsigned char, 4>>(highlightSetting + 0x28 * settingIndex + 4, highlightFunctionBits);
		write<std::array<float, 3>>(highlightSetting + 0x28 * settingIndex + 8, highlightParameter);
	}

	void cache_thread() {
		while (true) {
			if (vars.destroy)
				return;

			if (sdk.is_in_game()) {
				lplayer_ptr = read<uint64_t>(base + offsets::LocalPlayer);

				std::vector<uint64_t> player_temp;
				std::vector<uint64_t> loot_temp;
				for (int i = 0; i < 15000; i++)
				{
					if (vars.destroy)
						return;

					uint64_t entity = read<uint64_t>(base + offsets::cl_entitylist + (i * 0x20));
					if (!entity)
						continue;

					std::string signifier = sdk.get_entity_signifier(entity);
					if (signifier.empty())
						continue;

					if (signifier == _("player")) {
						if (entity == lplayer_ptr)
							continue;

						player_temp.push_back(entity);
					}

					if (signifier == _("npc_dummie"))
						player_temp.push_back(entity);

					if (signifier == _("prop_death_box") || signifier == _("prop_survival"))
					{
						int loot_id = read<uint64_t>(entity + offsets::m_customScriptInt);
						if (loot_id > 293)
							continue;

						loot_temp.push_back(entity);
					}

					Sleep(1);
				}

				player_cache = player_temp;
				loot_cache = loot_temp;
			}
			else {
				player_cache.clear();
				loot_cache.clear();
			}

			Sleep(10);
		}
	}

	bool world_to_screen(const c_vec3& in, c_vec3& out) {
		auto m_vmatrix = get_view_matrix().matrix;
		float w = m_vmatrix[12] * in.x + m_vmatrix[13] * in.y + m_vmatrix[14] * in.z + m_vmatrix[15];
		if (w < 0.01f)
			return false;

		out.x = m_vmatrix[0] * in.x + m_vmatrix[1] * in.y + m_vmatrix[2] * in.z + m_vmatrix[3];
		out.y = m_vmatrix[4] * in.x + m_vmatrix[5] * in.y + m_vmatrix[6] * in.z + m_vmatrix[7];

		float invw = 1.0f / w;
		out.x *= invw;
		out.y *= invw;

		float x = overlay.x / 2;
		float y = overlay.y / 2;

		x += 0.5f * out.x * overlay.x + 0.5f;
		y -= 0.5f * out.y * overlay.y + 0.5f;

		out.x = x;
		out.y = y;

		return true;
	}

	c_vec3 world_to_screen(const c_vec3 pos)
	{
		c_vec3 screen_pos;
		world_to_screen(pos, screen_pos);
		return screen_pos;
	}

	struct box_t {
		box_t() = default;
		box_t(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
		int x, y, w, h;

		bool valid() const {
			return x != 0 && y != 0 && w != 0 && h != 0;
		}
	};

	box_t create_box(const c_vec3& origin, const c_vec3& mins, const c_vec3& maxs) {
		c_vec3 min{}, max{}, flb{}, brt{}, blb{}, frt{}, frb{}, brb{}, blt{}, flt{};

		min = mins + origin;
		max = maxs + origin;

		c_vec3 points[] = {
		  c_vec3(min.x, min.y, min.z),
		  c_vec3(min.x, max.y, min.z),
		  c_vec3(max.x, max.y, min.z),
		  c_vec3(max.x, min.y, min.z),
		  c_vec3(max.x, max.y, max.z),
		  c_vec3(min.x, max.y, max.z),
		  c_vec3(min.x, min.y, max.z),
		  c_vec3(max.x, min.y, max.z)
		};

		world_to_screen(points[3], flb);
		world_to_screen(points[5], brt);
		world_to_screen(points[0], blb);
		world_to_screen(points[4], frt);
		world_to_screen(points[2], frb);
		world_to_screen(points[1], brb);
		world_to_screen(points[6], blt);
		world_to_screen(points[7], flt);

		c_vec3 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
		int left, top, right, bottom;

		left = flb.x;
		top = flb.y;
		right = flb.x;
		bottom = flb.y;

		if (left || top || right || bottom) {
			for (int i = 1; i < 8; ++i) {
				if (left > arr[i].x)
					left = arr[i].x;
				if (bottom < arr[i].y)
					bottom = arr[i].y;
				if (right < arr[i].x)
					right = arr[i].x;
				if (top > arr[i].y)
					top = arr[i].y;
			}
			return box_t{ left, top, right - left, bottom - top };
		}

		return box_t{ 0, 0, 0, 0 };
	}

	c_player lplayer;
	std::vector<c_player> players;
	std::vector<c_loot> loots;
	c_player closest_visible_enemy;
	c_player closest_crosshair_enemy;

	void update_data() {
		this->lplayer.get_data(lplayer_ptr);

		std::vector<c_player> players_temp;
		for (int i = 0; i < player_cache.size(); i++) {
			player.get_data(player_cache[i]);
			if (player.ptr && player.valid()) {
				player.distance = utils::calc_distance(this->lplayer.origin, player.origin);
				players_temp.push_back(player);
			}
		}
		this->players = players_temp;

		std::vector<c_loot> loots_temp;
		for (int i = 0; i < loot_cache.size(); i++) {
			loot.get_data(loot_cache[i]);
			if (loot.ptr && loot.valid()) {
				loot.distance = utils::calc_distance(this->lplayer.origin, loot.origin);
				loots_temp.push_back(loot);
			}
		}
		this->loots = loots_temp;

		float closest_crosshair = FLT_MAX;
		for (int i = 0; i < this->players.size(); i++) {
			if (!this->lplayer.knocked) {
				c_vec3 out;
				if (world_to_screen(this->players[i].origin, out)) {
					float cross_dist = utils::get_cross_distance(out.x, out.y, overlay.x / 2, overlay.y / 2);
					if ((cross_dist < closest_crosshair)) {
						if (this->players[i].team != this->lplayer.team && this->players[i].distance < 125) {
							if (this->players[i].knocked) {
								if (vars.aimbot_knocked)
									closest_crosshair_enemy = this->players[i];
							}
							else {
								closest_crosshair_enemy = this->players[i];
							}
							closest_crosshair = cross_dist;
						}
					}
				}
			}
		}

		float closest_dist = FLT_MAX;
		for (int i = 0; i < this->players.size(); i++) {
			if ((this->players[i].distance < closest_dist)) {
				if (this->players[i].team != this->lplayer.team) {
					closest_visible_enemy = this->players[i];
					closest_dist = this->players[i].distance;
				}
			}
		}
	}

} sdk;