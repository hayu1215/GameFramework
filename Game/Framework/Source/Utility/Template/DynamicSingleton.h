#pragma once

template<class T>
class DynamicSingleton {
protected:
    DynamicSingleton() {}
    virtual ~DynamicSingleton() {}

public:
    static T& Instance() {
        return *Instance;
    }

    static void Create() {
        if (!Instance) Instance = new T();
    }

    static void Destroy() {
        delete Instance;
        Instance = nullptr;
    }

    DynamicSingleton(const DynamicSingleton&) = delete;
    DynamicSingleton& operator=(const DynamicSingleton&) = delete;
    DynamicSingleton(DynamicSingleton&&) = delete;
    DynamicSingleton& operator=(DynamicSingleton&&) = delete;

private:
    static T* Instance;
};

template<class T>
T* DynamicSingleton<T>::Instance = nullptr;