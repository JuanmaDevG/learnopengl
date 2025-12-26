#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "utils.h"

#define INFO_LOG_SIZE 512


void key_callback(GLFWwindow *w, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(w, GL_TRUE);
  }
  else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
  {
    static GLenum cur_mode = GL_FILL;
    if(cur_mode == GL_FILL) cur_mode = GL_LINE;
    else cur_mode = GL_FILL;
    glPolygonMode(GL_FRONT_AND_BACK, cur_mode);
  }
}

void check_shader(const GLuint sh)
{
  GLint compilation_ok;
  GLchar info_log[INFO_LOG_SIZE];
  glGetShaderiv(sh, GL_COMPILE_STATUS, &compilation_ok);
  if(!compilation_ok)
  {
    glGetShaderInfoLog(sh, INFO_LOG_SIZE, NULL, info_log);
    printf("Failed to compile shader %u, %s\n", sh, info_log);
    exit(1);
  }
}

void check_program(GLuint prog)
{
  GLint linkage_ok;
  GLchar info_log[INFO_LOG_SIZE];
  glGetProgramiv(prog, GL_LINK_STATUS, &linkage_ok);
  if(!linkage_ok)
  {
    glGetProgramInfoLog(prog, GL_INFO_LOG_LENGTH, NULL, info_log);
    printf("Failed to link program %u, %s\n", prog, info_log);
    exit(1);
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

  load_file("../src/shaders/basic.vert", &source, &source_size);
  glShaderSource(v_shader, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(v_shader);
  check_shader(v_shader);
  free(source);
  load_file("../src/shaders/basic.frag", &source, &source_size);
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
