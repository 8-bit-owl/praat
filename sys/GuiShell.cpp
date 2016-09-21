/* GuiShell.cpp
 *
 * Copyright (C) 1993-2012,2015,2016 Paul Boersma, 2013 Tom Naughton
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

#include "GuiP.h"
#include "UnicodeData.h"

Thing_implement (GuiShell, GuiForm, 0);

#if cocoa
	@implementation GuiCocoaShell {
		GuiShell d_userData;
	}
	- (void) dealloc {   // override
		GuiShell me = d_userData;
		my d_cocoaShell = nullptr;   // this is already under destruction, so undangle
		forget (me);
		trace (U"deleting a window or dialog");
		[super dealloc];
	}
	- (GuiThing) getUserData {
		return d_userData;
	}
	- (void) setUserData: (GuiThing) userData {
		Melder_assert (userData == nullptr || Thing_isa (userData, classGuiShell));
		d_userData = static_cast <GuiShell> (userData);
	}
	- (void) keyDown: (NSEvent *) theEvent {
		trace (U"key down");
		[super keyDown: theEvent];   // for automatic behaviour in dialog boxes; do GuiWindows have to override this to do nothing?
	}
	- (BOOL) windowShouldClose: (id) sender {
		GuiCocoaShell *widget = (GuiCocoaShell *) sender;
		GuiShell me = (GuiShell) [widget getUserData];
		if (my d_goAwayCallback) {
			trace (U"calling goAwayCallback)");
			my d_goAwayCallback (my d_goAwayBoss);
		} else {
			trace (U"hiding window or dialog");
			[widget orderOut: nil];
		}
		return false;
	}
	@end
#endif

void structGuiShell :: v_destroy () noexcept {
	#if cocoa
		if (our d_cocoaShell) {
			[our d_cocoaShell setUserData: nullptr];   // undangle reference to this
			Melder_fatal (U"ordering out?");
			[our d_cocoaShell orderOut: nil];
			[our d_cocoaShell close];
			[our d_cocoaShell release];
			our d_cocoaShell = nullptr;   // undangle
		}
	#endif
	GuiShell_Parent :: v_destroy ();
}

int GuiShell_getShellWidth (GuiShell me) {
	int width = 0;
	#if gtk
		width = GTK_WIDGET (my d_gtkWindow) -> allocation.width;
	#elif cocoa
        return [my d_cocoaShell   frame].size.width;
	#elif motif
		width = my d_xmShell -> width;
	#endif
	return width;
}

int GuiShell_getShellHeight (GuiShell me) {
	int height = 0;
	#if gtk
		height = GTK_WIDGET (my d_gtkWindow) -> allocation.height;
	#elif cocoa
        return [my d_cocoaShell   frame].size.height;
	#elif motif
		height = my d_xmShell -> height;
	#endif
	return height;
}

void GuiShell_setTitle (GuiShell me, const char32 *title /* cattable */) {
	#if gtk
		gtk_window_set_title (my d_gtkWindow, Melder_peek32to8 (title));
	#elif cocoa
		[my d_cocoaShell   setTitle: (NSString *) Melder_peek32toCfstring (title)];
	#elif win
		SetWindowTextW (my d_xmShell -> window, Melder_peek32toW (title));
	#endif
}

void GuiShell_drain (GuiShell me) {
	#if gtk
		//gdk_window_flush (gtk_widget_get_window (my d_gtkWindow));
		gdk_flush ();
	#elif cocoa
		NSEvent *nsEvent = [NSApp
			nextEventMatchingMask: NSAnyEventMask
			untilDate: [NSDate distantPast]
			inMode: NSDefaultRunLoopMode
			dequeue: NO
			];
		Melder_assert (my d_cocoaShell);
        [my d_cocoaShell   flushWindow];
	#elif win
	#endif
}

/* End of file GuiShell.cpp */
