#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdio.h>

/* Essentially Atoms are like environment variables to the X server,
 * they can be defined and and decoded as properties
 */

char err_buf[256];

typedef struct {
  Atom id;
  const char* name;
} atom_pair_t;

unsigned char streq(const char *restrict host, const char *restrict guest) {
  while(*host != '\0' && *guest != '\0') {
    if(*host != *guest) return 0;
    host++;
    guest++;
  }
  return 1;
}


int main()
{
  Display* disp = XOpenDisplay(NULL);

  const atom_pair_t pairs[] = {
    {XA_PRIMARY, "PRIMARY"},
    {XA_SECONDARY, "SECONDARY"},
    {XA_BITMAP, "BITMAP"},
    {XA_CUT_BUFFER5, "CUT_BUFFER5"},
    {XA_STRING, "STRING"},
    {XA_SUPERSCRIPT_X, "SUPERSCRIPT_X"},
    {XA_FAMILY_NAME, "FAMILY_NAME"}
  };

  for(int i=0; i < sizeof(pairs) / sizeof(atom_pair_t); i++ )
  {
    if(XInternAtom(disp, pairs[i].name, True) != pairs[i].id) {
      sprintf(err_buf, "Id's of atom %s do not match\n", pairs[i].name);
      perror(err_buf);
      continue;
    }
    if(!streq(XGetAtomName(disp, pairs[i].id), pairs[i].name)) {
      sprintf(err_buf, "Names of the atom %s don't match\n", pairs[i].name);
      perror(err_buf);
      continue;
    }
    printf("The atom %lu is named %s\n", pairs[i].id, pairs[i].name);
  }

  XCloseDisplay(disp);
  return 0;
}
