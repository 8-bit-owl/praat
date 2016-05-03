#ifndef _Index_h_
#define _Index_h_
/* Index.h
 *
 * Copyright (C) 2005-2011 David Weenink
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Collection.h"

#include "Index_def.h"

void Index_init (Index me, long numberOfElements);

autoIndex Index_extractPart (Index me, long from, long to);

autoStringsIndex StringsIndex_create (long numberOfElements);

int StringsIndex_getClass (StringsIndex me, char32 *classLabel);

long StringsIndex_countItems (StringsIndex me, int iclas);

#endif /* _Index_h_ */
