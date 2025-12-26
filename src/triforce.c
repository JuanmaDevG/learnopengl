#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "utils.h"

#define INFO_LOG_SIZE 512
GLint gl_status;
GLchar info_log[INFO_LOG_SIZE];


void key_callback(GLFWwindow *w, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(w, GL_TRUE);
  }
}


int main()
{
  GLfloat vertices[] = {
    0.0f, 0.5f, 0.0f,
    0.25f, 0.0f, 0.0f,
    -0.25f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
  };

  GLuint indices[] = {0, 1, 2, 2, 3, 4, 1, 4, 5};

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* w = glfwCreateWindow(800, 600, "Zelda's triforce", NULL, NULL);

  if(!w) {
    printf("The window was not created\n");
    glfwTerminate();
    return 1;
  }

  glfwSetKeyCallback(w, key_callback);
  glfwMakeContextCurrent(w);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK) {
    printf("Failed to initialize GLEW\n");
    return 0;
  }

  GLuint v_buf, i_buf, v_arr, v_shader, f_shader, prog;
  void* source;
  size_t source_size;

  glGenVertexArrays(1, &v_arr);
  glBinVertexArray(v_arr);

  glGenBuffers(1, &v_buf);
  glBindBuffer(GL_ARRAY_BUFFER, v_buf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  //TODO: another attribute pointer for color

  glGenBuffers(1, &i_buf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 

  return 0;
}
