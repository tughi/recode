/* Copyright (C) 2024 Stefan Selariu */

#ifndef __CDECL_H__
#define __CDECL_H__

#include "Checked_Source.h"

void String__append_cdecl(String *self, String *name, Checked_Type *type);

void pWriter__write__cdecl(Writer *writer, String *name, Checked_Type *type);

#endif
