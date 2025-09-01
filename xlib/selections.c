#include <X11/Xlib.h>
#include <Xatom.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.c>

/*
 *
 *
 *
 *
 *
 *
 *
 *
 * DOES NOT WORK!!! I'll later fix it
 *
 *
 *
 *
 *
 *
 *
 *
*/

Display *disp;
Atom selection;
const Atom s_type = XA_STRING;
const char *s_name = "CUSTOM_TMP_BUFFER";
Window s_owner;

//NOTE:
// This is an example of selections by using a producer/consumer model

// TODO: CHANGE THE WHOLE PROGRAM, selections are owned by the program that 
// creates the window and by there, that program is the producer of data


void producer()
{
  disp = XOpenDisplay(NULL);
  do {
    selection = XInternAtom(disp, s_name, True);
    sleep(1);
  } while(selection == None);
  printf("Producer got the atom\n");

  do {
    s_owner = XGetSelectionOwner(disp, selection);
    sleep(1);
  } while(s_owner == None);
  printf("Producer got the selection owner\n");

  XCloseDisplay(disp);
  exit(0);
}

void consumer()
{
  disp = XOpenDisplay(NULL);

  XCloseDisplay(disp);
  exit(0);
}

int main()
{
  pid_t child = fork();
  if(child == (pid_t)-1) {
    perror("Could not generate the child process\n");
    return 1;
  }

  producer();
  if(child == 0) consumer();
  return 0;
}
