#include"Judge.h"
#include<Windows.h>
#include<sstream>

//#ifndef NDEBUG
//#define assert_msg(msg,expr)
//#else
//#define assert_msg(msg,expr)\
//    internal::assertMsg(expr,__FILE__,__LINE__,msg)
//#endif // !NDEBUG

namespace internal 
{

void AssertMsg(bool expr, const char* file, int line, const char* msg)
{
	if (expr) return;
	std::stringstream ss;
	ss << "ERROR : Assert Faild\n" << msg << "\n" << file << "(" + line << ")\n";
	std::string str = ss.str();
	OutputDebugString(str.c_str());
	abort();
}

}

namespace utility
{

void DebugLog(const std::string &msg)
{
	std::string msgStr = msg + "\n";
	OutputDebugString(msgStr.c_str());
}

bool CheckError(int target, const std::string &msg)
{
	if (target < 0)
	{
		DebugLog("ERROR : " + msg);
		return true;
	}
	return false;
}

bool CheckNull(const void *targetPtr, const std::string &msg)
{
	if (targetPtr == nullptr)
	{
		DebugLog("NULL : " + msg);
		return true;
	}
	return false;
}

}