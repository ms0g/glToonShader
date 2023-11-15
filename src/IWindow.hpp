#pragma once

template<typename T>
class IWindow {
public:
    virtual ~IWindow() = default;

    T* NativeHandle() const {
        return m_window;
    }

    void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) {
        ClearImpl(r, g, b, a);
    }

    virtual void SwapBuffer() = 0;

protected:
    virtual void ClearImpl(float r, float g, float b, float a) = 0;

    T* m_window;
};
