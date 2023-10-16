#pragma once

class IWindow {
public:
    virtual ~IWindow() = default;
    virtual void UpdateFpsCounter(float dt) = 0;
    virtual void Clear() = 0;
    virtual void SwapBuffer() = 0;
};
