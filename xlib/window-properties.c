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
 */

int main() {
  return 0;
}
