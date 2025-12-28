#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "utils.h"

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
    printf("Could not compile shader %u, %s\n", sh, info_log);
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
    printf("Failed to link program %u, %s\n", prog, info_log);
    exit(1);
  }
}


int main()
{
  const GLchar *const red_src = 
    "#version 330 core\n"
    "vec4 in_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);"
    "out vec4 color;"
    "void main() {"
    "color = in_color;"
    "}";
  const GLchar *const green_src =
    "#version 330 core\n"
    "vec4 in_color = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
    "out vec4 color;"
    "void main() {"
    "color = in_color;"
    "}";
  const GLchar *const blue_src =
    "#version 330 core\n"
    "vec4 in_color = vec4(0.0f, 0.0f, 1.0f, 1.0f);"
    "out vec4 color;"
    "void main() {"
    "color = in_color;"
    "}";
  const GLfloat red_triangle[] = {
    0.0f, 0.5f, 0.0f,
    0.25f, 0.0f, 0.0f,
    -0.25f, 0.0f, 0.0f
  };
  const GLfloat green_triangle[] = {
    -0.25f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f
  };
  const GLfloat blue_triangle[] = {
    0.25f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
  };
  const GLfloat *const triangles[] = {red_triangle, green_triangle, blue_triangle};
  const GLchar *const fragments[] = {red_src, green_src, blue_src};

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* w = glfwCreateWindow(800, 600, "Colored triforce", NULL, NULL);
  if(!w) {
    printf("It was not possible to create the window\n");
    exit(1);
  }
  glfwSetKeyCallback(w, key_callback);
  glfwMakeContextCurrent(w);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK)
  {
    printf("It was not possible to initialize glew\n");
    exit(1);
  }

  GLuint arrays[3], buffers[3], programs[3], v_shader, f_shader;
  void* source;
  size_t source_size;

  glGenVertexArrays(3, arrays);
  glGenBuffers(3, buffers);
  for(int i=0; i < 3; i++)
    programs[i] = glCreateProgram();

  for(int i=0; i < 3; i++) {
    glBindVertexArray(arrays[i]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triangles[i], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
  }

  v_shader = glCreateShader(GL_VERTEX_SHADER);
  load_file("../src/shaders/basic.vert", &source_size, &source);
  glShaderSource(v_shader, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(v_shader);
  check_shader(v_shader);
  free(source);

  f_shader = glCreateShader(GL_FRAGMENT_SHADER);
  for(int i=0; i < 3; i++) {
    glShaderSource(f_shader, 1, fragments + i, NULL);
    glCompileShader(f_shader);
    check_shader(f_shader);
    glAttachShader(programs[i], v_shader);
    glAttachShader(programs[i], f_shader);
    glLinkProgram(programs[i]);
    check_program(programs[i]);
  }
  glDeleteShader(f_shader);
  glDeleteShader(v_shader);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glViewport(0, 0, 800, 600);

  while(!glfwWindowShouldClose(w))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0; i < 3; i++)
    {
      glBindVertexArray(arrays[i]);
      glUseProgram(programs[i]);
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    glfwSwapBuffers(w);
  }
  
  return 0;
}
