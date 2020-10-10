#pragma once

#include<type_traits>
#include<string>

#ifndef NDEBUG
#define assert_msg(msg,expr)\
    internal::AssertMsg(expr,__FILE__,__LINE__,msg)
#else
#define assert_msg(msg,expr)
#endif // !NDEBUG

namespace internal {

void AssertMsg(bool expr, const char* file, int line, const char* msg);

}

namespace utility {

#ifdef _DEBUG
void DebugLog(const std::string&);
#endif

bool CheckError(int, const std::string&);
bool CheckNull(const void*, const std::string&);

template<class Base, class T>
bool JudgeBase() {
    return std::is_base_of<Base, T>::value;
};

}