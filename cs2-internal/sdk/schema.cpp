#include "../sdk/interfaces.hpp"
#include "schema.hpp"

void schema::initialize() {
	auto type_scope = interfaces::schema_system->FindTypeScopeForModule("client.dll");
	if (!type_scope)
		return;

	auto declared_class = type_scope->FindDeclaredClass("C_BaseEntity");
	if (!declared_class)
		return;


}
