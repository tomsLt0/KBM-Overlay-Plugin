// InputOverlay.h
#pragma once
#include "pch.h"

class InputOverlay : public BakkesMod::Plugin::BakkesModPlugin {
private:
    bool isKeyPressed[7] = { false }; // For Q,W,E,A,S,D,CapsLock
    bool isMousePressed[2] = { false }; // For LMB, RMB

    void RenderKeyboardOverlay(CanvasWrapper canvas);
    void RenderKey(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed);
    void RenderMouseButton(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed);
    void HandleInput();

public:
    virtual void onLoad();
    virtual void onUnload();
};