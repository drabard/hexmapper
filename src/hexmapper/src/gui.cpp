#include "gui.h"

#include "imgui.h"
#include "input.h"
#include "raylib.h"
#include "rlImGui.h"

constexpr f32 BUTTON_BORDER_SIZE = 0.1f;
constexpr f32 BUTTON_HEIGHT = 50.0f;
constexpr f32 TOOLBAR_WIDTH = 400.0f + BUTTON_BORDER_SIZE * 2.0f;
constexpr f32 TOOLBAR_HEIGHT = 50.0f + BUTTON_BORDER_SIZE * 2.0f;
constexpr f32 RIGHT_PANEL_WIDTH = 440.0f;
constexpr f32 BOTTOM_LEFT_PANEL_WIDTH = 150.0f;
constexpr f32 BOTTOM_LEFT_PANEL_HEIGHT = 50.0f;

constexpr ImColor COLOR_EBONY = ImColor(0.333f, 0.365f, 0.314f);
constexpr ImColor COLOR_COOL_GRAY = ImColor(0.549f, 0.573f, 0.675f);
constexpr ImColor COLOR_GRAY = ImColor(0.502f, 0.502f, 0.502f);
constexpr ImColor COLOR_LIGHT_GRAY = ImColor(0.602f, 0.602f, 0.602f);
constexpr ImColor COLOR_PEWTER = ImColor(0.914f, 0.918f, 0.925f);

void updateGUIRect(Rectangle* rect) {
    ImVec2 panel_pos = ImGui::GetWindowPos();
    ImVec2 panel_size = ImGui::GetWindowSize();
    *rect = (Rectangle){panel_pos.x, panel_pos.y, panel_size.x, panel_size.y};
}

void InitGUI() { rlImGuiSetup(true); }

void ShowRightHandPanel(f32 screenWidth, f32 screenHeight, Input* input) {
    f32 panelHeight = screenHeight;

    ImGui::SetNextWindowPos(ImVec2(screenWidth - RIGHT_PANEL_WIDTH, 0));
    ImGui::SetNextWindowSize(ImVec2(RIGHT_PANEL_WIDTH, panelHeight));

    ImGui::Begin("Right hand panel", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    //       updateGUIRect(&state->toolPanelRect);
    const char* headerText = "Selection information";
    switch (input->mode) {
        case INPUT_MODE_SELECT:
            headerText = "Select tiles";
            break;
        case INPUT_MODE_PAINT:
            headerText = "Paint tiles";
            break;
        case INPUT_MODE_ROTATE:
            headerText = "Rotate tiles";
            break;
        case INPUT_MODE_ERASE:
            headerText = "Erase tiles";
            break;
    }
    ImGui::Text(headerText);
    ImGui::End();
}

void ModeButton(const char* label, InputMode mode, Input* input,
                f32 buttonWidth) {
    if (input->mode == mode) ImGui::BeginDisabled();
    if (ImGui::Button(label, ImVec2(buttonWidth, BUTTON_HEIGHT))) {
        input->mode = mode;
    } else if (input->mode == mode) {
        ImGui::EndDisabled();
    }
}

void ShowToolbar(f32 screenWidth, f32 screenHeight, Input* input) {
    f32 viewportWidth = screenWidth - RIGHT_PANEL_WIDTH;
    ImGui::SetNextWindowPos(ImVec2(0.5f * (viewportWidth - TOOLBAR_WIDTH), 0));
    ImGui::SetNextWindowSize(ImVec2(TOOLBAR_WIDTH, TOOLBAR_HEIGHT));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, BUTTON_BORDER_SIZE);

    ImGui::Begin("Toolbar", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    constexpr f32 buttonWidth = TOOLBAR_WIDTH * 0.25f;

    ModeButton("Select", INPUT_MODE_SELECT, input, buttonWidth);
    ImGui::SameLine();
    ModeButton("Paint", INPUT_MODE_PAINT, input, buttonWidth);
    ImGui::SameLine();
    ModeButton("Rotate", INPUT_MODE_ROTATE, input, buttonWidth);
    ImGui::SameLine();
    ModeButton("Erase", INPUT_MODE_ERASE, input, buttonWidth);

    ImGui::PopStyleVar(3);

    ImGui::End();
}

void ShowBottomLeftPanel(f32 screenWidth, f32 screenHeight) {
    TraceLog(LOG_INFO, "Screen width: %f, Screen height: %f", screenWidth,
             screenHeight);
    ImGui::SetNextWindowPos(ImVec2(0, screenHeight - BOTTOM_LEFT_PANEL_HEIGHT));
    TraceLog(LOG_INFO, "Bottom left panel pos: 0, %f",
             screenHeight - BOTTOM_LEFT_PANEL_HEIGHT);
    ImGui::SetNextWindowSize(
        ImVec2(BOTTOM_LEFT_PANEL_WIDTH, BOTTOM_LEFT_PANEL_HEIGHT));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, BUTTON_BORDER_SIZE);

    ImGui::Begin("Bottom left panel", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    //       updateGUIRect(&state->toolPanelRect);
    constexpr f32 buttonWidth = BOTTOM_LEFT_PANEL_WIDTH * 0.5f;
    ImGui::Button("Save", ImVec2(buttonWidth, BUTTON_HEIGHT));
    ImGui::SameLine();
    ImGui::Button("Load", ImVec2(buttonWidth, BUTTON_HEIGHT));
    ImGui::SameLine();

    ImGui::End();

    ImGui::PopStyleVar(3);
}

void ApplyGUI(f32 screenWidth, f32 screenHeight, Input* input) {
    rlImGuiBegin();

    // ImGui::ShowDemoWindow();

    ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)COLOR_EBONY);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)COLOR_EBONY);
    ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)COLOR_PEWTER);
    ImGui::PushStyleColor(ImGuiCol_TextDisabled,
                          (ImVec4)ImColor(1.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)COLOR_GRAY);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)COLOR_COOL_GRAY);
    ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)COLOR_GRAY);

    ShowToolbar(screenWidth, screenHeight, input);
    ShowBottomLeftPanel(screenWidth, screenHeight);
    ShowRightHandPanel(screenWidth, screenHeight, input);

    ImGui::PopStyleColor(7);

    rlImGuiEnd();
}

