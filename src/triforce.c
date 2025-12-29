#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "utils.h"


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
    fprintf(stderr, "The window was not created\n");
    glfwTerminate();
    return 1;
  }

  glfwSetKeyCallback(w, key_callback);
  glfwMakeContextCurrent(w);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return 0;
  }

  GLuint v_buf, i_buf, v_arr, v_shader, f_shader, prog;
  void* source;
  size_t source_size;

  glGenVertexArrays(1, &v_arr);
  glBindVertexArray(v_arr);

  glGenBuffers(1, &v_buf);
  glBindBuffer(GL_ARRAY_BUFFER, v_buf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glGenBuffers(1, &i_buf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBindVertexArray(0);

  prog = glCreateProgram();
  v_shader = glCreateShader(GL_VERTEX_SHADER);
  f_shader = glCreateShader(GL_FRAGMENT_SHADER);

  load_file("../src/shaders/basic.vert", &source_size, &source);
  glShaderSource(v_shader, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(v_shader);
  check_shader(v_shader);
  free(source);
  load_file("../src/shaders/basic.frag", &source_size, &source);
  glShaderSource(f_shader, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(f_shader);
  check_shader(f_shader);
  free(source);

  glAttachShader(prog, v_shader);
  glAttachShader(prog, f_shader);
  glLinkProgram(prog);
  glDeleteShader(v_shader);
  glDeleteShader(f_shader);
  check_program(prog);

  glUseProgram(prog);
  glBindVertexArray(v_arr);
  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
  glViewport(0, 0, 800, 600);

  while(!glfwWindowShouldClose(w))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, (void*)0);

    glfwSwapBuffers(w);
  }

  return 0;
}
