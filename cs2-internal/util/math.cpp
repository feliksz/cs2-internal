#include "../globals.hpp"
#include "math.hpp"

bool math::world_to_screen(const v3& in, v2i& out) {
    auto z = globals::view_matrix[3][0] * in.x + globals::view_matrix[3][1] * in.y +
        globals::view_matrix[3][2] * in.z + globals::view_matrix[3][3];

    if (z < 0.001f) 
        return false;

    out = { (i32)(ImGui::GetIO().DisplaySize.x * 0.5f), (i32)(ImGui::GetIO().DisplaySize.y * 0.5f) };
    out.x *= 1.0f + (globals::view_matrix[0][0] * in.x + globals::view_matrix[0][1] * in.y +
        globals::view_matrix[0][2] * in.z + globals::view_matrix[0][3]) /
        z;
    out.y *= 1.0f - (globals::view_matrix[1][0] * in.x + globals::view_matrix[1][1] * in.y +
        globals::view_matrix[1][2] * in.z + globals::view_matrix[1][3]) /
        z;

    out = { (i32)out.x, (i32)out.y };
    return true;
}
