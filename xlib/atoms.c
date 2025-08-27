#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdio.h>

#define XA_ atom_property_type // is this right?

typedef struct {
  Atom id;
  const char* name;
} atom_pair_t;

int main()
{
  const atom_pair_t pairs[] = {
    {XA_PRIMARY, "PRIMARY"},
    {XA_SECONDARY, "SECONDARY"},
    {XA_BITMAP, "BITMAP"},
    {XA_CUT_BUFFER5, "CUT_BUFFER5"},
    {XA_STRING, "STRING"},
    {XA_SUPERSCRIPT_X, "SUPERSCRIPT_X"},
    {XA_FAMILY_NAME, "FAMILY_NAME"}
  };

  for(int i=0; i < sizeof(pairs) / sizeof(atom_pair_t); i++ ) {
    //TODO: marcar corespondencia
  }

  // Loop that returns and compares expected values
  printf("%lu each being %lu so we %lu elems\n", sizeof(pairs), sizeof(atom_pair_t), sizeof(pairs) / sizeof(atom_pair_t));
  return 0;
}
