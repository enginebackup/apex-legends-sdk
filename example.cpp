#include "sdk/driver.h"
#include "sdk/offsets.h"
#include "sdk/math.h"
#include "sdk/player.h"
#include "sdk/loot.h"
#include "sdk/sdk.h"

void render_esp() {
	sdk.update_data();
	if (sdk.is_in_game()) {
		if (vars.compensate_recoil)
			sdk.control_recoil(vars.recoil_compensation);

		if (vars.loot_enable) {
			for (c_loot& loot : sdk.loots) {
				if (loot.distance > vars.loot_max_distance)
					continue;

				c_vec3 originLoc = loot.origin;
				c_vec3 originScr;

				if (sdk.world_to_screen(originLoc, originScr))
				{
					if (vars.loot_id)
						draw.text(std::to_string(loot.id), ImVec2(int(originScr.x), int(originScr.y + 11)), ImGui::GetFontSize(), vars.loot_id_color.c(), nullptr, false, true);

					if (loot.hash.count(loot.id))
					{
						std::string loot_text;
						loot_text = loot.hash[loot.id].name;
						if (vars.loot_distance)
							loot_text += _(" [") + std::to_string((int)loot.distance) + _("m]");

						if (vars.loot_deathbox && loot.hash[loot.id].type == loot.type::deathbox) {
							draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_deathbox_color.c(), nullptr, true, true);
						}

						if (vars.loot_survival && loot.hash[loot.id].type == loot.type::survival) {
							draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_survival_color.c(), nullptr, true, true);
						}

						if (vars.loot_medic && loot.hash[loot.id].type == loot.type::medic) {
							draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_medic_color.c(), nullptr, true, true);
						}

						if (vars.loot_grenade && loot.hash[loot.id].type == loot.type::grenade) {
							draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_grenade_color.c(), nullptr, true, true);
						}

						if (vars.loot_weapon && loot.hash[loot.id].type == loot.type::weapon) {
							draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_weapon_color.c(), nullptr, true, true);
						}

						if (vars.loot_ammo) {
							if (vars.loot_light_ammo && loot.hash[loot.id].type == loot.type::light_ammo) {
								draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_light_ammo_color.c(), nullptr, true, true);
							}

							if (vars.loot_energy_ammo && loot.hash[loot.id].type == loot.type::energy_ammo) {
								draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_energy_ammo_color.c(), nullptr, true, true);
							}

							if (vars.loot_shotgun_ammo && loot.hash[loot.id].type == loot.type::shotgun_ammo) {
								draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_shotgun_ammo_color.c(), nullptr, true, true);
							}

							if (vars.loot_heavy_ammo && loot.hash[loot.id].type == loot.type::heavy_ammo) {
								draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_heavy_ammo_color.c(), nullptr, true, true);
							}

							if (vars.loot_sniper_ammo && loot.hash[loot.id].type == loot.type::sniper_ammo) {
								draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_sniper_ammo_color.c(), nullptr, true, true);
							}
						}

						if (vars.loot_scope && loot.hash[loot.id].type == loot.type::scope) {
							draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_scope_color.c(), nullptr, true, true);
						}

						if (vars.loot_modification && loot.hash[loot.id].type == loot.type::modification) {
							draw.text(loot_text, ImVec2(int(originScr.x), int(originScr.y)), ImGui::GetFontSize(), vars.loot_modification_color.c(), nullptr, true, true);
						}
					}
				}
			}
		}

		if (vars.player_enable) {
			for (c_player& player : sdk.players) {
				if (player.distance > vars.player_max_distance)
					continue;

				if (player.team == sdk.lplayer.team && !vars.player_team)
					continue;

				auto box = sdk.create_box(player.origin, player.min, player.max);

				if (box.x && box.y && box.w && box.h) {
					if (vars.player_box) {
						draw.box(ImVec2(box.x, box.y), ImVec2(box.w, box.h), player.knocked ? ImColor(vars.player_box_knocked_color.c()) : ImColor(vars.player_box_color.c()));
					}
					if (vars.player_health) {
						draw.health_bar(ImVec2(box.x - 4, box.y), ImVec2(4, box.h), 2, player.hp, player.hp_max, player.shield, player.shield_max, vars.player_health_gradient, vars.player_health_fullhp_color.c(), vars.player_health_lowhp_color.c(), vars.player_health_fullar_color.c(), vars.player_health_lowar_color.c());
					}
					std::string text;
					if (vars.player_name || vars.player_distance) {
						if (vars.player_name)
							text += player.name;

						if (vars.player_distance)
							text += _(" [") + std::to_string((int)player.distance) + _("m]");

						//char buffer[256];
						//sprintf_s(buffer, " ptr: %llx", static_cast<unsigned long long>(player.ptr));

						//text += buffer;

						ImVec2 text_pos = { box.x + (box.w / 2) - (ImGui::CalcTextSize(text.c_str()).x / 2), float(box.y - ImGui::CalcTextSize(text.c_str()).y - 4) };
						draw.text(text.c_str(), ImVec2(int(text_pos.x), int(text_pos.y)), ImGui::GetFontSize(), ImColor(vars.player_name_color.c()), nullptr, false, true);
					}
					if (vars.player_weapon) {
						std::string weapon = player.weapon_name;
						ImVec2 text_pos2 = { box.x + (box.w / 2) - (ImGui::CalcTextSize(weapon.c_str()).x / 2), float(box.y + box.h) };
						draw.text(weapon.c_str(), ImVec2(int(text_pos2.x), int(text_pos2.y)), ImGui::GetFontSize(), ImColor(vars.player_weapon_color.c()), nullptr, false, true);
					}
				}
			}
		}
	}
}

int main() {
	std::thread([&]()
	{ 
		sdk.cache_thread();
	}).detach();

	while (msg.message != WM_QUIT)
	{
		render_esp();
	}

	return 0;
}