#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_BUF_LENGTH 256

int xlib_status = 0;
char err_buf[ERR_BUF_LENGTH];

int main()
{
  Display* disp = XOpenDisplay(NULL);
  if(!disp) {
    printf("I mean... the display is null man\n");
    exit(1);
  }

  XSetWindowAttributes wattr;
  wattr.background_pixel = WhitePixel(disp, DefaultScreen(disp));

  /*
  Window w = XCreateWindow(
      disp, DefaultRootWindow(disp), 0, 0, 800, 600, 0,
      DefaultDepth(disp, DefaultScreen(disp)), InputOutput, CopyFromParent,
      CWBackPixel, &wattr);
  */
  //TODO: debug, BadRequest being sent
  Window w = XCreateSimpleWindow(
      disp, DefaultRootWindow(disp), 0, 0, 800, 600, 0, 0,
      BlackPixel(disp, DefaultScreen(disp)));

  xlib_status = XMapWindow(disp, w);
  if(xlib_status) {
    XGetErrorText(disp, xlib_status, err_buf, ERR_BUF_LENGTH);
    printf("CANNOT MAP WINDOW: %s\n", err_buf);
    XCloseDisplay(disp);
    exit(1);
  }
  sleep(2);

  XDestroyWindow(disp, w);
  XCloseDisplay(disp);
  return 0;
}
