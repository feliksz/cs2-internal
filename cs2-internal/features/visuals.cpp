#include "../menu/config.hpp"
#include "../sdk/entity/CBasePlayerPawn.hpp"
#include "../sdk/entity/CCSPlayerController.hpp"
#include "../sdk/entity/CWeaponCSBase.hpp"
#include "../sdk/interfaces.hpp"
#include "../util/render.hpp"
#include "../vendor/fnv1a.hpp"
#include "features.hpp"

#include <format>

static void draw_entity_box(const bbox_t& bbox, const col_t& col) {
	render::rect(bbox.x - 1, bbox.y - 1, bbox.w + 2, bbox.h + 2, col_t::black(100));
	render::rect(bbox.x, bbox.y, bbox.w, bbox.h, col);
	render::rect(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, col_t::black(100));
}


void draw_player_esp(CCSPlayerController* controller, const bbox_t& bbox) {
	auto player = controller->m_hPawn().get<CBasePlayerPawn>();
	if (BOOL_GET("visuals.player_esp.box")) {
		draw_entity_box(bbox, { 255, 0, 0, 255 });
	}
	if (BOOL_GET("visuals.player_esp.name")) {
		auto text_size = render::get_text_size(controller->m_sSanitizedPlayerName());
		render::text(bbox.x + (bbox.w / 2) - (text_size.x / 2), bbox.y - text_size.y - 4, controller->m_sSanitizedPlayerName(), col_t::white());
	}
	if (BOOL_GET("visuals.player_esp.health")) {
		auto healthbar_pos = v2i{ (i32)bbox.x - 6, (i32)bbox.y };
		auto healthbar_size = v2i{ 2, (i32)bbox.h };
		auto h = i32(healthbar_size.y * f32(controller->m_iPawnHealth() / 100.f));
		render::filled_rect(healthbar_pos, healthbar_size, col_t::black(80));
		render::filled_rect(v2i{ healthbar_pos.x, healthbar_pos.y + healthbar_size.y - h }, v2i{ healthbar_size.x, h }, col_t(0, 255, 0, 255));
		render::rect(healthbar_pos.x - 1, healthbar_pos.y - 1, healthbar_size.x + 2, healthbar_size.y + 2, col_t::black(120));
		render::rect(healthbar_pos.x + 1, healthbar_pos.y + 1, healthbar_size.x - 2, healthbar_size.y - 2, col_t::black(120));

	}
	if (BOOL_GET("visuals.player_esp.weapon")) {
		auto weapon = player->m_pWeaponServices()->m_hActiveWeapon().get<CWeaponCSBase>();
		if (weapon) {
			auto name = weapon->m_AttributeManager().m_Item().GetStaticData()->GetSimpleWeaponName();
			auto text_size = render::get_text_size(name);
			render::text(bbox.x + (bbox.w / 2) - (text_size.x / 2), bbox.y + bbox.h, name, col_t::white());
		}
	}
}

void draw_weapon_esp(CWeaponCSBase* weapon, const bbox_t& bbox) {
	if (BOOL_GET("visuals.weapon_esp.box")) {
		draw_entity_box(bbox, { 255, 255, 0, 255 });
	}
	if (BOOL_GET("visuals.weapon_esp.name")) {
		auto weapon_name = weapon->m_AttributeManager().m_Item().GetStaticData()->GetSimpleWeaponName();
		auto text_size = render::get_text_size(weapon_name);
		render::text(bbox.x + (bbox.w / 2) - (text_size.x / 2), bbox.y + bbox.h, weapon_name, col_t::white());
	}
	if (BOOL_GET("visuals.weapon_esp.ammo")) {
		auto clip1 = weapon->m_iClip1();
		if (clip1 >= 0) {
			auto ammo_text = std::to_string(weapon->m_iClip1());
			auto text_size = render::get_text_size(ammo_text.c_str());
			render::text(bbox.x + (bbox.w / 2) - (text_size.x / 2), bbox.y + bbox.h + 16, ammo_text.data(), col_t::white());
		}
	}
}

void draw_projectile_esp(CBaseEntity* entity, const bbox_t& bbox) {
	draw_entity_box(bbox, col_t{ 255, 0, 255, 255 });
}
void draw_spectators() {
	auto y = 0u;
	auto local_player = interfaces::game_entity_system->GetLocalPlayerController();
	for (auto i = 0; i < interfaces::game_entity_system->GetHighestEntityIndex(); i++) {
		auto entity = interfaces::game_entity_system->GetBaseEntity(i);
		if (!entity || !entity->IsBasePlayerController())
			continue;

		auto controller = (CCSPlayerController*)entity;
		auto pawn       = controller->m_hPawn().get<CBasePlayerPawn>();
		if (!pawn)
			continue;

		auto observer_service = pawn->m_pObserverServices();
		auto observer_target  = observer_service->m_hObserverTarget().get<CCSObserverPawn>();
		if (!observer_target)
			continue;

		auto target_controller = observer_target->m_hController().get<CCSPlayerController>();
		if (!target_controller)
			continue;

		if (BOOL_GET("visuals.other.spectators_only_local") && target_controller != local_player)
			continue;

		auto str = std::format(
			"{} -> {} ({})",
			controller->m_sSanitizedPlayerName(),
			target_controller->m_sSanitizedPlayerName(),
			observer_service->m_iObserverMode() == 2 ? "first-person" : "third-person"
		);

		render::text(10, 320 + y, str.data(), col_t(0, 0, 255, 255));
		y += render::get_text_size(str.data()).y + 2;
	}
}

void draw_entity_debug_info(CBaseEntity* entity) {
	auto bbox = bbox_t{};
	if (!entity->get_bounding_box(bbox))
		return;

	auto binding = entity->Schema_DynamicBinding();
	if (!binding)
		return;

	render::text(bbox.x, bbox.y + bbox.h, binding->GetName(), col_t::white());
}

void features::visuals::draw() {
	auto local_player = interfaces::game_entity_system->GetLocalPlayerController();

	for (auto i = 0; i < interfaces::game_entity_system->GetHighestEntityIndex(); i++) {
		auto entity = interfaces::game_entity_system->GetBaseEntity(i);
		if (!entity)
			continue;

		if (entity->IsBasePlayerController()) {
			auto controller = (CCSPlayerController*) entity;
			if (!controller->IsAlive())
				continue;

			if (controller->m_bIsLocalPlayerController())
				continue;

			if (BOOL_GET("visuals.player_esp.ignore_allies") && controller->m_iTeamNum() == local_player->m_iTeamNum())
				continue;

			auto player = controller->m_hPawn().get<CBasePlayerPawn>();

			auto bbox = bbox_t{};
			if (!player->get_bounding_box(bbox, false))
				continue;

			draw_player_esp(controller, bbox);
		}
		else if (entity->IsBaseWeaponController()) {
			auto weapon = (CWeaponCSBase*) entity;
			if (!weapon)
				continue;

			if (weapon->m_hOwnerEntity().is_valid())
				continue;

			auto bbox = bbox_t{};
			if (!weapon->get_bounding_box(bbox, true))
				continue;

			draw_weapon_esp(weapon, bbox);
		}
		else {
			auto class_hash = HASH(entity->Schema_DynamicBinding()->GetName());
			switch (class_hash) {
			case HASH("C_BaseCSGrenadeProjectile"): // HE Grenade/Flashbang
			case HASH("C_MolotovProjectile"): // Molotov
			case HASH("C_SmokeGrenadeProjectile"): // Smoke
			case HASH("C_DecoyProjectile"): // Decoy
				auto bbox = bbox_t{};
				if (!entity->get_bounding_box(bbox, false))
					continue;

				draw_projectile_esp(entity, bbox);
				break;
			default:
				break;
			}
		}

		// debug info
		if (BOOL_GET("misc.draw_debug_info")) {
			draw_entity_debug_info(entity);
		}
	}

	if (BOOL_GET("visuals.other.spectators")) {
		draw_spectators();
	}
}