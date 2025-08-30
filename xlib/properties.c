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
 *
 * PropMode has 3 values:
 * - PropModePrepend: append before the beginning
 * - PropModeAppend: append at the end
 * - PropModeReplace: overwrite
 *
 * NOTE:
 * XRotateWindowProperties basically makes a cyclic shift on the property list, 
 * this is just meant to change order priority:
 * delta = 1: A B C D -> D A B C (right shift)
 * delta = -1: A B C D -> B C D A (left shift)
 */

char win_name[] = "Hello window";


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

  // Add a property to our window (it's name)
  XChangeProperty(
      disp, w, XA_WM_NAME, XA_STRING, 8, PropModeReplace,
      win_name, sizeof(win_name));

  //And then extract it
  int prop_len;
  Atom *properties;
  properties = XListProperties(disp, w, &prop_len);

  printf("Fetched %i properties that are:\n", prop_len);
  for(int i=0; i < prop_len; i++)
  {
    unsigned char *prop_return; // to XFree (not implementing generic data repr)
    char *prop_name, *prop_type_name;
    int prop_fmt;
    Atom prop_type;
    unsigned long nprop_items, prop_bytes_left;
    XGetWindowProperty(
        disp, w, properties[i], 0, ~0ul, False, AnyPropertyType,
        &prop_type, &prop_fmt, &nprop_items, &prop_bytes_left, &prop_return);

    prop_type_name = XGetAtomName(disp, prop_type);
    prop_name = XGetAtomName(disp, properties[i]);
    printf("- %s {type: %s, format: %i, items: %lu, bytes_left: %lu }\n",
        prop_name, prop_type_name, prop_fmt, nprop_items, prop_bytes_left);

    XFree(prop_name);
    XFree(prop_return);
    XFree(prop_type_name);
  }

  prop_len = 0; // Just as annotation, this is useless
  XFree(properties);
  XCloseDisplay(disp);
  return 0;
}
