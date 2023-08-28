#include <libNexusDb.h>
#include <string>
#include <stdlib.h>
#include <helper.h>

void hNxStr16::destroy(hNxStr16Ptr str)
{
  if (str != NULL)
  {
    if (str->str != NULL)
    {
      free(str->str);
    }
    free(str);
  }
}

char16_t *hNxStr16::toChar16()
{
  char16_t *str = (char16_t *)malloc(sizeof(char16_t) * (len + 1));
  for (size_t i = 0; i < len; i++)
  {
    str[i] = this->str[i];
  }
  str[len] = '\0';
  return str;
}

char *hNxStr16::toChar()
{
  char *str = (char *)malloc(sizeof(char) * (len + 1));
  for (size_t i = 0; i < len; i++)
  {
    str[i] = (char)this->str[i];
  }
  str[len] = '\0';
  return str;
}

hNxStr16Ptr hNxStr16::fromString(const char *str)
{
  hNxStr16Ptr hStr = (hNxStr16Ptr)malloc(sizeof(hNxStr16));
  hStr->len = strlen(str);
  hStr->str = (char16_t *)malloc(sizeof(char16_t) * (hStr->len + 1));
  for (size_t i = 0; i < hStr->len; i++)
  {
    hStr->str[i] = (char16_t)str[i];
  }
  hStr->str[hStr->len] = '\0';
  return hStr;
}
