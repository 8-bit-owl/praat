#ifndef _DLL_h_
#define _DLL_h_
/* DLL.h
 *
 * Copyright (C) 2011 David Weenink, 2015 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include "Data.h"

Thing_define (DLLNode, Daata) {
	DLLNode next, prev;
	Daata data;

	void v_destroy ()
		override;
	void v_copy (Daata data_to)
		override;
};

Thing_define (DLL, Thing) {
	long numberOfNodes;
	DLLNode front, back;

	void v_destroy ()
		override;

	static int s_compareHook (Daata /* data1 */, Daata /* data2 */) noexcept;
	virtual Data_CompareHook v_getCompareHook () { return s_compareHook; }
};

autoDLLNode DLLNode_create (Daata data); // DLLNode owns the data

void DLL_init (DLL me);

autoDLL DLL_create ();

void DLL_addFront (DLL me, DLLNode n);

void DLL_addBack (DLL me, DLLNode n);

void DLL_addBefore (DLL me, DLLNode pos, DLLNode n);

void DLL_addAfter (DLL me, DLLNode pos, DLLNode n);

void DLL_remove (DLL me, DLLNode n);

void DLL_sort (DLL me);

void DLL_sortPart (DLL me, DLLNode from, DLLNode to);

#endif // _DLL_h_

