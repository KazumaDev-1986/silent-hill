#include "includes/error.h"
#include "includes/raylib.h"
#include <errno.h>
#include <string.h>

__AC__ void printError(const char *description) {
  TraceLog(LOG_ERROR, TextFormat("%s: %s", description, strerror(errno)));
}
