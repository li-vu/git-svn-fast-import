/* Copyright (C) 2014 by Maxim Bublis <b@codemonkey.ru>
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

#include "dump.h"

svn_error_t *
dump_revision_begin(svn_stream_t *out, revision_t *rev, apr_pool_t *pool)
{
    SVN_ERR(svn_stream_printf(out, pool, "commit refs/heads/%s\n", rev->branch->name));
    SVN_ERR(svn_stream_printf(out, pool, "mark :%d\n", rev->mark));
    SVN_ERR(svn_stream_printf(out, pool, "committer %s <%s@local> %"PRId64" +0000\n",
                              rev->author, rev->author, rev->timestamp));
    SVN_ERR(svn_stream_printf(out, pool, "data %ld\n", strlen(rev->message)));
    SVN_ERR(svn_stream_printf(out, pool, "%s\n", rev->message));

    if (rev->copyfrom != NULL) {
        SVN_ERR(svn_stream_printf(out, pool, "from :%d\n", rev->copyfrom->mark));
    }

    return SVN_NO_ERROR;
}

svn_error_t *
dump_revision_end(svn_stream_t *out, revision_t *rev, apr_pool_t *pool)
{
    SVN_ERR(svn_stream_printf(out, pool, "progress Imported revision %d\n", rev->revnum));

    return SVN_NO_ERROR;
}

svn_error_t *
dump_revision_noop(svn_stream_t *out, revision_t *rev, apr_pool_t *pool)
{
    SVN_ERR(svn_stream_printf(out, pool, "progress Skipped revision %d\n", rev->revnum));

    return SVN_NO_ERROR;
}

svn_error_t *
dump_branch_found(svn_stream_t *out, branch_t *branch, apr_pool_t *pool)
{
    SVN_ERR(svn_stream_printf(out, pool, "progress Found branch at %s\n", branch->path));

    return SVN_NO_ERROR;
}

static svn_error_t *
node_modify(svn_stream_t *out, node_t *node, apr_pool_t *pool)
{
    if (node->kind == KIND_DIR) {
        return SVN_NO_ERROR;
    }
    return svn_stream_printf(out, pool, "M %o :%d \"%s\"\n", node->mode, node->blob->mark, node->path);
}

static svn_error_t *
node_delete(svn_stream_t *out, node_t *node, apr_pool_t *pool)
{
    return svn_stream_printf(out, pool, "D \"%s\"\n", node->path);
}

static svn_error_t *
node_replace(svn_stream_t *out, node_t *node, apr_pool_t *pool)
{
    SVN_ERR(node_delete(out, node, pool));
    return node_modify(out, node, pool);
}

svn_error_t *
dump_node(svn_stream_t *out, node_t *node, apr_pool_t *pool)
{
    switch (node->action) {
    case ACTION_ADD:
    case ACTION_CHANGE:
        return node_modify(out, node, pool);
    case ACTION_DELETE:
        return node_delete(out, node, pool);
    case ACTION_REPLACE:
        return node_replace(out, node, pool);
    default:
        return SVN_NO_ERROR;
    }
}

svn_error_t *
dump_blob_header(svn_stream_t *out, blob_t *blob, apr_pool_t *pool)
{
    SVN_ERR(svn_stream_printf(out, pool, "blob\n"));
    SVN_ERR(svn_stream_printf(out, pool, "mark :%d\n", blob->mark));
    SVN_ERR(svn_stream_printf(out, pool, "data %ld\n", blob->length));

    return SVN_NO_ERROR;
}
