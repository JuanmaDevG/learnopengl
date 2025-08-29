#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h> //TODO: remove

/*
 * Notes for attributes that are confusing:
 * ----------------------------------------
 *
 * CWAttributeName -> CW stands for Configure Window
 *
 * bit_gravity: how to preserve window contents if window is resized.
 *
 * win_gravity: how to reposition the window when parent window is resized or
 *  repositioned.
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
 *  mask. WARNING: it cannot interfere with .event_mask and the only events
 *  available are:
 *  - KeyPressMask
 *  - KeyReleaseMask
 *  - ButtonPressMask
 *  - ButtonReleaseMask
 *  - PointerMotionMask
 *  - ButtonMotionMask
 *  - Button1MotionMask
 *  - Button2MotionMask
 *  - Button3MotionMask
 *  - Button4MotionMask
 *  - Button5MotionMask
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

int main()
{
  Display *disp = XOpenDisplay(NULL);
  XSetWindowAttributes attr = {
    .background_pixel = BlackPixel(disp, DefaultScreen(disp)),
    .border_pixel = WhitePixel(disp, DefaultScreen(disp)),
    .bit_gravity = CenterGravity,
    .win_gravity = ForgetGravity,
    .save_under = False,
    .event_mask = (KeyPressMask | KeyReleaseMask | ExposureMask),
    .do_not_propagate_mask = ButtonReleaseMask, // for example
    .override_redirect = False,
    .colormap = CopyFromParent,
    .cursor = None,
    .backing_store = NotUseful,
    .backing_planes = AllPlanes,
    .backing_pixel = 0
  };

  //NOTE:
  //For window depth, CopyFromParent is better and equally verbose
  Window w = XCreateWindow(disp, DefaultRootWindow(disp), 0, 0, 800, 600, 0,
      Depth(disp), InputOutput, CopyFromParent,
      CWBackPixel | CWBorderPixel | CWBitGravity | CWEventMask | CWDontPropagate,
      &attr);

  XWindowAttributes extracted_attr;
  XGetWindowAttributes(disp, w, &extracted_attr);

  printf("Window { x: %i, y: %i, width: %i, height: %i, border_width: %i }\n",
      extracted_attr.x, extracted_attr.y,
      extracted_attr.width, extracted_attr.height,
      extracted_attr.border_width);

  char const* p_str;
  switch(extracted_attr.bit_gravity) {
    case ForgetGravity:
      p_str = "ForgetGravity";
      break;
    case NorthWestGravity:
      p_str = "NorthWestGravity";
      break;
    case NorthGravity:
      p_str = "NorthGravity";
      break;
    case NorthEastGravity:
      p_str = "NorthEastGravity";
      break;
    case WestGravity:
      p_str = "WestGravity";
      break;
    case CenterGravity:
      p_str = "CenterGravity";
      break;
    case EastGravity:
      p_str = "EastGravity";
      break;
    case SouthWestGravity:
      p_str = "SouthWestGravity";
      break;
    case SouthGravity:
      p_str = "SouthGravity";
      break;
    case SouthEastGravity:
      p_str = "SouthEastGravity";
      break;
    case StaticGravity:
      p_str = "StaticGravity";
      break;
    default:
      p_str = "ERROR";
  };
  printf("- bit_gravity: %s\n", p_str);

  printf("- your_event_mask: ");
  char const *const avail_event_masks[] = {
    "KeyPressMask",
    "KeyReleaseMask",
    "ButtonPressMask",
    "ButtonReleaseMask",
    "EnterWindowMask",
    "LeaveWindowMask",
    "PointerMotionMask",
    "PointerMotionHintMask",
    "Button1MotionMask",
    "Button2MotionMask",
    "Button3MotionMask",
    "Button4MotionMask",
    "Button5MotionMask",
    "ButtonMotionMask",
    "KeymapStateMask",
    "ExposureMask",
    "VisibilityChangeMask",
    "StructureNotifyMask",
    "ResizeRedirectMask",
    "StructureNotifyMask",
    "ResizeRedirectMask",
    "SubstructureNotifyMask",
    "SubstructureRedirectMask",
    "FocusChangeMask",
    "PropertyChangeMask",
    "ColormapChangeMask",
    "OwnerGrabButtonMask"
  };
  if(extracted_attr.your_event_mask == NoEventMask)
  {
    printf("NoEventMask");
  }
  else {
    printf("{ ");
    if(extracted_attr.your_event_mask & 1) {
      printf("KeyPressMask ");
    }
    for(int i=1; i <= 24; i++)
    {
      if((extracted_attr.your_event_mask >> i) & 1)
        printf("| %s ", avail_event_masks[i]);
    }
    printf("}");
  }
  printf("\n");
  
  // I'm lazy to do the do_not_propagate_mask, it would be basially the same

  XDestroyWindow(disp, w);
  XCloseDisplay(disp);
  return 0;
}
