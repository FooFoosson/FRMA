#ifdef _WIN32
#include <windows.h>

static void createDirectory(const char *path) { CreateDirectoryA(path); }

#endif
