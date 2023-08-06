#pragma once
#include "../../util/memory.hpp"

struct SchemaClassFieldData_t {
    const char* m_name;
    char __pad0[0x8];
    i16 m_offset;
    char __pad1[0xE];
};


class SchemaClassInfoData_t {
public:
    const char* GetName() {
        return *(const char**)(u64(this) + 0x8);
    }

    i16 GetFieldsSize() {
        return *(i16*)(u64(this) + 0x1C);
    }

    SchemaClassFieldData_t* GetFields() {
        return *(SchemaClassFieldData_t**)(u64(this) + 0x28);
    }
};
class CSchemaSystemTypeScope {
public:   
    SchemaClassInfoData_t* FindDeclaredClass(const char* class_name) {
        return memory::call_vfunc<SchemaClassInfoData_t*>(this, 2, class_name);
    }
};

class ISchemaSystem {
public:
    CSchemaSystemTypeScope* FindTypeScopeForModule(const char* module) {
        return memory::call_vfunc<CSchemaSystemTypeScope*>(this, 13, module);
    }
};