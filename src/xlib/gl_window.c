#include <X11/Xlib.h>

//TODO: finish later

int main()
{
  Display* disp = XOpenDisplay(NULL);
  Window w = XCreateWindow(disp, NULL, 0, 0, 800, 600, 0, 0, InputOutput);
  //TODO: to get screen number from a Display, use macro DefaultScreen
  return 0;
}
