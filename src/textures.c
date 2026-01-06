#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include "utils.h"

int main()
{
  const GLfloat texture_fig[] = {
    // coords        // texture coords
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 1.0f
  };
  const GLuint indices[] = { 0, 1, 2, 1, 2, 3 };
  const GLfloat tex_clamp_border_color[] = { 1.0f, 1.0f, 0.0f, 0.0f };

  glfwInit();
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLWF_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* w = glfwCreateWindow(800, 600, "Texture", NULL, NULL);
  
  glfwSetKeyCallback(w, key_callback);
  glfwMakeContextCurrent(w);

  glewStatic = GL_TRUE;
  glewInit();

  GLuint v_arr, v_buff, e_buf, tex, prog, v_shader, f_shader;
  void* source;
  size_t source_size;

  glGenVertexArrays(1, &v_arr);
  glGenBuffers(1, &v_buf);
  glGenBuffers(1, &e_buf);
  glBindVertexArray(v_arr);
  glBindBuffer(GL_ARRAY_BUFFER, v_buf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e_buf);
  glBUfferData(GL_ARRAY_BUFFER, sizeof(texture_fig), texture_fig, GL_STATIC_DRAW);
  glBUfferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIS_DRAW);
  glVertexAttribPointer(0, 3, 5 * sizeof(GLfloat), (void*)0);
  glVertexAttribPointer(1, 2, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  prog = glCreateProgram();
  v_shader = glCreateShader(GL_VERTEX_SHADER);
  f_shader = glCreateShader(GL_FRAGMENT_SHADER);
  load_file("../src/shaders/basic_tex.vert", &source_size, &source);
  glShaderSource(v_shader, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(v_shader);
  check_shader(v_shader);
  free(source);
  load_file("../src/shaders/basic_tex.frag", &source_size, &source);
  glShaderSource(f_shader, 1, (const GLchar* const*)&source, NULL);
  glCompileShader(f_shader);
  check_shader(f_shader);
  free(source);
  glAttachShader(prog, v_shader);
  glAttachShader(prog, f_shader);
  glLinkProgram(prog);
  check_program(prog);
  glDeleteShader(v_shader);
  glDeleteShader(f_shader);

  int width, height;
  unsigned char* img;
  img = SOIL_load_image("../src/img/shbeek.jpg", &width, &height, 0, SOIL_LOAD_RGB); //TODO: why channels param is zeroed
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, tex_clamp_border_color);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(
      GL_TEXTURE_2D,      // target
      0,                  // mipmap_level
      GL_RGB,             // GPU dst fmt
      width, height,
      0,                  // LEGACY, KEEP ZERO
      GL_RGB,             // RAM src fmt (what to expect)
      GL_UNSIGNED_BYTE,   // RAM src datatype
      img);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(img);
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindTexture2D(GL_TEXTURE_2D, tex); //TODO: mess up with uniforms, this alone is likely to not work
  glBindVertexArray(v_arr);
  glUseProgram(prog);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glViewport(0, 0, 800, 600);
  //TODO: get uniform locations
  while(!glfwWindowShouldClose(w))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    //TODO: draw calls and stuff

    glfwSwapBuffers(w);
  }

  return 0;
}
