#ifndef UTILS_H
#define UTILS_H

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void load_file(const char *const restrict filename, size_t *const file_size, void **const filebuf)
{
  struct stat file_status;
  if(stat(filename, &file_status) < 0)
  {
    *filebuf = NULL;
    *file_size = 0;
    return;
  }
  *file_size = file_status.st_size;
  *filebuf = malloc(*file_size + 1);
  ((char*)*filebuf)[*file_size] = '\0';
  int fd = open(filename, O_RDONLY, 0);
  read(fd, *filebuf, *file_size);
  close(fd);
}

#endif // UTILS_H
