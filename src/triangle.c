//IMPORTANT NOTE: make sure to include glew before glfw to import opengl decl
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "utils.h"


void key_callback(GLFWwindow *w, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(w, GL_TRUE);
  }
}

#define INFO_LOG_SIZE 512
GLint gl_status;
GLchar info_log[INFO_LOG_SIZE];


int main()
{
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };

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

  glfwSetKeyCallback(w, key_callback);
  glfwMakeContextCurrent(w);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK)
  {
    printf("Failed to initialize GLEW\n");
    return 1;
  }

  GLuint vertex_buffer, vertex_array, vertex_shader, fragment_shader, program; // index_buffer, vertex_array
  void* source_file;
  size_t source_filesize;

  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0); // Unbind

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  load_file("../src/shaders/basic.vert", &source_file, &source_filesize);
  glShaderSource(vertex_shader, 1, (const GLchar *const *)&source_file, NULL);
  glCompileShader(vertex_shader);
  free(source_file);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &gl_status);
  if(!gl_status)
  {
    glGetShaderInfoLog(vertex_shader, INFO_LOG_SIZE, NULL, info_log);
    printf("Failed to compile vertex shader: %s\n", info_log);
    return 1;
  }

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  load_file("../src/shaders/basic.frag", &source_file, &source_filesize);
  glShaderSource(fragment_shader, 1, (const GLchar *const *)&source_file, NULL);
  glCompileShader(fragment_shader);
  free(source_file);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &gl_status);
  if(!gl_status)
  {
    glGetShaderInfoLog(fragment_shader, INFO_LOG_SIZE, NULL, info_log);
    printf("Failed to compile fragment shader: %s", info_log);
    return 1;
  }

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  glGetProgramiv(program, GL_LINK_STATUS, &gl_status);
  if(!gl_status)
  {
    glGetProgramInfoLog(program, INFO_LOG_SIZE, NULL, info_log);
    printf("Failed to link the shader program: %s\n", info_log);
    return 1;
  }
  glUseProgram(program);
  glBindVertexArray(vertex_array);

  glViewport(0, 0, 800, 600);
  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
  
  while(!glfwWindowShouldClose(w))
  {
    glfwPollEvents(); // Use function callbacks
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(w);
  }

  glfwTerminate();
  return 0;
}
