/**
 * @file debug.c
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-02-28
 *
 * MIT License
 *
 * Copyright 2022 IotaHydrae(writeforever@foxmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "lib/ringbuffer.h"
#include "common/init.h"
// #include "common/types.h"

/* integer equivalents of KERN_<LEVEL> */
#define LOGLEVEL_SCHED      -2  /* Deferred messages from sched code are set to this special level */
#define LOGLEVEL_DEFAULT    -1  /* default (or last) loglevel */
#define LOGLEVEL_EMERG      0   /* system is unusable */
#define LOGLEVEL_ALERT      1   /* action must be taken immediately */
#define LOGLEVEL_CRIT       2   /* critical conditions */
#define LOGLEVEL_ERR        3   /* error conditions */
#define LOGLEVEL_WARNING    4   /* warning conditions */
#define LOGLEVEL_NOTICE     5   /* normal but significant condition */
#define LOGLEVEL_INFO       6   /* informational */
#define LOGLEVEL_DEBUG      7   /* debug-level messages */

enum log_flags {
    LOG_NOCONS  = 1,    /* already flushed, do not print to console */
    LOG_NEWLINE = 2,    /* text ended with a newline */
    LOG_PREFIX  = 4,    /* text started with a prefix */
    LOG_CONT    = 8,    /* text is a fragment of a continuation line */
};

// struct printk_log {
//  u64 ts_nsec;        /* timestamp in nanoseconds */
//  u16 len;        /* length of entire record */
//  u16 text_len;       /* length of text buffer */
//  u16 dict_len;       /* length of dictionary buffer */
//  u8 facility;        /* syslog facility */
//  u8 flags:5;     /* internal record flags */
//  u8 level:3;     /* syslog level */
// };

#define PREFIX_MAX      32
#define LOG_LINE_MAX    (1024 - PREFIX_MAX)

#define LOG_LEVEL(v)        ((v) & 0x07)
#define LOG_FACILITY(v)     ((v) >> 3 & 0xff)

#define LOG_BUF_SHIFT    10

// #define LOG_ALIGN __alignof__(struct printk_log)
#define __LOG_BUF_LEN (1 << LOG_BUF_SHIFT)
static char __log_buf[__LOG_BUF_LEN]; // __attribute__((align(LOG_ALIGN)));
static char *log_buf = __log_buf;
static unsigned int log_buf_len = __LOG_BUF_LEN;

static struct ring_buffer_t rb_log;

// static int log_store(int facility, int level,
//           enum log_flags flags, u64 ts_nsec,
//           const char *dict, u16 dict_len,
//           const char *text, u16 text_len)
// {

// }

// static int log_output(int facility, int level, enum log_flags lflags, const char *dict, int dictlen, char *text, size_t text_len)
// {


//  /* Skip empty continuation lines that couldn't be added - they just flush */
//  if (!text_len && (lflags & LOG_CONT))
//      return 0;

//  /* If it doesn't end in a newline, try to buffer the current line */
//  // if (!(lflags & LOG_NEWLINE)) {
//  //  if (cont_add(facility, level, lflags, text, text_len))
//  //      return text_len;
//  // }

//  /* Store it in the record log */
//  return log_store(facility, level, lflags, 0, dict, dictlen, text, text_len);
// }

static int vprintk_store(int facility, int level,
                         const char *dict, int dictlen,
                         const char *fmt, va_list args)
{
    static char textbuf[LOG_LINE_MAX];
    char *text = textbuf;
    int text_len;
    enum log_flags lflags = 0;

    /*
     * The printf needs to come first; we need the syslog
     * prefix which might be passed-in as a parameter.
     */
    text_len = vsnprintf(text, sizeof(textbuf), fmt, args);

    /* mark and strip a trailing newline */
    // if (text_len && text[text_len - 1] == '\n') {
    //     text_len--;
    //     lflags |= LOG_NEWLINE;
    // }

    for (int i = 0; i < text_len; i++)
        ring_buffer_queue(&rb_log, textbuf[i]);
    /* strip kernel syslog prefix and extract log level or control flags */
    // if (facility == 0) {
    //  int kern_level;

    //  while ((kern_level = printk_get_level(text)) != 0) {
    //      switch (kern_level) {
    //      case '0' ... '7':
    //          if (level == LOGLEVEL_DEFAULT)
    //              level = kern_level - '0';
    //          /* fallthrough */
    //      case 'd':   /* KERN_DEFAULT */
    //          lflags |= LOG_PREFIX;
    //          break;
    //      case 'c':   /* KERN_CONT */
    //          lflags |= LOG_CONT;
    //      }

    //      text_len -= 2;
    //      text += 2;
    //  }
    // }

    if (dict)
        lflags |= LOG_PREFIX | LOG_NEWLINE;

}

static int vprintk_emit(int facility, int level,
                        const char *dict, int dictlen,
                        const char *fmt, va_list args)
{
    int printed_len;

    printed_len = vprintk_store(facility, level, dict, dictlen, fmt, args);

    return printed_len;
}

static int vprintk_default(const char *fmt, va_list args)
{
    int r;

    r = vprintk_emit(0, LOGLEVEL_DEFAULT, NULL, 0, fmt, args);

    return r;
}

int log_buf_flush(void)
{
    char tmp;
    for (int cnt = 0; ring_buffer_dequeue(&rb_log, &tmp) > 0; cnt ++);
}

int dump_kmsg(bool flush)
{
    char *tmp = __log_buf;

    while(*tmp) {
        if (*tmp == '\n') {
            printf("\n");
            tmp++;
            continue;
        }

        printf("%c", *tmp);
        tmp++;
    }
    // if (ring_buffer_is_empty(&rb_log))
    //     return 0;

    // char tmp;
    // int cnt = 0;
    // for (; ring_buffer_dequeue(&rb_log, &tmp) > 0; cnt ++)
    //     printf("%c", tmp);

    // if (flush)
    //     log_buf_flush();

    return 0;
}

int printk(const char *fmt, ...)
{
    va_list args;
    int r;

    va_start(args, fmt);
    r = vprintk_default(fmt, args);
    va_end(args);

    return r;
}

int printk_late_init(void)
{
    int rc;

    ring_buffer_init(&rb_log, __log_buf, __LOG_BUF_LEN);

    return 0;
}

static CORE_INITCALL(printk_init)
{
    int rc;
    ring_buffer_init(&rb_log, __log_buf, __LOG_BUF_LEN);

    printk("%s, initialzing printk ...\n", __func__);

    return 0;
}

// arch_initcall(printk_init);
