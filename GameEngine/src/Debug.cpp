/*
** EPITECH PROJECT, 2023
** R-Type-epitech
** File description:
** Debug
*/

#include "Debug.hpp"
#include "components/TransformComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/MusicComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/DamageComponent.hpp"
#include "components/GravityComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/ScoreComponent.hpp"
#include "components/NetworkIdComponent.hpp"

#ifdef DEBUG
namespace Debug
{
    void DebugMenu::_showTransfomComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::TransformComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::TransformComponent> &transforms =
                _registry.getComponent<GameEngine::TransformComponent>();
            _showComponentList<GameEngine::TransformComponent>(transforms, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (transforms[currentComponent]) {
                ImGui::Text("Position: (%f, %f)", transforms[currentComponent]->position.x,
                    transforms[currentComponent]->position.y);
                ImGui::Text("Velocity: (%f, %f)", transforms[currentComponent]->velocity.x,
                    transforms[currentComponent]->velocity.y);
            }
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showTextureComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::TextureComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::TextureComponent> &textures =
                _registry.getComponent<GameEngine::TextureComponent>();
            _showComponentList<GameEngine::TextureComponent>(textures, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (textures[currentComponent]) {
                ImGui::Checkbox("Is Rendered", &textures[currentComponent]->isRendered);
                ImGui::Checkbox("Is Animated", &textures[currentComponent]->animated);
                ImGui::Text("Render Layer: %ld", textures[currentComponent]->renderLayer);
                ImGui::Text("Texture Path: \"%s\"", textures[currentComponent]->path.c_str());
                if (textures[currentComponent]->animated)
                    ImGui::Text("Animation state: %f/%f (%ld/%ld)", textures[currentComponent]->lastUpdate,
                        textures[currentComponent]->animationSpeed, textures[currentComponent]->animeid,
                        textures[currentComponent]->textureRects.size());
            }
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showCameraComponentMenu()
    {
        ImGui::Text("No information available for this component");
        ImGui::TreePop();
    }

    void DebugMenu::_showCollisionComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::CollisionComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::CollisionComponent> &collisions =
                _registry.getComponent<GameEngine::CollisionComponent>();
            _showComponentList<GameEngine::CollisionComponent>(collisions, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (collisions[currentComponent]) {
                ImGui::Checkbox("Collision Active", &collisions[currentComponent]->isActive);
                ImGui::Text("Layer: %ld", collisions[currentComponent]->layer);
                ImGui::Text("Actions registered: %ld", collisions[currentComponent]->actions.size());
            }
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showMusicComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::MusicComponent>()) {
            ImGui::Text("No information available for this component");
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showPressableComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::PressableComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::PressableComponent> &pressables =
                _registry.getComponent<GameEngine::PressableComponent>();
            _showComponentList<GameEngine::PressableComponent>(pressables, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (pressables[currentComponent]) {
                switch (pressables[currentComponent]->state) {
                case GameEngine::PressableState::defaultState:
                    ImGui::Text("State: Default");
                    break;
                case GameEngine::PressableState::hoveredState:
                    ImGui::Text("State: Hovered");
                    break;
                case GameEngine::PressableState::pressedState:
                    ImGui::Text("State: Pressed");
                    break;
                default:
                    ImGui::Text("State: Undifined");
                }
            }
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showTextComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::TextComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::TextComponent> &texts = _registry.getComponent<GameEngine::TextComponent>();
            _showComponentList<GameEngine::TextComponent>(texts, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (texts[currentComponent]) {
                ImGui::Text("Text: %s", texts[currentComponent]->str.c_str());
                ImGui::Text("Size: %ld", texts[currentComponent]->size);
                ImGui::Checkbox("Is Rendered", &texts[currentComponent]->isRendered);
                ImGui::Text("Layer: %ld", texts[currentComponent]->renderLayer);
            }
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showControllableComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::ControllableComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::ControllableComponent> &controllables =
                _registry.getComponent<GameEngine::ControllableComponent>();
            _showComponentList<GameEngine::ControllableComponent>(controllables, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (controllables[currentComponent]) {
                ImGui::Text("Speed: %f", controllables[currentComponent]->speed);
            }
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showDamageComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::DamageComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::DamageComponent> &damageComponents =
                _registry.getComponent<GameEngine::DamageComponent>();
            _showComponentList<GameEngine::DamageComponent>(damageComponents, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (damageComponents[currentComponent])
                ImGui::Text("Damage: %hhu", damageComponents[currentComponent]->damage);
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showGravityComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::GravityComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::GravityComponent> &gravityComponents =
                _registry.getComponent<GameEngine::GravityComponent>();
            _showComponentList<GameEngine::GravityComponent>(gravityComponents, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (gravityComponents[currentComponent]) {
                ImGui::Text("Gravity Force: (%f, %f)", gravityComponents[currentComponent]->gravityForce.x,
                    gravityComponents[currentComponent]->gravityForce.y);
                ImGui::Text("Cumulated G Velocity: (%f, %f)", gravityComponents[currentComponent]->cumulatedGVelocity.x,
                    gravityComponents[currentComponent]->cumulatedGVelocity.y);
                if (ImGui::Button("Reset Cumulated G Velocity"))
                    gravityComponents[currentComponent]->cumulatedGVelocity = GameEngine::Vector2<float>(0.0f, 0.0f);
                ImGui::Checkbox("Is Active", &gravityComponents[currentComponent]->isActive);
            }
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showInputComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::InputComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::InputComponent> &inputComponents =
                _registry.getComponent<GameEngine::InputComponent>();
            _showComponentList<GameEngine::InputComponent>(inputComponents, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (inputComponents[currentComponent]) {
                ImGui::Text("Input Registered: %hhu", inputComponents[currentComponent]->inputs.size());
                ImGui::Text("Inputs:");
                for (auto inputInfo : inputComponents[currentComponent]->inputs)
                    ImGui::Text("[%hhu -> %d]", inputInfo.first, inputInfo.second);
            }
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showHealthComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::HealthComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::HealthComponent> &healthComponents =
                _registry.getComponent<GameEngine::HealthComponent>();
            _showComponentList<GameEngine::HealthComponent>(healthComponents, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (healthComponents[currentComponent])
                ImGui::Text("Health: %d", healthComponents[currentComponent]->health);
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showScoreComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::ScoreComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::ScoreComponent> &scoreComponents =
                _registry.getComponent<GameEngine::ScoreComponent>();
            _showComponentList<GameEngine::ScoreComponent>(scoreComponents, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (scoreComponents[currentComponent])
                ImGui::Text("Score: %ld", scoreComponents[currentComponent]->score);
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showNetworkIdComponentMenu()
    {
        if (_registry.isComponentRegistered<GameEngine::NetworkIdComponent>()) {
            static int currentComponent = 0;
            ImGui::BeginGroup();
            SparseArray<GameEngine::NetworkIdComponent> &networkIdComponents =
                _registry.getComponent<GameEngine::NetworkIdComponent>();
            _showComponentList<GameEngine::NetworkIdComponent>(networkIdComponents, currentComponent);
            ImGui::SameLine();
            ImGui::BeginGroup();
            if (networkIdComponents[currentComponent])
                ImGui::Text("Network ID: %ld", networkIdComponents[currentComponent]->id);
            ImGui::EndGroup();
            ImGui::EndGroup();
        } else {
            ImGui::Text("Component not registered");
        }
        ImGui::TreePop();
    }

    void DebugMenu::_showGameMenu()
    {
        static int fpsLimit = DEFAULT_FPS_LIMIT_SLIDER_VALUE;
        static int oldFpsLimit = 0;
        static bool unlimitedFps = false;
        static int fpsValuesOffset = 0;
        static int maxFps = 0;
        static int lowFps = fpsLimit;
        static float fpsValues[DEFAULT_FPS_PLOT_NB_VALUES] = {};
        static double plotRefreshRate = DEFAULT_FPS_PLOT_REFRESH_RATE;
        static double plotDeltaTime = 0.0;
        float fps = 0.0f;
        char fpsText[DEFAULT_FPS_PLOT_TEXT_LENGTH];

        if (plotDeltaTime == 0.0)
            plotDeltaTime = ImGui::GetTime();
        fps = 1 / _deltaTime.getDeltaTime();
        if (fps > maxFps)
            maxFps = fps;
        if (fps < lowFps)
            lowFps = fps;
        while (plotDeltaTime < ImGui::GetTime()) {
            fpsValues[fpsValuesOffset] = fps;
            fpsValuesOffset = (fpsValuesOffset + 1) % IM_ARRAYSIZE(fpsValues);
            plotDeltaTime += 1.0f / plotRefreshRate;
        }
        sprintf(fpsText, "FPS: %f", fps);
        ImGui::SeparatorText("FPS");
        ImGui::PlotLines("##fpsPlot", fpsValues, IM_ARRAYSIZE(fpsValues), fpsValuesOffset, fpsText, 0.0f, fpsLimit * 2,
            DEFAULT_FPS_PLOT_SIZE);

        if (!unlimitedFps) {
            if (ImGui::SliderInt("##fpsLimitSlider", &fpsLimit, 1, DEFAULT_FPS_LIMIT_SLIDER_MAX_VALUE, "%d"))
                _eventManager
                    .getHandler<const float &>(static_cast<GameEngine::EventType>(GameEngine::Event::SetFpsLimitEvent))
                    .publish((float)fpsLimit);
        } else {
            fpsLimit = maxFps;
        }
        if (ImGui::Checkbox("Unlimited Fps", &unlimitedFps)) {
            if (unlimitedFps) {
                oldFpsLimit = fpsLimit;
                maxFps = 0;
                lowFps = fpsLimit;
                _eventManager
                    .getHandler<const float &>(static_cast<GameEngine::EventType>(GameEngine::Event::SetFpsLimitEvent))
                    .publish(-1.0f);
            } else {
                fpsLimit = oldFpsLimit;
                _eventManager
                    .getHandler<const float &>(static_cast<GameEngine::EventType>(GameEngine::Event::SetFpsLimitEvent))
                    .publish((float)fpsLimit);
            }
        }
        ImGui::Text("Low: %d, Max: %d", lowFps, maxFps);
        ImGui::EndTabItem();
    }

    void DebugMenu::_showRegistryMenu()
    {
        if (ImGui::CollapsingHeader("Entities")) {
            ImGui::SeparatorText("Entities");
            ImGui::Text("Living Entities: %d/%d", _registry._nbEntities - _registry._emptyIndexes.size(),
                _registry._maxEntities);
            ImGui::Text("Max Entity Id Used: %d/%d", _registry._nbEntities, _registry._maxEntities);
        }
        if (ImGui::CollapsingHeader("Components")) {
            ImGui::SeparatorText("Components");
            if (ImGui::TreeNode("Transform"))
                _showTransfomComponentMenu();
            if (ImGui::TreeNode("Texture"))
                _showTextureComponentMenu();
            if (ImGui::TreeNode("Camera"))
                _showCameraComponentMenu();
            if (ImGui::TreeNode("Collision"))
                _showCollisionComponentMenu();
            if (ImGui::TreeNode("Music"))
                _showMusicComponentMenu();
            if (ImGui::TreeNode("Pressable"))
                _showPressableComponentMenu();
            if (ImGui::TreeNode("Text"))
                _showTextComponentMenu();
            if (ImGui::TreeNode("Controllable"))
                _showControllableComponentMenu();
            if (ImGui::TreeNode("Damage"))
                _showDamageComponentMenu();
            if (ImGui::TreeNode("Gravity"))
                _showGravityComponentMenu();
            if (ImGui::TreeNode("Input"))
                _showInputComponentMenu();
            if (ImGui::TreeNode("Health"))
                _showHealthComponentMenu();
            if (ImGui::TreeNode("Score"))
                _showScoreComponentMenu();
            if (ImGui::TreeNode("Network ID"))
                _showNetworkIdComponentMenu();
        }
        if (ImGui::CollapsingHeader("Systems")) {
            ImGui::SeparatorText("Systems");
            ImGui::Text("Systems Registered: %ld", _registry._systems.size());
        }
        ImGui::EndTabItem();
    }

    void DebugMenu::_showEventsMenu()
    {
        ImGui::SeparatorText("Events");
        ImGui::BeginChild("##eventLog", ImVec2(ImGui::GetContentRegionAvail().x, DEFAULT_EVENT_LOG_HEIGHT),
            ImGuiChildFlags_Border,
            ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar);

        ImGuiListClipper eventLog;
        eventLog.Begin(_eventManager.eventLog.size());
        while (eventLog.Step()) {
            for (int i = eventLog.DisplayStart; i < eventLog.DisplayEnd; i++) {
                if (GameEngine::InternalEventNames.contains(_eventManager.eventLog[i])) {
                    ImGui::Text("[%d](Internal) Event triggered: %s", i,
                        GameEngine::InternalEventNames.at(_eventManager.eventLog[i]).c_str());
                } else
                    ImGui::Text("[%d] Event triggered: %ld", i, _eventManager.eventLog[i]);
            }
        }

        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
        ImGui::EndChild();
        if (ImGui::Button("Clear Event Log"))
            _eventManager.eventLog.clear();
        ImGui::SameLine();
        ImGui::Text("(Auto Clear at %d Event)", GameEngine::DEFAULT_MAX_EVENT_LOG_LENGTH);
    }

} // namespace Debug
#endif
