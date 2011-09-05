/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpir.h>
#include "flint.h"
#include "arith.h"
#include "ulong_extras.h"

#define PI 3.141592653589793238462643

/* TODO: add MPFR version also */
double
d_cos_pi_frac(mp_limb_signed_t p, mp_limb_signed_t q)
{
    p = FLINT_ABS(p);
    p %= (2 * q);
    if (p >= q)
        p = 2 * q - p;

    if (4 * p <= q)
        return cos(p * PI / q);
    else if (4 * p < 3 * q)
        return sin((q - 2*p) * PI / (2 * q));
    else
        return -cos((q - p) * PI / q);
}

double 
dedekind_cosine_sum_d(mp_limb_t k, mp_limb_t n)
{
    double s;
    int i;
    trig_prod_t prod;

    trig_prod_init(prod);
    dedekind_cosine_sum_factored(prod, k, n);

    if (prod->prefactor == 0)
        return 0.0;

    s = prod->prefactor * sqrt((double)prod->sqrt_p / (double)prod->sqrt_q);

    for (i = 0; i < prod->n; i++)
        s *= d_cos_pi_frac(prod->cos_p[i], prod->cos_q[i]);

    return s;
}