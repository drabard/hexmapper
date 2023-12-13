#include "gui.h"

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include "state.h"

constexpr f32 BUTTON_BORDER_SIZE = 0.1f;
constexpr f32 TOOLBAR_WIDTH = 500.0f + BUTTON_BORDER_SIZE * 2.0f;
constexpr f32 TOOLBAR_HEIGHT = 50.0f + BUTTON_BORDER_SIZE * 2.0f;
constexpr f32 RIGHT_PANEL_WIDTH = 330.0f;

constexpr ImColor COLOR_EBONY = ImColor(0.333f, 0.365f, 0.314f);
constexpr ImColor COLOR_COOL_GRAY = ImColor(0.549f, 0.573f, 0.675f);
constexpr ImColor COLOR_GRAY = ImColor(0.502f, 0.502f, 0.502f);
constexpr ImColor COLOR_LIGHT_GRAY = ImColor(0.602f, 0.602f, 0.602f);
constexpr ImColor COLOR_PEWTER = ImColor(0.914f, 0.918f, 0.925f);


void updateGUIRect(Rectangle *rect) {
    ImVec2 panel_pos = ImGui::GetWindowPos();
    ImVec2 panel_size = ImGui::GetWindowSize();
    *rect = (Rectangle){panel_pos.x, panel_pos.y, panel_size.x, panel_size.y};
}

void InitGUI() { rlImGuiSetup(true); }

void ShowRightHandPanel(f32 screenWidth, f32 screenHeight) {
    f32 panelHeight = screenHeight;

    ImGui::SetNextWindowPos(ImVec2(screenWidth - RIGHT_PANEL_WIDTH, 0));
    ImGui::SetNextWindowSize(ImVec2(RIGHT_PANEL_WIDTH, panelHeight));

    ImGui::Begin("Right hand panel", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    //       updateGUIRect(&state->toolPanelRect);
    ImGui::End();
}

void ShowToolbar(f32 screenWidth, f32 screenHeight) {
    f32 viewportWidth = screenWidth - RIGHT_PANEL_WIDTH;
    ImGui::SetNextWindowPos(ImVec2(0.5f * (viewportWidth - TOOLBAR_WIDTH), 0));
    ImGui::SetNextWindowSize(ImVec2(TOOLBAR_WIDTH, TOOLBAR_HEIGHT));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, BUTTON_BORDER_SIZE);

    ImGui::Begin("Toolbar", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    constexpr f32 buttonWidth = TOOLBAR_WIDTH * 0.20f;

    ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)COLOR_GRAY);

    ImGui::Button("Select", ImVec2(buttonWidth, TOOLBAR_HEIGHT));
    ImGui::SameLine();
    ImGui::Button("Paint", ImVec2(buttonWidth, TOOLBAR_HEIGHT));
    ImGui::SameLine();
    ImGui::Button("Rotate", ImVec2(buttonWidth, TOOLBAR_HEIGHT));
    ImGui::SameLine();
    ImGui::Button("Erase", ImVec2(buttonWidth, TOOLBAR_HEIGHT));
    ImGui::SameLine();
    ImGui::Button("Zoom", ImVec2(buttonWidth, TOOLBAR_HEIGHT));
    ImGui::SameLine();

    ImGui::PopStyleColor(1);

    ImGui::PopStyleVar(3);

    ImGui::End();
}

void DrawGUI(f32 screenWidth, f32 screenHeight) {
    rlImGuiBegin();

    // ImGui::ShowDemoWindow();

    ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)COLOR_EBONY);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)COLOR_EBONY);
    ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)COLOR_PEWTER);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                          (ImVec4)COLOR_GRAY);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)COLOR_COOL_GRAY);

    ShowRightHandPanel(screenWidth, screenHeight);
    ShowToolbar(screenWidth, screenHeight);

    ImGui::PopStyleColor(5);

    rlImGuiEnd();
}

