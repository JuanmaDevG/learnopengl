#include <X11/Xlib.h>

//TODO: finish later

int main()
{
  Display* disp = XOpenDisplay(NULL);
  Window w = XCreateWindow(
      disp, DefaultRootWindow(disp), 0, 0, 800, 600, 0,
      DefaultDepth(disp, DefaultScreen(disp)), InputOutput, CopyFromParent, //TODO: see value mask and Window Attributes
  return 0;
}
