/* Copyright (C) 2014-2015 by Maxim Bublis <b@codemonkey.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GIT_SVN_FAST_IMPORT_OPTIONS_H_
#define GIT_SVN_FAST_IMPORT_OPTIONS_H_

#include "error.h"
#include "tree.h"

#include <apr_pools.h>

typedef struct
{
    int verbose;
    // Trunk path prefix.
    const char *trunk;
    // Branches path prefixes.
    tree_t *branches;
    // Tags path prefixes.
    tree_t *tags;
    // Ignore path prefixes.
    tree_t *ignore;
    // Path to a file containing mapping of
    // Subversion committers to Git authors.
    const char *authors;
    // Path to a file where marks should be exported.
    const char *export_marks;
} git_svn_options_t;

git_svn_status_t
git_svn_parse_options(git_svn_options_t *options, int argc, const char **argv, apr_pool_t *pool);

#endif // GIT_SVN_FAST_IMPORT_OPTIONS_H_
