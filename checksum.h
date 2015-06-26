/* Copyright (C) 2015 by Maxim Bublis <b@codemonkey.ru>
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

#ifndef SVN_FAST_EXPORT_CHECKSUM_H_
#define SVN_FAST_EXPORT_CHECKSUM_H_

#include "tree.h"
#include <svn_checksum.h>
#include <svn_fs.h>

// Abstract type for checksum cache.
typedef struct checksum_cache_t checksum_cache_t;

// Create new checksum cache.
checksum_cache_t *
checksum_cache_create(apr_pool_t *pool);

// Returns a Git checksum for SVN checksum.
svn_checksum_t *
checksum_cache_get(checksum_cache_t *c,
                   const svn_checksum_t *svn_checksum);

// Sets a Git checksum for SVN checksum.
void
checksum_cache_set(checksum_cache_t *c,
                   const svn_checksum_t *svn_checksum,
                   const svn_checksum_t *git_checksum);

svn_error_t *
set_content_checksum(svn_checksum_t **checksum,
                     svn_stream_t *output,
                     checksum_cache_t *cache,
                     svn_fs_root_t *root,
                     const char *path,
                     apr_pool_t *pool);

svn_error_t *
set_tree_checksum(svn_checksum_t **checksum,
                  apr_array_header_t **entries,
                  svn_stream_t *output,
                  checksum_cache_t *cache,
                  svn_fs_root_t *root,
                  const char *path,
                  const char *root_path,
                  tree_t *ignores,
                  apr_pool_t *pool);

#endif // SVN_FAST_EXPORT_CHECKSUM_H_
