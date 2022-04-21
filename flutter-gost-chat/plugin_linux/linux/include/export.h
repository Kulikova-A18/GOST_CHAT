/*#ifdef cplusplus //If it is a C++ language
#define LIBRARY_API extern "C" __attribute((visibility ("default"))) attribute((used)) 
#else
#define LIBRARY_API extern attribute((visibility ("default")))
#endif*/

#define LIBRARY_API extern "C" __attribute__((visibility("default"))) __attribute__((used))