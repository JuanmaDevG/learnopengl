#include <X11/Xlib.h>

int xlib_status;

int main()
{
  Display* disp = XOpenDisplay(NULL);
  XSetWindowAttributes wattr;
  wattr.background_pixel = WhitePixel(disp, DefaultScreen(disp));
  wattr.win_gravity = CenterGravity;

  Window w = XCreateWindow(
      disp, DefaultRootWindow(disp), 0, 0, 800, 600, 0,
      DefaultDepth(disp, DefaultScreen(disp)), InputOutput, CopyFromParent,
      CWBackPixel | CWWinGravity, &wattr);

  xlib_status = XMapWindow(disp, w);

  XDestroyWindow(disp, w);
  XCloseDisplay(disp);
  return 0;
}
