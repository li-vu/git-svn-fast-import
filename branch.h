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

#ifndef GIT_SVN_FAST_IMPORT_BRANCH_H_
#define GIT_SVN_FAST_IMPORT_BRANCH_H_

#include "tree.h"
#include <apr_pools.h>
#include <apr_tables.h>
#include <svn_io.h>

typedef struct
{
    const char *refname;
    const char *path;
    svn_boolean_t dirty;
} branch_t;

// Tests if path is branch's root
svn_boolean_t
branch_path_is_root(const branch_t *b, const char *path);

const char *
branch_refname_from_path(const char *path, apr_pool_t *pool);

typedef struct
{
    apr_pool_t *pool;
    tree_t *tree;
    // Branch and tag path prefixes.
    tree_t *pfx;
    apr_hash_t *refnames;
} branch_storage_t;

// Create new branch storage.
branch_storage_t *
branch_storage_create(apr_pool_t *pool);

void
branch_storage_add_prefix(branch_storage_t *bs, const char *pfx, svn_boolean_t is_tag, apr_pool_t *pool);

// Add new branch reference name and path.
branch_t *
branch_storage_add_branch(branch_storage_t *bs, const char *ref, const char *path, apr_pool_t *pool);

// Lookup a branch by path.
branch_t *
branch_storage_lookup_path(branch_storage_t *bs, const char *path, apr_pool_t *pool);

// Lookup a branch by refname.
branch_t *
branch_storage_lookup_refname(branch_storage_t *bs, const char *refname);

svn_error_t *
branch_storage_dump(branch_storage_t *bs, svn_stream_t *dst, apr_pool_t *pool);

svn_error_t *
branch_storage_dump_path(branch_storage_t *bs, const char *path, apr_pool_t *pool);

svn_error_t *
branch_storage_load(branch_storage_t *bs, svn_stream_t *src, apr_pool_t *pool);

svn_error_t *
branch_storage_load_path(branch_storage_t *bs, const char *path, apr_pool_t *pool);

#endif // GIT_SVN_FAST_IMPORT_BRANCH_H_
