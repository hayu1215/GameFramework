#include"Log.h"
#include<Windows.h>

namespace debug {

#ifdef _DEBUG
void Log(const std::string& msg) {
    std::string msgStr = "[DebugLog] " + msg + "\n";
    OutputDebugString(msgStr.c_str());
}
#else
void Log(const std::string& msg) {}
#endif

}