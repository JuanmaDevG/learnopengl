#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils.h"
//#include <cglm/cglm.h>


int main()
{
  const GLfloat triangle = {
    -0.5f, 0.5f, 0.0f,
    -1.0f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f
  };

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* w = glfwCreateWindow(800, 600, "Triangle moving and blinking", NULL, NULL);

  //TODO: do buffers and shaders stuff

  //TODO: modify color and position by uniform

  return 0;
}
