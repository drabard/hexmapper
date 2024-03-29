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

void InitGUI() { rlImGuiSetup(true); }

void ShowImageDirectory(FsNode* directory, i32 siblingIdx) {
    if(ImGui::TreeNodeEx(directory->path.c_str(), 0)) {
        for(FsNode file : directory->files) {
            ImGui::Text("- %s", file.path.c_str());
        }

        i32 siblingIdx = 0;
        for(FsNode subdir : directory->dirs) {
            ShowImageDirectory(&subdir, siblingIdx++);
        }

        ImGui::TreePop();
    }
}

void ShowImagesLibrary(State* state) {
    ShowImageDirectory(&state->imagesRoot, 0);
}

void ShowRightHandPanel(f32 screenWidth, f32 screenHeight, Input* input, State* state) {
    f32 panelHeight = screenHeight;

    ImGui::SetNextWindowPos(ImVec2(screenWidth - RIGHT_PANEL_WIDTH, 0));
    ImGui::SetNextWindowSize(ImVec2(RIGHT_PANEL_WIDTH, panelHeight));

    ImGui::Begin("Right hand panel", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    switch (input->mode) {
        case INPUT_MODE_SELECT:
            ImGui::Text("Select tiles");
            ShowImagesLibrary(state);
            break;
        case INPUT_MODE_PAINT:
            ImGui::Text("Paint tiles");
            break;
        case INPUT_MODE_ROTATE:
            ImGui::Text("Rotate tiles");
            break;
        case INPUT_MODE_ERASE:
            ImGui::Text("Erase tiles");
            break;
    }
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
    ImGui::SetNextWindowPos(ImVec2(0, screenHeight - BOTTOM_LEFT_PANEL_HEIGHT));
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

void ShowZoomPanel(f32 screenWidth, f32 screenHeight, Input* input,
                   State* state) {
    constexpr f32 ZOOM_BUTTON_HEIGHT = 25.0f;
    constexpr f32 ZOOM_BUTTON_WIDTH = 50.0f;
    constexpr f32 ZOOM_INDICATOR_WIDTH = 100.0f;
    constexpr f32 ZOOM_PANEL_WIDTH = ZOOM_BUTTON_WIDTH + ZOOM_INDICATOR_WIDTH;
    constexpr f32 ZOOM_PANEL_HEIGHT = ZOOM_BUTTON_HEIGHT * 2.0f;

    f32 viewportWidth = screenWidth - RIGHT_PANEL_WIDTH;

    ImGui::SetNextWindowPos(ImVec2(0.5f * (viewportWidth - ZOOM_PANEL_WIDTH),
                                   screenHeight - ZOOM_PANEL_HEIGHT));
    ImGui::SetNextWindowSize(ImVec2(ZOOM_INDICATOR_WIDTH, ZOOM_PANEL_HEIGHT));

    ImGui::Begin("Zoom indicator", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    switch (state->zoomLevel) {
        case ZOOM_6_MILES:
            ImGui::TextUnformatted("6 mile hex");
            break;
        case ZOOM_12_MILES:
            ImGui::TextUnformatted("12 mile hex");
            break;
        case ZOOM_24_MILES:
            ImGui::TextUnformatted("24 mile hex");
            break;
        case ZOOM_48_MILES:
            ImGui::TextUnformatted("48 mile hex");
            break;
        default:
            assert(!"Invalid ZoomLevel.");
    }
    ImGui::End();

    ImGui::SetNextWindowPos(
        ImVec2(0.5f * (viewportWidth - ZOOM_PANEL_WIDTH) + ZOOM_INDICATOR_WIDTH,
               screenHeight - ZOOM_PANEL_HEIGHT));
    ImGui::SetNextWindowSize(ImVec2(ZOOM_BUTTON_WIDTH, ZOOM_PANEL_HEIGHT));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, BUTTON_BORDER_SIZE);

    ImGui::Begin("Zoom buttons", 0,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    if (ImGui::Button("+", ImVec2(ZOOM_BUTTON_WIDTH, ZOOM_BUTTON_HEIGHT))) {
        input->zoomIn = true;
    }
    if (ImGui::Button("-", ImVec2(ZOOM_BUTTON_WIDTH, ZOOM_BUTTON_HEIGHT))) {
        input->zoomOut = true;
    }
    ImGui::End();

    ImGui::PopStyleVar(3);
}

void ApplyGUI(f32 screenWidth, f32 screenHeight, Input* input, State* state) {
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
    ShowRightHandPanel(screenWidth, screenHeight, input, state);
    ShowZoomPanel(screenWidth, screenHeight, input, state);

    ImGui::PopStyleColor(7);

    rlImGuiEnd();
}

