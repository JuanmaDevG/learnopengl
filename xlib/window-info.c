#include <stdio.h>
#include <X11/Xlib.h>

/*
 * Notes for attributes that are confusing:
 * ----------------------------------------
 *
 * CWAttributeName -> CW stands for Configure Window
 *
 * bit_gravity: how to preserve window contents if window is resized
 *
 * win_gravity: how to reposition the window when parent window is resized
 *
 * backing_store: hints X server if to maintain window contents when a window 
 *  is partially (or completely covered), in some applications this has no
 *  sense because when the window is uncovered, it is solved with a redraw.
 *
 * backing_planes: basically a mask where you decide what color bits are
 *  significant to preserve in the backing store. If I preserve 0xff (bits 0 - 7)
 *  , I'm only saving the blue channel, having a 'blued' save as a result till
 *  any repaint is made. On modern desktops YOU SHOULD IGNORE THEM
 *
 * backing_pixel: for bits set to 0 on backing_planes (bits considered 
 *  non-relevant to store), we can decide what will be their default value 
 *  when the window is uncovered (they're normally set to zero).
 *
 * save_under: when set to True (X definition of true), if the window is
 *  partially covered by a pop up window, the pixels will be saved without
 *  the need for a redraw when uncovered.
 * 
 * event_mask: inclusive OR bitmask of the events types taht the window can
 *  receive.
 *
 * do_not_propagate_mask: if our event_mask ignores an event type, it propagates
 *  to the parent window. We can avoid propagation by setting that bit in this
 *  mask.
 *
 * override_redirect: when True, tells the window manager NOT to intercept or
 *  modify window properties, location or size. This is fine for pop-up windows
 *  that may need to map in a very specific way.
 *
 * colormap: select the colormap for the window (read more), the most generic
 *  (and normally the optimal) is to set it to CopyFromParent.
 *
 * cursor: wich cursor to be used when the pointer is in the window. If set to
 *  None, the parent's cursor is used.
 * */

#define Depth(display) DefaultDepth(display, DefaultScreen(display))

inr main()
{
  Display *disp = XOpenDisplay(NULL);
  XSetWindowAttributes attr = {
    .background_pixel = BlackPixel(disp, DefaultScreen(disp)),
    .border_pixel = WhitePixel(disp, DefaultScreen(disp)),
    .bit_gravity = Centergravity,
    .win_gravity = ForgetGravity,
    .save_under = False,
    .event_mask = KeyPressMask | KeyReleaseMask | ExposureMask,
    .do_not_propagate_mask = 
      0xffffffff & ~(KeyPressMask | KeyReleaseMask | ExposureMask),
    .override_redirect = False,
    .colormap = CopyFromParent,
    .cursor = None,
    .backing_store = NotUseful,
    .backing_planes = AllPlanes(),
    .backing_pixel = 0
  };

  Widnow w = XCreateWindow(disp, DefaultRootWindow(disp), 0, 0, 800, 600, 0,
      Depth(disp), InputOutput, CopyFromParent,
      CWBackPixel | CWBorderPixel | CWBitGravity | CWEventMask | CWDontPropagate,
      &attr);

  // Not mapping, just extracting and printing window information

  XDestroyWindow(disp, w);
  XCloseDisplay(disp);
  return EXIT_SUCCESS;
}
