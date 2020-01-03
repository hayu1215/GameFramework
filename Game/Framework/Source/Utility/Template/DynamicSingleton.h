#pragma once

template<class T>
class DynamicSingleton
{
protected:
	DynamicSingleton() {}
	virtual ~DynamicSingleton() {}

public:
	static T& Instance() 
	{
		return *instance;
	}

	static void Create() 
	{
		if (!instance) instance = new T();
	}

	static void Destroy() 
	{
		delete instance;
		instance = nullptr;
	}

	DynamicSingleton(const DynamicSingleton&) = delete;
	DynamicSingleton& operator=(const DynamicSingleton&) = delete;
	DynamicSingleton(DynamicSingleton&&) = delete;
	DynamicSingleton& operator=(DynamicSingleton&&) = delete;

private:
	static T* instance;
};

template<class T>
T* DynamicSingleton<T>::instance = nullptr;