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
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };

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
  
  glfwSetKeyCallback(w, key_callback);
  glfwMakeContextCurrent(w);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK)
  {
    printf("Failed to initialize GLEW\n");
    return 1;
  }

  GLuint vertex_buffer, index_buffer, vertex_shader, fragment_shader;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  // TODO: load shader with shader_loader funcs
  // TODO: then set the source, compile the shader and free the source code allocated memory

  // Probably make fast shader load functions

  glViewport(0, 0, 800, 600);
  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
  
  while(!glfwWindowShouldClose(w))
  {
    glfwPollEvents(); // Use function callbacks
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(w);
  }

  glfwTerminate();
  return 0;
}
