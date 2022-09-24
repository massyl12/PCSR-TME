#pragma once
#include <cstddef>

#include "String.h"

namespace pr {
int compare(const char *s, const char *s1);
size_t length(const char *);
char *newcopy(const char *);
char *newcpy(const char *s);
}  // namespace pr
