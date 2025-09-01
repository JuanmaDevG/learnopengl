#include <X11/Xlib.h>
#include <X11/Xatom.h>

static Display *disp;
static int screen_num;
static int default_depth;
static Window wroot; //NOTE: a window is a drawable

static XSetWindowAttributes attr = {
  .bit_gravity = CenterGravity,
  .backing_store = NotUseful,
  .save_under = False,
  .override_redirect = False,
  .event_mask = KeyPressMask | KeyReleaseMask | ExposureMask
};


int main()
{
  disp = XOpenDisplay(NULL);
  screen_number = DefaultScreen(disp);
  default_depth = DefaultDepth(disp, screen_number);
  wroot = DefaultRootWindow(disp);

  attr.background_pixel = BlackPixel(disp, screen_number);
  attr.border_pixel = WhitePixel(disp, screen_number);

  Window w = XCreateWindow(disp, wroot, 0, 0, 800, 600, 3, 
      default_depth, InputOutput, CopyFromParent,
      CWBitGravity | CWBackingStore | CWSaveUnder | CWEventMask,
      &attr);

  Pixmap pmap = XCreatePixmap(disp, w, 100, 100, (unsigned int)default_depth);

  XGCValues gcval = {
  };
  GC gc = XCreateGC(disp, w, 0/*TODO*/, &gcval);

  //TODO: drawing something and putting a loop

  XFreePixmap(pmap);
  XDestroyWindow(disp, w);
  XCLoseDisplay(disp);
  return 0;
}
