/*
** EPITECH PROJECT, 2023
** R-Type-epitech
** File description:
** Debug
*/

#ifdef DEBUG
    #ifndef DEBUG_HPP_
        #define DEBUG_HPP_
        #include <memory>
        #include <imgui.h>
        #include <imgui_internal.h>
        #include "Registry.hpp"
        #include "utils/DeltaTime.hpp"
        #include "Event.hpp"
        #include "utils/Utils.hpp"

namespace Debug
{
    static const ImVec2 DEBUG_MENU_DEFAULT_WINDOW_SIZE = ImVec2((float)500, (float)500);
    static const size_t DEFAULT_FPS_PLOT_TEXT_LENGTH = 32;
    static const size_t DEFAULT_FPS_PLOT_NB_VALUES = 90;
    static const double DEFAULT_FPS_PLOT_REFRESH_RATE = 60.0;
    static const ImVec2 DEFAULT_FPS_PLOT_SIZE = ImVec2(0, 80.0f);

    class DebugMenu
    {
      public:
        DebugMenu(
            GameEngine::EventManager &eventManager, GameEngine::Registry &registry, GameEngine::DeltaTime &deltaTime)
            : _eventManager(eventManager), _registry(registry), _deltaTime(deltaTime)
        {
        }
        ~DebugMenu() {}

        void draw()
        {
            ImGui::ShowDemoWindow();
            ImGui::SetNextWindowSize(DEBUG_MENU_DEFAULT_WINDOW_SIZE, ImGuiCond_FirstUseEver);
            ImGui::Begin("Debug Menu");
            if (ImGui::BeginTabBar("MainTabBar")) {
                if (ImGui::BeginTabItem("Game")) {
                    _showGameMenu();
                }
                if (ImGui::BeginTabItem("Registry")) {
                    _showRegistryMenu();
                }
                ImGui::EndTabBar();
            }
            ImGui::End();
        }

      private:
        GameEngine::EventManager &_eventManager;
        GameEngine::Registry &_registry;
        GameEngine::DeltaTime &_deltaTime;
        void _showGameMenu();
        void _showRegistryMenu();
        template <typename Component>
        void _showComponentList(SparseArray<Component> &components, int &currentComponent)
        {
            if (ImGui::BeginListBox("", ImVec2(ImGui::GetContentRegionAvail().x / 3.0f, 150))) {
                for (int i = 0; i < _registry._nbEntities; i++) {
                    if (!components[i])
                        continue;
                    const bool is_selected = (currentComponent == i);
                    if (ImGui::Selectable(std::to_string(i).c_str(), is_selected)) {
                        currentComponent = i;
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndListBox();
            }
        }
        void _showTransfomComponentMenu();
        void _showTextureComponentMenu();
        void _showCameraComponentMenu();
        void _showCollisionComponentMenu();
        void _showFontComponentMenu();
        void _showMusicComponentMenu();
        void _showPressableComponentMenu();
        void _showTextComponentMenu();
        void _showControllableComponentMenu();
    };
} // namespace Debug
    #endif
#endif
