#include "pch.h"
#include "InputOverlay.h"

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

BAKKESMOD_PLUGIN(InputOverlay, "Keyboard and Mouse Input Overlay", plugin_version, PLUGINTYPE_FREEPLAY)

void InputOverlay::onLoad()
{
    _globalCvarManager = cvarManager;

    // Register the draw callback
    gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
        HandleInput(); // Move input handling to the draw callback
        if (gameWrapper->IsInGame()) {
            RenderKeyboardOverlay(canvas);
        }
        });

    // Log that plugin has loaded
    cvarManager->log("Keyboard Overlay Plugin has loaded!");
}

void InputOverlay::onUnload()
{
    cvarManager->log("Keyboard Overlay Plugin has unloaded!");
}

void InputOverlay::HandleInput()
{
    // Add debug logging to verify input detection
    if (GetAsyncKeyState(0x51) & 0x8000) { // Q key
        cvarManager->log("Q key pressed");
    }

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
    // Base position for the overlay (fixed position)
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

    if (isPressed) {
        // Golden yellow fill when pressed
        canvas.SetColor(255, 223, 0, 255); // #FFDF00
        canvas.SetPosition(position);
        canvas.FillBox(Vector2F{ keySize, keySize });
    }

    // Always draw black outline
    canvas.SetColor(0, 0, 0, 255);
    canvas.SetPosition(position);
    canvas.DrawBox(Vector2F{ keySize, keySize });

    // Draw the label
    canvas.SetPosition(Vector2F{ position.X + keySize / 2.0f - 5.0f, position.Y + keySize / 2.0f - 5.0f });
    if (isPressed) {
        canvas.SetColor(0, 0, 0, 255); // Black text when pressed
    }
    else {
        canvas.SetColor(255, 255, 255, 255); // White text when not pressed
    }
    canvas.DrawString(label);
}

void InputOverlay::RenderMouseButton(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed)
{
    float buttonWidth = 40.0f;
    float buttonHeight = 30.0f;

    if (isPressed) {
        // Golden yellow fill when pressed
        canvas.SetColor(255, 223, 0, 255); // #FFDF00
        canvas.SetPosition(position);
        canvas.FillBox(Vector2F{ buttonWidth, buttonHeight });
    }

    // Always draw black outline
    canvas.SetColor(0, 0, 0, 255);
    canvas.SetPosition(position);
    canvas.DrawBox(Vector2F{ buttonWidth, buttonHeight });

    // Draw the label
    canvas.SetPosition(Vector2F{ position.X + buttonWidth / 2.0f - 10.0f, position.Y + buttonHeight / 2.0f - 5.0f });
    if (isPressed) {
        canvas.SetColor(0, 0, 0, 255); // Black text when pressed
    }
    else {
        canvas.SetColor(255, 255, 255, 255); // White text when not pressed
    }
    canvas.DrawString(label);
}
