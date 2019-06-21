#pragma once

#include<type_traits>
#include<string>

#ifndef NDEBUG
#define assert_msg(msg,expr)\
    internal::assertMsg(expr,__FILE__,__LINE__,msg)
#else
#define assert_msg(msg,expr)
#endif // !NDEBUG

namespace internal 
{
	void assertMsg(bool expr, const char* file, int line, const char* msg);
}

namespace utility 
{
#ifdef _DEBUG
	void debugLog(const std::string&);
#endif

	bool checkError(int, const std::string&);
	bool checkNull(const void*, const std::string&);

	template<class Base, class T>
	bool judgeBase()
	{
		return std::is_base_of<Base, T>::value;
	};
}