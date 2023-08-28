#pragma once

#ifndef HELPER_H
#define HELPER_H

#include <libNexusDb.h>

struct hNxStr16
{
  char16_t *str;
  size_t len;

  static hNxStr16 *fromString(const char *str);

  static void destroy(hNxStr16 *str);

  char16_t *toChar16();

  char *toChar();
};
typedef hNxStr16 *hNxStr16Ptr;

#endif // HELPER_H
