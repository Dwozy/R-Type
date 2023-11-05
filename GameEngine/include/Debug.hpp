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
    static const float DEFAULT_COMPONENT_LIST_HEIGHT = 150.0f;
    static const float DEFAULT_EVENT_LOG_HEIGHT = 200.0f;
    static const size_t DEFAULT_FPS_PLOT_TEXT_LENGTH = 32;
    static const size_t DEFAULT_FPS_PLOT_NB_VALUES = 90;
    static const double DEFAULT_FPS_PLOT_REFRESH_RATE = 60.0;
    static const ImVec2 DEFAULT_FPS_PLOT_SIZE = ImVec2(0, 80.0f);
    static const int DEFAULT_FPS_LIMIT_SLIDER_MAX_VALUE = 1000;
    static const int DEFAULT_FPS_LIMIT_SLIDER_VALUE = 60;

    class DebugMenu
    {
      public:
        /// @brief Debug menu constructor
        /// @param eventManager reference to the event manager
        /// @param registry reference to the registry
        /// @param deltaTime reference to the delta time
        DebugMenu(
            GameEngine::EventManager &eventManager, GameEngine::Registry &registry, GameEngine::DeltaTime &deltaTime)
            : _eventManager(eventManager), _registry(registry), _deltaTime(deltaTime)
        {
        }
        /// @brief DebugMenu Destructor
        ~DebugMenu() {}

        /// @brief draw the Debug Menu
        void draw()
        {
            ImGui::SetNextWindowSize(DEBUG_MENU_DEFAULT_WINDOW_SIZE, ImGuiCond_FirstUseEver);
            ImGui::Begin("Debug Menu");
            if (ImGui::BeginTabBar("MainTabBar")) {
                if (ImGui::BeginTabItem("Game")) {
                    _showGameMenu();
                }
                if (ImGui::BeginTabItem("Registry")) {
                    _showRegistryMenu();
                }
                if (ImGui::BeginTabItem("Events")) {
                    _showEventsMenu();
                }
                ImGui::EndTabBar();
            }
            ImGui::End();
        }

      private:
        GameEngine::EventManager &_eventManager;
        GameEngine::Registry &_registry;
        GameEngine::DeltaTime &_deltaTime;
        /// @brief show the "Game" part of the Debug Menu
        void _showGameMenu();
        /// @brief show the "Registry" part of the Debug Menu
        void _showRegistryMenu();
        /// @brief show a list of all the instance of a components with specific type
        /// @tparam Component type of the components
        /// @param components list of the components
        /// @param currentComponent current component selected in the list
        template <typename Component>
        void _showComponentList(SparseArray<Component> &components, int &currentComponent)
        {
            if (ImGui::BeginListBox("##componentList", ImVec2(ImGui::GetContentRegionAvail().x / 3.0f, DEFAULT_COMPONENT_LIST_HEIGHT))) {
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
        /// @brief show a list of all the Transfom components and the stored info
        void _showTransfomComponentMenu();
        /// @brief show a list of all the Texture components and the stored info
        void _showTextureComponentMenu();
        /// @brief show a list of all the Camera components and the stored info
        void _showCameraComponentMenu();
        /// @brief show a list of all the Collision components and the stored info
        void _showCollisionComponentMenu();
        /// @brief show a list of all the Font components and the stored info
        void _showFontComponentMenu();
        /// @brief show a list of all the Music components and the stored info
        void _showMusicComponentMenu();
        /// @brief show a list of all the Pressable components and the stored info
        void _showPressableComponentMenu();
        /// @brief show a list of all the Text components and the stored info
        void _showTextComponentMenu();
        /// @brief show a list of all the Controllable components and the stored info
        void _showControllableComponentMenu();
        /// @brief show a list of all the Damage components and the stored info
        void _showDamageComponentMenu();
        /// @brief show a list of all the Gravity components and the stored info
        void _showGravityComponentMenu();
        /// @brief show a list of all the Input components and the stored info
        void _showInputComponentMenu();
        /// @brief show a list of all the Health components and the stored info
        void _showHealthComponentMenu();
        /// @brief show a list of all the Score components and the stored info
        void _showScoreComponentMenu();
        /// @brief show a list of all the NetworkId components and the stored info
        void _showNetworkIdComponentMenu();
        /// @brief show the "Event" part of the Debug Menu
        void _showEventsMenu();
    };
} // namespace Debug
    #endif
#endif
