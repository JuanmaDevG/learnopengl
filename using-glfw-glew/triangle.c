//IMPORTANT NOTE: make sure to include glew before glfw to import opengl decl
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>


int main()
{
  //GLFW stuff
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWWindow* w = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
  
  if(!w) {
    printf("Failed to create the window\n");
    glfwTerminate();
    exit(1);
  }
  // I guews this allocates, points to, and maps the window
  glfwMakeContextCurrent(w);

  //GLEW stuff
  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK)
  {
    printf("Failed to initialize GLEW\n");
    return 1;
  }

  /* Configure window on OpenGL state machine.
   * Zeros are for the left corner of the window.
   */
  glViewPort(0, 0, 800, 600);
  
  //Core loop
  while(!glfwWindowHouldClose(w))
  {
    glfwPollEvents();
    glfwSwapBuffers(w);
  }

  glfwTerminate();
  return 0;
}
