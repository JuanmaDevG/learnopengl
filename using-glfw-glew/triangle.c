//IMPORTANT NOTE: make sure to include glew before glfw to import opengl decl
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>


void key_callback(GLFWwindow *w, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(w, GL_TRUE);
  }
}

int main()
{
  //GLFW stuff
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* w = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
  
  if(!w) {
    printf("Failed to create the window\n");
    glfwTerminate();
    return 1;
  }
  
  // ESCAPE key means close window
  glfwSetKeyCallback(w, key_callback);
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
  glViewport(0, 0, 800, 600);
  
  //Core loop
  while(!glfwWindowShouldClose(w))
  {
    glfwPollEvents();
    glfwSwapBuffers(w);
  }

  glfwTerminate();
  return 0;
}
