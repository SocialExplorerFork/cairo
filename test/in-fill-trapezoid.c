/*
 * Copyright © 2008 Chris Wilson
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Author: Chris Wilson <chris@chris-wilson.co.uk>
 */

#include "cairo-test.h"

static cairo_test_status_t
draw (cairo_t *cr, int width, int height)
{
    const cairo_test_context_t *ctx = cairo_test_get_context (cr);
    cairo_test_status_t ret = CAIRO_TEST_SUCCESS;

    cairo_set_fill_rule (cr, CAIRO_FILL_RULE_EVEN_ODD);

    /* simple rectangle */
    cairo_new_path (cr);
    cairo_rectangle (cr, -10, -10, 20, 20);
    if (! cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Failed to find point inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* rectangular boundary tests */
    if (cairo_in_fill (cr, -10, -10)) {
	cairo_test_log (ctx, "Error: Found top-left vertex inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (cairo_in_fill (cr, -10, 10)) {
	cairo_test_log (ctx, "Error: Found bottom-left vertex inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (! cairo_in_fill (cr, 10, -10)) {
	cairo_test_log (ctx, "Error: Failed to find top-right vertex inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (cairo_in_fill (cr, 10, 10)) {
	cairo_test_log (ctx, "Error: Found bottom-right vertex inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (cairo_in_fill (cr, -10, 0)) {
	cairo_test_log (ctx, "Error: Found left edge inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (! cairo_in_fill (cr, 0, -10)) {
	cairo_test_log (ctx, "Error: Failed to find top edge inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (! cairo_in_fill (cr, 10, 0)) {
	cairo_test_log (ctx, "Error: Failed to find right edge inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (cairo_in_fill (cr, 0, 10)) {
	cairo_test_log (ctx, "Error: Found bottom edge inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* simple circle */
    cairo_new_path (cr);
    cairo_arc (cr, 0, 0, 10, 0, 2 * M_PI);
    if (! cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Failed to find point inside circle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* holey rectangle */
    cairo_new_path (cr);
    cairo_rectangle (cr, -10, -10, 20, 20);
    cairo_rectangle (cr, -5, -5, 10, 10);
    if (cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Found an unexpected point inside rectangular hole\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* holey circle */
    cairo_new_path (cr);
    cairo_arc (cr, 0, 0, 10, 0, 2 * M_PI);
    cairo_arc (cr, 0, 0, 5, 0, 2 * M_PI);
    if (cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Found an unexpected point inside circular hole\n");
	ret = CAIRO_TEST_FAILURE;
    }


    cairo_set_fill_rule (cr, CAIRO_FILL_RULE_WINDING);

    /* simple rectangle */
    cairo_new_path (cr);
    cairo_rectangle (cr, -10, -10, 20, 20);
    if (! cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Failed to find point inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* simple circle */
    cairo_new_path (cr);
    cairo_arc (cr, 0, 0, 10, 0, 2 * M_PI);
    if (! cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Failed to find point inside circle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* overlapping circle/rectangle */
    cairo_new_path (cr);
    cairo_rectangle (cr, -10, -10, 20, 20);
    cairo_new_sub_path (cr);
    cairo_arc (cr, 0, 0, 10, 0, 2 * M_PI);
    if (! cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Failed to find point inside circle+rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* holey rectangle */
    cairo_new_path (cr);
    cairo_rectangle (cr, -10, -10, 20, 20);
    cairo_rectangle (cr, 5, -5, -10, 10);
    if (cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Found an unexpected point inside rectangular hole\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* holey circle */
    cairo_new_path (cr);
    cairo_arc (cr, 0, 0, 10, 0, 2 * M_PI);
    cairo_arc_negative (cr, 0, 0, 5, 0, -2 * M_PI);
    if (cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Found an unexpected point inside circular hole\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* not a holey circle */
    cairo_new_path (cr);
    cairo_arc (cr, 0, 0, 10, 0, 2 * M_PI);
    cairo_arc (cr, 0, 0, 5, 0, 2 * M_PI);
    if (! cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Failed to find point inside two circles\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* check off-centre */
    cairo_new_path (cr);
    cairo_arc (cr, 7.5, 0, 10, 0, 2 * M_PI);
    cairo_arc_negative (cr, 7.5, 0, 5, 0, -2 * M_PI);
    if (cairo_in_fill (cr, 7.5, 0)) {
	cairo_test_log (ctx, "Error: Found an unexpected point inside circular hole\n");
	ret = CAIRO_TEST_FAILURE;
    }
    cairo_new_path (cr);
    cairo_arc (cr, 0, 7.5, 10, 0, 2 * M_PI);
    cairo_arc_negative (cr, 0, 7.5, 5, 0, -2 * M_PI);
    if (cairo_in_fill (cr, 0, 7.5)) {
	cairo_test_log (ctx, "Error: Found an unexpected point inside circular hole\n");
	ret = CAIRO_TEST_FAILURE;
    }
    cairo_new_path (cr);
    cairo_arc (cr, 15, 0, 10, 0, 2 * M_PI);
    if (! cairo_in_fill (cr, 15, 0)) {
	cairo_test_log (ctx, "Error: Failed to find point inside circle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    cairo_new_path (cr);
    cairo_arc (cr, 0, 15, 10, 0, 2 * M_PI);
    if (! cairo_in_fill (cr, 0, 15)) {
	cairo_test_log (ctx, "Error: Failed to find point inside circle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* simple rectangle */
    cairo_new_path (cr);
    cairo_rectangle (cr, 10, 0, 5, 5);
    if (cairo_in_fill (cr, 0, 0)) {
	cairo_test_log (ctx, "Error: Found an unexpected point outside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (cairo_in_fill (cr, 20, 20)) {
	cairo_test_log (ctx, "Error: Found an unexpected point outside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (! cairo_in_fill (cr, 12.5, 2.5)) {
	cairo_test_log (ctx, "Error: Failed to find point inside rectangle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    /* off-centre triangle */
    cairo_new_path (cr);
    cairo_move_to (cr, 10, 0);
    cairo_line_to (cr, 15, 5);
    cairo_line_to (cr, 5, 5);
    cairo_close_path (cr);
    if (cairo_in_fill (cr, 0, 0) ||
	cairo_in_fill (cr, 10, 10) ||
	cairo_in_fill (cr, 20, 0) ||
	cairo_in_fill (cr, 7, 2.5) ||
	cairo_in_fill (cr, 13, 2.5))
    {
	cairo_test_log (ctx, "Error: Found an unexpected point outside triangle\n");
	ret = CAIRO_TEST_FAILURE;
    }
    if (! cairo_in_fill (cr, 8, 2.5) ||
	! cairo_in_fill (cr, 12, 2.5))
    {
	cairo_test_log (ctx, "Error: Failed to find point inside triangle\n");
	ret = CAIRO_TEST_FAILURE;
    }

    return ret;
}

CAIRO_TEST (in_fill_trapezoid,
	    "Test _cairo_trap_contains via cairo_in_fill",
	    "in, trap", /* keywords */
	    NULL, /* requirements */
	    0, 0,
	    NULL, draw)
