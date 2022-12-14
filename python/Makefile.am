## -*- coding: utf-8 -*-
## Copyright (C) 2010, 2011, 2013-2021 Laboratoire de Recherche
## et Development de l'Epita (LRDE).
## Copyright (C) 2003, 2004  Laboratoire d'Informatique de Paris 6 (LIP6),
## département Systèmes Répartis Coopératifs (SRC), Université Pierre
## et Marie Curie.
##
## This file is part of Spot, a model checking library.
##
## Spot is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
##
## Spot is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
## or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
## License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS = subdir-objects

# __STDC_FORMAT_MACROS is used to avoid an issue with some version of
# <inttypes.h> and <cinttypes>.  Some version of inttypes.h do not
# define macros such as PRIx64 in C++ unless __STDC_FORMAT_MACROS is
# defined.  Including <cintypes> will force the definition of
# __STDC_FORMAT_MACROS before including <inttypes.h>, but if the later
# had already been included before (for instance via the inclusion of
# <Python.h>), it is too late and the PRIx64 will not be defined.
# This issue has been observed on the CentOS6-based build system used
# by conda-forge; it seems to be fixed in more recent distributions,
# where <inttypes.h> define PRIx64 and friends unconditionally.
AM_CPPFLAGS = -I$(PYTHONINC) -I$(top_builddir) -I$(top_srcdir) \
	      $(BUDDY_CPPFLAGS) -lpthread -DSWIG_TYPE_TABLE=spot \
	      -D__STDC_FORMAT_MACROS

SWIGFLAGS = -c++ -python -py3 -O -MD

EXTRA_DIST = buddy.i spot/impl.i spot/ltsmin.i spot/gen.i
nobase_pyexec_PYTHON = \
  spot/__init__.py \
  spot/aux_.py \
  spot/impl.py \
  spot/ltsmin.py \
  spot/gen.py \
  spot/jupyter.py \
  buddy.py
nobase_pyexec_LTLIBRARIES = _buddy@PYEXT@.la spot/_impl@PYEXT@.la \
  spot/_ltsmin@PYEXT@.la spot/_gen@PYEXT@.la


MAINTAINERCLEANFILES = \
  $(srcdir)/spot/impl_wrap.cxx $(srcdir)/spot/impl.py \
  $(srcdir)/spot/ltsmin_wrap.cxx $(srcdir)/spot/ltsmin.py \
  $(srcdir)/spot/gen_wrap.cxx $(srcdir)/spot/gen.py \
  $(srcdir)/buddy_wrap.cxx $(srcdir)/buddy.py

DISTCLEANFILES = \
  spot/$(DEPDIR)/impl_wrap.Pcxx spot/$(DEPDIR)/ltsmin_wrap.Pcxx \
  spot/$(DEPDIR)/gen_wrap.Pcxx $(DEPDIR)/buddy_wrap.Pcxx

## The # am--include-marker files are created by older version
## of Automake when seeing the "# am--include-marker" used here
## for Automake 1.16.
clean-local:
	rm -f '#' am--include-marker

## Automake 1.16 fails to remove the __pycache__/* files.
uninstall-local:
	rm -rf $(DESTDIR)$(pyexecdir)/spot/__pycache__
	rm -f $(DESTDIR)$(pyexecdir)/__pycache__/buddy.*

# This is normally automatically generated by Automake, but we want
# to append our own rules to it.
am__depfiles_remade = ./$(DEPDIR)/buddy_wrap.Plo \
        spot/$(DEPDIR)/gen_wrap.Plo spot/$(DEPDIR)/impl_wrap.Plo \
        spot/$(DEPDIR)/ltsmin_wrap.Plo

## spot

spot__impl@PYEXT@_la_SOURCES = spot/impl_wrap.cxx
spot__impl@PYEXT@_la_LDFLAGS = -avoid-version -module $(SYMBOLIC_LDFLAGS)
spot__impl@PYEXT@_la_LIBADD = $(top_builddir)/spot/libspot.la -lpthread

am__depfiles_remade += ./spot/$(DEPDIR)/impl_wrap.Pcxx
@AMDEP_TRUE@@am__include@ @am__quote@./spot/$(DEPDIR)/impl_wrap.Pcxx@am__quote@ # am--include-marker

${srcdir}/spot/impl_wrap.cxx: spot/impl.i
if AMDEP
	$(SWIG) $(SWIGFLAGS) -I$(srcdir) -I$(top_srcdir) -MF spot/$(DEPDIR)/impl_wrap.TPcxx $(srcdir)/spot/impl.i
	mv spot/$(DEPDIR)/impl_wrap.TPcxx spot/$(DEPDIR)/impl_wrap.Pcxx
else
	$(SWIG) $(SWIGFLAGS) -I$(srcdir) -I$(top_srcdir) $(srcdir)/spot/impl.i
endif
## work around https://github.com/swig/swig/issues/1553
	$(PERL) -pi -e 's/^#define SWIG_Python_CallFunctor.*/#define SWIG_Python_CallFunctor(functor, obj) PyObject_CallFunctionObjArgs(functor, obj, NULL);/' $@

spot/impl.py: spot/impl.i
	$(MAKE) $(AM_MAKEFLAGS) spot/impl_wrap.cxx


## spot-ltsmin

spot__ltsmin@PYEXT@_la_SOURCES = spot/ltsmin_wrap.cxx
spot__ltsmin@PYEXT@_la_LDFLAGS = -avoid-version -module $(SYMBOLIC_LDFLAGS)
spot__ltsmin@PYEXT@_la_LIBADD = $(top_builddir)/spot/libspot.la \
                                $(top_builddir)/spot/ltsmin/libspotltsmin.la \
				-lpthread

am__depfiles_remade += ./spot/$(DEPDIR)/ltsmin_wrap.Pcxx
@AMDEP_TRUE@@am__include@ @am__quote@./spot/$(DEPDIR)/ltsmin_wrap.Pcxx@am__quote@ # am--include-marker

${srcdir}/spot/ltsmin_wrap.cxx: spot/ltsmin.i
if AMDEP
	$(SWIG) $(SWIGFLAGS) -I$(srcdir) -I$(top_srcdir) -MF spot/$(DEPDIR)/ltsmin_wrap.TPcxx $(srcdir)/spot/ltsmin.i
	mv spot/$(DEPDIR)/ltsmin_wrap.TPcxx spot/$(DEPDIR)/ltsmin_wrap.Pcxx
else
	$(SWIG) $(SWIGFLAGS) -I$(srcdir) -I$(top_srcdir) $(srcdir)/spot/ltsmin.i
endif

spot/ltsmin.py: spot/ltsmin.i
	$(MAKE) $(AM_MAKEFLAGS) spot/ltsmin_wrap.cxx


## spot-gen

spot__gen@PYEXT@_la_SOURCES = spot/gen_wrap.cxx
spot__gen@PYEXT@_la_LDFLAGS = -avoid-version -module $(SYMBOLIC_LDFLAGS)
spot__gen@PYEXT@_la_LIBADD = $(top_builddir)/spot/libspot.la \
                             $(top_builddir)/spot/gen/libspotgen.la \
                             -lpthread

am__depfiles_remade += ./spot/$(DEPDIR)/gen_wrap.Pcxx
@AMDEP_TRUE@@am__include@ @am__quote@./spot/$(DEPDIR)/gen_wrap.Pcxx@am__quote@ # am--include-marker

${srcdir}/spot/gen_wrap.cxx: spot/gen.i
if AMDEP
	$(SWIG) $(SWIGFLAGS) -I$(srcdir) -I$(top_srcdir) -MF spot/$(DEPDIR)/gen_wrap.TPcxx $(srcdir)/spot/gen.i
	mv spot/$(DEPDIR)/gen_wrap.TPcxx spot/$(DEPDIR)/gen_wrap.Pcxx
else
	$(SWIG) $(SWIGFLAGS) -I$(srcdir) -I$(top_srcdir) $(srcdir)/spot/gen.i
endif

spot/gen.py: spot/gen.i
	$(MAKE) $(AM_MAKEFLAGS) spot/gen_wrap.cxx


## buddy

_buddy@PYEXT@_la_SOURCES = buddy_wrap.cxx
_buddy@PYEXT@_la_LDFLAGS = -avoid-version -module \
                           $(BUDDY_LDFLAGS) $(SYMBOLIC_LDFLAGS)

am__depfiles_remade += ./$(DEPDIR)/buddy_wrap.Pcxx
@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/buddy_wrap.Pcxx@am__quote@ # am--include-marker

${srcdir}/buddy_wrap.cxx: buddy.i
if AMDEP
	$(SWIG) $(SWIGFLAGS) $(BUDDY_CPPFLAGS) -MF $(DEPDIR)/buddy_wrap.TPcxx $(srcdir)/buddy.i
	mv $(DEPDIR)/buddy_wrap.TPcxx $(DEPDIR)/buddy_wrap.Pcxx
else
	$(SWIG) $(SWIGFLAGS) $(BUDDY_CPPFLAGS) $(srcdir)/buddy.i
endif

buddy.py: buddy.i
	$(MAKE) $(AM_MAKEFLAGS) buddy_wrap.cxx
