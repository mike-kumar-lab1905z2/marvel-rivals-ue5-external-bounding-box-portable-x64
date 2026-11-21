#include <windows.h>
#include <cstdint>
#include <atomic>

namespace runtime {
struct RenderConfig {
    uint32_t target_fps = 144;
    float fov_radius = 65.0f;
    float smooth_factor = 1.45f;
    bool draw_bounds = true;
};
static std::atomic<bool> g_running{true};
void PollHotkeys(bool& menu_open) noexcept {
    if (GetAsyncKeyState(VK_INSERT) & 1) menu_open = !menu_open;
    if (GetAsyncKeyState(VK_END) & 1) g_running.store(false, std::memory_order_relaxed);
}
} // namespace runtime

int main() {
    bool menu_open = true;
    while (runtime::g_running.load(std::memory_order_relaxed)) {
        runtime::PollHotkeys(menu_open);
        Sleep(6);
    }
    return 0;
}
