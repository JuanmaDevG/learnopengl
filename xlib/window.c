#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  Display* disp = XOpenDisplay(NULL);
  if(!disp) {
    printf("I mean... the display is null man\n");
    return EXIT_FAILURE;
  }

  XSetWindowAttributes wattr;
  wattr.background_pixel = WhitePixel(disp, DefaultScreen(disp));

  Window w = XCreateWindow(
      disp, DefaultRootWindow(disp), 0, 0, 800, 600, 0,
      DefaultDepth(disp, DefaultScreen(disp)), InputOutput, CopyFromParent,
      CWBackPixel, &wattr);

  XMapWindow(disp, w);
  XFlush(disp); //Force to process all events and block till done
  sleep(2);

  XDestroyWindow(disp, w);
  XCloseDisplay(disp);
  return EXIT_SUCCESS;
}
