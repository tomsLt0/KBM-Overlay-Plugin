#pragma once
#include "pch.h"

constexpr auto plugin_version = "1.0";

class InputOverlay : public BakkesMod::Plugin::BakkesModPlugin {
private:
    bool isKeyPressed[7] = { false }; // For Q,W,E,A,S,D,CapsLock
    bool isMousePressed[2] = { false }; // For LMB, RMB
    bool showOverlay = true;

    void RenderKeyboardOverlay(CanvasWrapper canvas);
    void RenderKey(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed);
    void RenderMouseButton(CanvasWrapper canvas, Vector2F position, const char* label, bool isPressed);
    void HandleInput();

public:
    virtual void onLoad();
    virtual void onUnload();
};

extern std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
