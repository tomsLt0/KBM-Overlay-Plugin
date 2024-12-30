// InputOverlay.cpp
#include "pch.h"
#include "InputOverlay.h"

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

BAKKESMOD_PLUGIN(InputOverlay, "Displays keyboard and mouse inputs overlay", "1", PLUGINTYPE_FREEPLAY)

void InputOverlay::onLoad()
{
    gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
        RenderKeyboardOverlay(canvas);
        });

    gameWrapper->HookEvent("Function TAGame.GameViewportClient_TA.Tick",
        [this](std::string eventName) {
            HandleInput();
        });
}

void InputOverlay::onUnload()
{
}

void InputOverlay::HandleInput()
{
    isKeyPressed[0] = GetAsyncKeyState(0x51) & 0x8000; // Q
    isKeyPressed[1] = GetAsyncKeyState(0x57) & 0x8000; // W
    isKeyPressed[2] = GetAsyncKeyState(0x45) & 0x8000; // E
    isKeyPressed[3] = GetAsyncKeyState(0x41) & 0x8000; // A
    isKeyPressed[4] = GetAsyncKeyState(0x53) & 0x8000; // S
    isKeyPressed[5] = GetAsyncKeyState(0x44) & 0x8000; // D
    isKeyPressed[6] = GetAsyncKeyState(VK_CAPITAL) & 0x8000; // Caps Lock

    isMousePressed[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000; // LMB
    isMousePressed[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000; // RMB
}

void InputOverlay::RenderKeyboardOverlay(CanvasWrapper canvas)
{
    if (!gameWrapper->IsInGame()) return;

    // Base position for the overlay (top-left corner)
    Vector2F basePos = { 100.0f, 100.0f };
    float keySize = 40.0f;
    float spacing = 5.0f;

    // First row (Q,W,E)
    RenderKey(canvas, Vector2F{ basePos.X, basePos.Y }, "Q", isKeyPressed[0]);
    RenderKey(canvas, Vector2F{ basePos.X + keySize + spacing, basePos.Y }, "W", isKeyPressed[1]);
    RenderKey(canvas, Vector2F{ basePos.X + (keySize + spacing) * 2.0f, basePos.Y }, "E", isKeyPressed[2]);

    // Second row (A,S,D)
    RenderKey(canvas, Vector2F{ basePos.X, basePos.Y + keySize + spacing }, "A", isKeyPressed[3]);
    RenderKey(canvas, Vector2F{ basePos.X + keySize + spacing, basePos.Y + keySize + spacing }, "S", isKeyPressed[4]);
    RenderKey(canvas, Vector2F{ basePos.X + (keySize + spacing) * 2.0f, basePos.Y + keySize + spacing }, "D", isKeyPressed[5]);

    // Caps Lock
    RenderKey(canvas, Vector2F{ basePos.X, basePos.Y + (keySize + spacing) * 2.0f }, "CAPS", isKeyPressed[6]);

    // Mouse buttons
    Vector2F mouseBasePos = { basePos.X + (keySize + spacing) * 3.5f, basePos.Y };
    RenderMouseButton(canvas, mouseBasePos, "LMB", isMousePressed[0]);
    RenderMouseButton(canvas, Vector2F{ mouseBasePos.X, mouseBasePos.Y + keySize + spacing }, "RMB", isMousePressed[1]);
}

void InputOverlay::RenderKey(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed)
{
    float keySize = 40.0f;

    // Draw key outline (black)
    canvas.SetPosition(position);
    canvas.SetColor(0, 0, 0, 255);
    canvas.DrawBox(Vector2F{ keySize, keySize });

    // Draw key fill if pressed
    if (isPressed) {
        canvas.SetPosition(Vector2F{ position.X + 1.0f, position.Y + 1.0f });
        canvas.SetColor(255, 223, 0, 255); // Golden Yellow #FFDF00
        canvas.DrawBox(Vector2F{ keySize - 2.0f, keySize - 2.0f });
    }

    // Draw key label
    canvas.SetColor(0, 0, 0, 255);
    canvas.SetPosition(Vector2F{ position.X + keySize / 2.0f - 5.0f, position.Y + keySize / 2.0f - 5.0f });
    canvas.DrawString(label);
}

void InputOverlay::RenderMouseButton(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed)
{
    float buttonWidth = 40.0f;
    float buttonHeight = 30.0f;

    // Draw button outline (black)
    canvas.SetPosition(position);
    canvas.SetColor(0, 0, 0, 255);
    canvas.DrawBox(Vector2F{ buttonWidth, buttonHeight });

    // Draw button fill if pressed
    if (isPressed) {
        canvas.SetPosition(Vector2F{ position.X + 1.0f, position.Y + 1.0f });
        canvas.SetColor(255, 223, 0, 255); // Golden Yellow #FFDF00
        canvas.DrawBox(Vector2F{ buttonWidth - 2.0f, buttonHeight - 2.0f });
    }

    // Draw button label
    canvas.SetColor(0, 0, 0, 255);
    canvas.SetPosition(Vector2F{ position.X + buttonWidth / 2.0f - 10.0f, position.Y + buttonHeight / 2.0f - 5.0f });
    canvas.DrawString(label);
}