/* This file is part of the KDE libraries

    Copyright (C) 2003,2007 Oswald Buddenhagen <ossi@kde.org>

    Rewritten for QT4 by e_k <e_k at users.sourceforge.net>, Copyright (C)2008

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef kpty_p_h
#define kpty_p_h

#include "kpty.h"

#include <QByteArray>

#ifdef _WIN32
class WPtyPrivate
{
public:
    Q_DECLARE_PUBLIC(WPty)

    WPtyPrivate(WPty *parent);
    virtual ~WPtyPrivate();

    HPCON hPC;              // Handle to the ConPTY instance.
    HANDLE hPipeInputWrite; // Parent's write handle to ConPTY input.
    HANDLE hPipeOutputRead; // Parent's read handle from ConPTY output.
    PROCESS_INFORMATION pi; // Information about the spawned process.

    bool created;
    bool processSpawned;

    WPty *q_ptr;
};
#else
class KPtyPrivate
{
public:
    Q_DECLARE_PUBLIC(KPty)

    KPtyPrivate(KPty *parent);
    virtual ~KPtyPrivate();

    bool chownpty(bool grant);

    int masterFd;
    int slaveFd;
    bool ownMaster : 1;

    QByteArray ttyName;

    KPty *q_ptr;
};
#endif

#endif
