#include "gui.h"

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include "state.h"

void updateGUIRect(Rectangle *rect) {
    ImVec2 panel_pos = ImGui::GetWindowPos();
    ImVec2 panel_size = ImGui::GetWindowSize();
    *rect = (Rectangle){panel_pos.x, panel_pos.y, panel_size.x, panel_size.y};
}

void InitGUI() { rlImGuiSetup(true); }

void DrawGUI(State *state) {
    rlImGuiBegin();

    f32 vpWidth = state->viewportWidth;
    f32 vpHeight = state->viewportHeight;

    f32 panelWidth = 350.0;
    f32 panelHeight = vpHeight;
    ImGui::SetNextWindowPos(ImVec2(vpWidth - panelWidth, 0));
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight));
    ImGui::Begin("Tools Panel", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    //       updateGUIRect(&state->toolPanelRect);
    ImGui::End();

    rlImGuiEnd();
}

