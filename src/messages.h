#pragma once

#ifndef MESSAGES_H
#define MESSAGES_H

namespace Messages
{
  const char *ERR_DLL_NOT_LOADED = "DLL not loaded";
  const char *ERR_DLL_ALREADY_LOADED = "DLL already loaded";
  const char *ERR_DLL_NOT_UNLOADED = "DLL not unloaded";
  const char *ERR_DLL_NOT_FOUND = "DLL for 'NexusDb' not found";
  const char *ERR_FUNCTION_NOT_FOUND = "Error Loading Function";

  const char *ERR_WRONG_ARGUMENTS = "Wrong arguments";
  const char *ERR_WRONG_ARGUMENTS_COUNT = "Wrong Number of arguments";
} // namespace Messages

#endif // MESSAGES_H
