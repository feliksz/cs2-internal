#include "../interfaces.hpp"
#include "CBaseEntity.hpp"
#include "CHandle.hpp"

CBaseEntity* CHandle::get_base_entity() {
    return interfaces::game_entity_system->GetBaseEntity(get_index());
}
