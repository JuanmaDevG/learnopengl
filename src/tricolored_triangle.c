#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils.h"


int main()
{
  const GLfloat colored_triangle[] = {
    // vertices      |    colors
    0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
  };

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* w = glfwCreateWindow(800, 600, "Triangle with three colors", NULL, NULL);
  glfwSetKeyCallback(w, key_callback);
  glfwMakeContextCurrent(w);

  glewExperimental = GL_TRUE;
  glewInit();

  GLuint v_arr, v_buf, prog, v_shader, f_shader;
  void* source;
  size_t source_size;

  glGenVertexArrays(1, &v_arr);
  glGenBuffers(1, &v_buf);

  glBindVertexArray(v_arr);
  glBindBuffer(GL_ARRAY_BUFFER, v_buf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colored_triangle), colored_triangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  prog = glCreateProgram();
  v_shader = glCreateShader(GL_VERTEX_SHADER);
  f_shader = glCreateShader(GL_FRAGMENT_SHADER);

  load_file("../src/shaders/pass_color.vert", &source_size, &source);
  glShaderSource(v_shader, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(v_shader);
  check_shader(v_shader);
  free(source);

  load_file("../src/shaders/recv_color.frag", &source_size, &source);
  glShaderSource(f_shader, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(f_shader);
  check_shader(f_shader);
  free(source);

  glAttachShader(prog, v_shader);
  glAttachShader(prog, f_shader);
  glLinkProgram(prog);
  check_program(prog);
  glDeleteShader(v_shader);
  glDeleteShader(f_shader);

  glUseProgram(prog);
  glBindVertexArray(v_arr);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glViewport(0, 0, 800, 600);

  while(!glfwWindowShouldClose(w))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(w);
  }

  return 0;
}
