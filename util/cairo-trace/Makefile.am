bin_SCRIPTS = cairo-trace
lib_LTLIBRARIES = cairo-trace.la

AM_CPPFLAGS = -I$(top_srcdir)/src \
	      -I$(top_builddir)/src

cairo_trace_la_SOURCES = \
			 lookup-symbol.c \
			 lookup-symbol.h \
			 trace.c
cairo_trace_la_CFLAGS = @FREETYPE_CFLAGS@ @CAIRO_CFLAGS@
cairo_trace_la_LDFLAGS = -module -no-undefined
cairo_trace_la_LIBADD = -ldl -lz -lbfd

system-install:
	grep -sq @libdir@/cairo-trace.so /etc/ld.so.preload || echo @libdir@/cairo-trace.so >> /etc/ld.so.preload

system-uninstall:
	sed -e '/\/usr\/local\/lib\/cairo-trace.so/d' < /etc/ld.so.preload > /tmp/ld.so.preload && mv /tmp/ld.so.preload /etc/ld.so.preload;

EXTRA_DIST = \
	COPYING \
	COPYING-GPL-3 \
	cairo-trace.in