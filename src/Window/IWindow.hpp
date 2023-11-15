#pragma once

template<typename T>
class IWindow {
public:
    virtual ~IWindow() = default;

    T* nativeHandle() const {
        return m_window;
    }

    void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) {
        clearImpl(r, g, b, a);
    }

protected:
    virtual void clearImpl(float r, float g, float b, float a) = 0;

    T* m_window;
};
