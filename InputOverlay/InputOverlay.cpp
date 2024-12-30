/*
* Input Overlay Plugin for BakkesMod
* Created by tomsLt0
* Last updated: 2024-12-30
*/

#include "pch.h"
#include "InputOverlay.h"
#include "bakkesmod/wrappers/GuiManagerWrapper.h"

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

BAKKESMOD_PLUGIN(InputOverlay, "Input Overlay", plugin_version, PLUGINTYPE_FREEPLAY)

void InputOverlay::onLoad()
{
    gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
        HandleInput();
        if (gameWrapper->IsInGame()) {
            RenderKeyboardOverlay(canvas);
        }
        });

    cvarManager->log("Input Overlay Plugin loaded!");
}

void InputOverlay::onUnload()
{
    cvarManager->log("Input Overlay Plugin unloaded!");
}

void InputOverlay::HandleInput()
{
    isKeyPressed[0] = (GetAsyncKeyState(0x51) & 0x8000) != 0; // Q
    isKeyPressed[1] = (GetAsyncKeyState(0x57) & 0x8000) != 0; // W
    isKeyPressed[2] = (GetAsyncKeyState(0x45) & 0x8000) != 0; // E
    isKeyPressed[3] = (GetAsyncKeyState(0x41) & 0x8000) != 0; // A
    isKeyPressed[4] = (GetAsyncKeyState(0x53) & 0x8000) != 0; // S
    isKeyPressed[5] = (GetAsyncKeyState(0x44) & 0x8000) != 0; // D
    isKeyPressed[6] = (GetAsyncKeyState(VK_CAPITAL) & 0x8000) != 0; // Caps Lock

    isMousePressed[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0; // LMB
    isMousePressed[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0; // RMB
}

void InputOverlay::RenderKeyboardOverlay(CanvasWrapper canvas)
{
    float baseKeySize = 60.0f;
    float spacing = 8.0f;
    float capsWidth = baseKeySize * 1.5f;
    Vector2F basePos = { 100.0f, 100.0f };

    // First row (Q,W,E)
    RenderKey(canvas, Vector2F{ basePos.X, basePos.Y }, "Q", isKeyPressed[0], baseKeySize);
    RenderKey(canvas, Vector2F{ basePos.X + baseKeySize + spacing, basePos.Y }, "W", isKeyPressed[1], baseKeySize);
    RenderKey(canvas, Vector2F{ basePos.X + (baseKeySize + spacing) * 2.0f, basePos.Y }, "E", isKeyPressed[2], baseKeySize);

    // Second row (A,S,D)
    RenderKey(canvas, Vector2F{ basePos.X, basePos.Y + baseKeySize + spacing }, "A", isKeyPressed[3], baseKeySize);
    RenderKey(canvas, Vector2F{ basePos.X + baseKeySize + spacing, basePos.Y + baseKeySize + spacing }, "S", isKeyPressed[4], baseKeySize);
    RenderKey(canvas, Vector2F{ basePos.X + (baseKeySize + spacing) * 2.0f, basePos.Y + baseKeySize + spacing }, "D", isKeyPressed[5], baseKeySize);

    // Caps Lock
    RenderKey(canvas, Vector2F{ basePos.X, basePos.Y + (baseKeySize + spacing) * 2.0f }, "CAPS", isKeyPressed[6], capsWidth);

    // Mouse buttons
    float mouseButtonsX = basePos.X + (baseKeySize + spacing) * 3.5f;
    float mouseButtonsY = basePos.Y + baseKeySize + spacing;
    RenderMouseButton(canvas, Vector2F{ mouseButtonsX, mouseButtonsY }, "LMB", isMousePressed[0]);
    RenderMouseButton(canvas, Vector2F{ mouseButtonsX + baseKeySize + spacing, mouseButtonsY }, "RMB", isMousePressed[1]);
}

void InputOverlay::RenderKey(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed, float width)
{
    float height = 60.0f;
    float borderThickness = 2.0f;

    // Fill
    canvas.SetColor(244, 208, 63, isPressed ? 255 : 0); // #F4D03F when pressed, transparent when not
    canvas.SetPosition(position);
    canvas.FillBox(Vector2F{ width, height });

    // Single white border
    canvas.SetColor(255, 255, 255, 255);
    canvas.SetPosition(position);
    canvas.DrawBox(Vector2F{ width, height });

    // Get text dimensions for proper centering
    float textScale = (strcmp(label, "CAPS") == 0) ? 1.2f : 1.8f; // Smaller scale for CAPS, larger for single letters
    canvas.SetColor(255, 255, 255, 255);
    auto textDimensions = canvas.GetStringSize(label, textScale, textScale);

    // Calculate center position
    Vector2F textPos = {
        position.X + (width - textDimensions.X) / 2.0f,
        position.Y + (height - textDimensions.Y) / 2.0f
    };

    canvas.SetPosition(textPos);
    canvas.DrawString(label, textScale, textScale);
}

void InputOverlay::RenderMouseButton(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed)
{
    float width = 60.0f;
    float height = 45.0f;
    float borderThickness = 2.0f;

    // Fill
    canvas.SetColor(244, 208, 63, isPressed ? 255 : 0); // #F4D03F when pressed, transparent when not
    canvas.SetPosition(position);
    canvas.FillBox(Vector2F{ width, height });

    // Single white border
    canvas.SetColor(255, 255, 255, 255);
    canvas.SetPosition(position);
    canvas.DrawBox(Vector2F{ width, height });

    // Get text dimensions for proper centering
    float textScale = 1.2f; // Mouse button text stays the same size
    canvas.SetColor(255, 255, 255, 255);
    auto textDimensions = canvas.GetStringSize(label, textScale, textScale);

    // Calculate center position
    Vector2F textPos = {
        position.X + (width - textDimensions.X) / 2.0f,
        position.Y + (height - textDimensions.Y) / 2.0f
    };

    canvas.SetPosition(textPos);
    canvas.DrawString(label, textScale, textScale);
}
