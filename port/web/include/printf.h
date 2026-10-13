// Web builds: stands in for the platform <printf.h> that NL/nlPrint.h pulls in
// for va_list.
#pragma once
#include <stdarg.h>
#ifndef __va_list
#define __va_list va_list
#endif
