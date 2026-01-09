#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include "utils.h"


//TODO: look for another non-progressive jpeg img
int main()
{
  const GLfloat figure[] = {
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f
  };
  const GLuint indices[] = { 0, 1, 2, 1, 2, 3 };
  const GLfloat tex_clamp_border_color[] = { 1.0f, 1.0f, 0.0f, 0.0f };

  glfwInit();
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* w = glfwCreateWindow(800, 600, "Mixing textures", NULL, NULL);
  glfwSetKeyCallback(key_callback);
  glfwMakeContextCurrent(w);

  glewExperimental = GL_TRUE;
  glewInit();

  GLuint vao, vbo, ebo, tex, prog, v_shader, f_shader;
  void* source;
  size_t source_size;
  GLint tex_uloc;
  int width, height;
  unsigned char *img;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(figure), figure, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (vodi*)(3 * sizeof(GLfloat)));
  glEnableVertexAtrtibArray(0);
  glEnableVertexAtrtibArray(1);
  glBindBuffer(GL_EEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);

  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //TODO: teximage 2D
  glGenerateMipmap(GL_TEXTURE_2D);

  return 0;
}
