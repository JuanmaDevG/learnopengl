#include <X11/Xlib.h>
#include <X11/Atoms.h>
#include <stdio.h>

/* NOTE:
 * Window properties ARE NOT THE SAME AS widow attributes, a property list for 
 * a window is defined by the client, otherwise window attributes are defined 
 * by the struct XSetWindowAttributes and they are gotten by the 
 * XWindowAttributes struct.
 *
 * Window properties have {name, type, value} and can be attached to a window.
 *
 * NOTE ABOUT XGetWindowProperty:
 * The last parameter prop_return gets a double pointer because it NEEDS a
 * reference to WRITE into the client pointer that will point to the array of 
 * data.
 */


int main() {
  Display *disp = XOpenDisplay(NULL);
  return 0;
}
