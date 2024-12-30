#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"

#include "version.h"

class InputOverlay : public BakkesMod::Plugin::BakkesModPlugin
{
private:
    bool isKeyPressed[7] = { false }; // For Q,W,E,A,S,D,CapsLock
    bool isMousePressed[2] = { false }; // For LMB, RMB

    // Rendering functions
    void RenderKeyboardOverlay(CanvasWrapper canvas);
    void RenderKey(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed, float width);
    void RenderMouseButton(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed);
    void HandleInput();

public:
    void onLoad() override;
    void onUnload() override;
};
