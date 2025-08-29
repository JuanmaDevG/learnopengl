#include <X11/Xlib.h>
#include <X11/Xatom.h>
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
  XSetWindowAttributes attr = {
    .background_pixel = WhitePixel(disp, DefaultScreen(disp)),
    .bit_gravity = CenterGravity,
    .backing_store = NotUseful,
    .save_under = False,
    .event_mask = KeyPressMask | KeyReleaseMask | ExposureMask,
    .override_redirect = False,
    .colormap = CopyFromParent
  };
  Window w = XCreateWindow(disp, DefaultRootWindow(disp),
      0, 0, 800, 600, 0, CopyFromParent, InputOutput, CopyFromParent,
      CWBackPixel | CWBitGravity | CWBackingStore | CWEventMask | CWColormap,
      &attr);

  int prop_len;
  Atom *properties;
  properties = XListProperties(disp, w, &prop_len);

  //TODO: add properties (none by default)

  printf("Fetched %i properties whose names are:\n", prop_len);
  for(int i=0; i < prop_len; i++)
  {
    char *atom_name;
    atom_name = XGetAtomName(disp, properties[i]);
    printf("- %s\n", atom_name);
    XFree(atom_name);
  }

  prop_len = 0; // Just as annotation, this is useless
  XFree(properties);
  XCloseDisplay(disp);
  return 0;
}
