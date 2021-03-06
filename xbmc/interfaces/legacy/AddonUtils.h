/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

/*
 * addon.h
 *
 *  Created on: Aug 21, 2010
 *      Author: jim
 */

//#define ENABLE_XBMC_TRACE_API

#include "threads/SingleLock.h"

#include <memory>
#include <vector>

#ifdef TARGET_WINDOWS
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

/**
 * This file contains the public definitions for the Addon api. It's meant to be used
 * by those writing language bindings.
 */

namespace XBMCAddon
{
class LanguageHook;
}

namespace XBMCAddonUtils
{
  class GuiLock
  {
  public:
    GuiLock(XBMCAddon::LanguageHook* languageHook, bool offScreen);
    ~GuiLock();

  protected:
    XBMCAddon::LanguageHook* m_languageHook = nullptr;
    bool m_offScreen = false;
  };

  class InvertSingleLockGuard
  {
    CSingleLock& lock;
  public:
    explicit InvertSingleLockGuard(CSingleLock& _lock) : lock(_lock) { lock.Leave(); }
    ~InvertSingleLockGuard() { lock.Enter(); }
  };


  /*
   * Looks in references.xml for image name
   * If none exist return default image name
   */
  const char *getDefaultImage(char* cControlType, char* cTextureType);

#ifdef ENABLE_XBMC_TRACE_API
  class TraceGuard
  {
    const char* function;
  public:
    TraceGuard* parent;
    int depth;

    const char* getSpaces();

    explicit TraceGuard(const char* _function);
    TraceGuard();
    ~TraceGuard();
  };
#endif
}

#ifdef ENABLE_XBMC_TRACE_API
#define XBMC_TRACE XBMCAddonUtils::TraceGuard _tg(__PRETTY_FUNCTION__)
#else
#define XBMC_TRACE
#endif


