#include "../cs2.hpp"
#include "c_handle.hpp"

CBaseEntity* CHandle::get_base_entity() const {
    return cs2::interfaces::resource_system->entity_system->get_base_entity(m_index & 0x7fff);
}
