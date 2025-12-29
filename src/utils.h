#ifndef UTILS_H
#define UTILS_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define INFO_LOG_LENGTH 512


void key_callback(GLFWwindow *w, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(w, GL_TRUE);
  }
  else if(key == GLFW_KEY_SPACE  && action == GLFW_PRESS)
  {
    static GLenum pmode = GL_FILL;
    if(pmode == GL_FILL) pmode = GL_LINE;
    else pmode = GL_FILL;
    glPolygonMode(GL_FRONT_AND_BACK, pmode);
  }
}

void check_shader(GLuint sh)
{
  GLint status_ok;
  GLchar info_log[INFO_LOG_LENGTH];
  glGetShaderiv(sh, GL_COMPILE_STATUS, &status_ok);
  if(!status_ok)
  {
    glGetShaderInfoLog(sh, INFO_LOG_LENGTH, NULL, info_log);
    fprintf(stderr, "Could not compile shader %u, %s\n", sh, info_log);
    exit(1);
  }
}

//void glPrintError();

void check_program(GLuint prog)
{
  GLint linkage_ok;
  GLchar info_log[INFO_LOG_LENGTH];
  glGetProgramiv(prog, GL_LINK_STATUS, &linkage_ok);
  if(!linkage_ok)
  {
    glGetProgramInfoLog(prog, GL_INFO_LOG_LENGTH, NULL, info_log);
    fprintf(stderr, "Failed to link program %u, %s\n", prog, info_log);
    exit(1);
  }
}

void check_uniform(GLint u_loc)
{
  if(u_loc == -1)
  {
    fprintf(stderr, "Uniform unreachable because it doesn't exist or it was not used and the GLSL compiler removed it\n");
    exit(1);
  }
}


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
