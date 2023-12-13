#pragma once

#include "core.h"

struct Input;
struct State;

void InitGUI();
void ApplyGUI(f32 viewportWidth, f32 viewportHeight, Input* input, State* state);
