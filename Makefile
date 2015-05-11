# Copyright (C) 2014-2015 by Maxim Bublis <b@codemonkey.ru>
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

CC ?= cc
RM = rm -f
CFLAGS = -g -O2 -Wall -std=c99
CPPFLAGS =
LDFLAGS =
EXTLIBS = -lapr-1 -lsvn_subr-1 -lsvn_repos-1

-include config.mak
include uname.mak

APR_INCLUDES := $(shell apr-1-config --includes)
APR_CPPFLAGS := $(shell apr-1-config --cppflags)
CPPFLAGS +=$(APR_INCLUDES) $(APR_CPPFLAGS)

GIT_SVN_FAST_IMPORT := git-svn-fast-import
GIT_SVN_VERIFY_IMPORT := git-svn-verify-import
SVN_FAST_EXPORT := svn-fast-export
OBJECTS := svn-fast-export.o \
	author.o \
	backend.o \
	blob.o \
	branch.o \
	commit.o \
	error.o \
	node.o \
	options.o \
	parse.o \
	revision.o \
	symlink.o \
	tree.o \
	utils.o

all: $(GIT_SVN_FAST_IMPORT) $(GIT_SVN_VERIFY_IMPORT) $(SVN_FAST_EXPORT)

$(GIT_SVN_FAST_IMPORT): git-svn-fast-import.sh

$(GIT_SVN_VERIFY_IMPORT): git-svn-verify-import.py
	cat git-svn-verify-import.py > git-svn-verify-import
	chmod a+x git-svn-verify-import

$(SVN_FAST_EXPORT): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(EXTLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

test: all
	$(MAKE) -C t all

clean:
	$(RM) $(GIT_SVN_FAST_IMPORT) $(GIT_SVN_VERIFY_IMPORT) $(SVN_FAST_EXPORT) $(OBJECTS)

.PHONY: all clean
