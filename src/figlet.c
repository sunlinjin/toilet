/*
 *  TOIlet        The Other Implementation’s letters
 *  Copyright (c) 2006 Sam Hocevar <sam@hocevar.net>
 *                All Rights Reserved
 *
 *  $Id$
 *
 *  This program is free software. It comes without any warranty, to
 *  the extent permitted by applicable law. You can redistribute it
 *  and/or modify it under the terms of the Do What The Fuck You Want
 *  To Public License, Version 2, as published by Sam Hocevar. See
 *  http://sam.zoy.org/wtfpl/COPYING for more details.
 */

/*
 * This file contains functions for handling FIGlet fonts.
 */

#include "config.h"

#if defined(HAVE_INTTYPES_H)
#   include <inttypes.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <caca.h>

#include "toilet.h"
#include "render.h"

#define STD_GLYPHS (127 - 32)
#define EXT_GLYPHS (STD_GLYPHS + 7)

static int feed_figlet(context_t *, uint32_t, uint32_t);
static int flush_figlet(context_t *);
static int end_figlet(context_t *);

int init_figlet(context_t *cx)
{
    char path[2048];

    snprintf(path, 2047, "%s/%s", cx->dir, cx->font);
    if(caca_canvas_set_figfont(cx->cv, path))
        return -1;

    cx->feed = feed_figlet;
    cx->flush = flush_figlet;
    cx->end = end_figlet;

    return 0;
}

static int feed_figlet(context_t *cx, uint32_t ch, uint32_t attr)
{
    return caca_put_figchar(cx->cv, ch);
}

static int flush_figlet(context_t *cx)
{
    int ret = caca_flush_figlet(cx->cv);
    cx->torender = cx->cv;
    cx->cv = caca_create_canvas(0, 0);
    return ret;
}

static int end_figlet(context_t *cx)
{
    return caca_canvas_set_figfont(cx->cv, NULL);
}

