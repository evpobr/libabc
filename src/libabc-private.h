/*
  libabc - something with abc

  Copyright (C) 2011 Someone <someone@example.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#ifndef _LIBABC_PRIVATE_H_
#define _LIBABC_PRIVATE_H_

#include <stdbool.h>
#include <stdarg.h>
#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#else
#define	LOG_EMERG   0 /* system is unusable */
#define	LOG_ALERT   1 /* action must be taken immediately */
#define	LOG_CRIT    2 /* critical conditions */
#define	LOG_ERR     3 /* error conditions */
#define	LOG_WARNING 4 /* warning conditions */
#define	LOG_NOTICE	5 /* normal but significant condition */
#define	LOG_INFO    6 /* informational */
#define	LOG_DEBUG   7 /* debug-level messages */
#endif

#include <abc/libabc.h>

#ifdef __GNUC__
static inline void __attribute__((always_inline, format(printf, 2, 3)))
#else
static inline void
#endif
abc_log_null(struct abc_ctx *ctx, const char *format, ...) {}

#define abc_log_cond(ctx, prio, ...) \
  do { \
    if (abc_get_log_priority(ctx) >= prio) \
      abc_log(ctx, prio, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); \
  } while (0)

#ifdef ENABLE_LOGGING
#  ifdef ENABLE_DEBUG
#    define dbg(ctx, ...) abc_log_cond(ctx, LOG_DEBUG, __VA_ARGS__)
#  else
#    define dbg(ctx, ...) abc_log_null(ctx, __VA_ARGS__)
#  endif
#  define info(ctx, ...) abc_log_cond(ctx, LOG_INFO, __VA_ARGS__)
#  define err(ctx, ...) abc_log_cond(ctx, LOG_ERR, __VA_ARGS__)
#else
#  define dbg(ctx, ...) abc_log_null(ctx, __VA_ARGS__)
#  define info(ctx, ...) abc_log_null(ctx, __VA_ARGS__g)
#  define err(ctx, ...) abc_log_null(ctx, __VA_ARGS__)
#endif

#ifndef HAVE_SECURE_GETENV
#  ifdef HAVE___SECURE_GETENV
#    define secure_getenv __secure_getenv
#  else
#    define secure_getenv getenv
#  endif
#endif

void abc_log(struct abc_ctx *ctx,
           int priority, const char *file, int line, const char *fn,
           const char *format, ...)
           __attribute__((format(printf, 6, 7)));

#endif
