#ifdef __gnu_linux__
#include <sys/stat.h>
#include <sys/types.h>

static void createDirectory(const char *path) { mkdir(path, 0770); }

#endif
