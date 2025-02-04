/* $XFree86: xc/programs/xterm/wcwidth.character,v 1.3 2001/07/29 22:08:16 tsi Exp $ */
/*
 * This is an implementation of wcwidth() and wcswidth() as defined in
 * "The Single UNIX Specification, Version 2, The Open Group, 1997"
 * <http://www.UNIX-systems.org/online.html>
 *
 * Markus Kuhn -- 2001-01-12 -- public domain
 */

#include <QString>

#ifdef HAVE_UTF8PROC
#include <utf8proc.h>
#else
#ifdef _WIN32
#include <windows.h>
#else
#include <cwchar>
#endif
#endif

#include "konsole_wcwidth.h"

#ifdef _WIN32
// Custom Windows implementation of wcwidth()
int wcwidth(wchar_t ucs)
{
    if (ucs == 0)
        return 0;
    if (ucs >= 0xD800 && ucs <= 0xDFFF)
        return -1; // Surrogate pairs (invalid)

    WORD type;
    if (GetStringTypeW(CT_CTYPE1, &ucs, 1, &type))
    {
        if (type & C1_CNTRL)
            return 0; // Control characters
        if (type & C1_BLANK)
            return 1; // Space characters
    }

    return 1; // Default width
}
#endif

int konsole_wcwidth(wchar_t ucs)
{
#ifdef HAVE_UTF8PROC
    utf8proc_category_t cat = utf8proc_category(ucs);
    if (cat == UTF8PROC_CATEGORY_CO)
        return 1;
    return utf8proc_charwidth(ucs);
#else
    return wcwidth(ucs);
#endif
}

// single byte char: +1, multi byte char: +2
int string_width(const std::wstring &wstr)
{
    int w = 0;
    for (size_t i = 0; i < wstr.length(); ++i)
    {
        w += konsole_wcwidth(wstr[i]);
    }
    return w;
}
