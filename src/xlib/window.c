#include <X11/Xlib.h>

int main()
{
  Display* disp = XOpenDisplay(NULL);
  XSetWindowAttributes wattr;
  wattr.background_pixel = WhitePixel(disp, DefaultScreen(disp));

  Window w = XCreateWindow(
      disp, DefaultRootWindow(disp), 0, 0, 800, 600, 0,
      DefaultDepth(disp, DefaultScreen(disp)), InputOutput, CopyFromParent,
      CWBackPixel, &wattr);

  XDestroyWindow(disp, w);
  XCloseDisplay(disp);
  return 0;
}
