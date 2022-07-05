#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"UniformBuffer.h"
#include"VertexArray.h"
#include"Texture.h"
#include"VertexBufferLayout.h"
#include"Shader.h"
#include"Logo.h"

void key_callback(GLFWwindow*, int, int, int, int);

const GLuint WIDTH = 1920, HEIGHT = 1080;

int main(void)
{
    srand(time(0));
    if (!initGLFW())
        return -1;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LogoBounce", glfwGetPrimaryMonitor(), NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    setupDebug();
    GLCall(glDisable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLint width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    {
        glm::vec3 windowDims(8.0f, 6.0f, 3.0f);
        Logo logo;
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 proj = glm::ortho(-windowDims.x, windowDims.x, -windowDims.y, windowDims.y, -windowDims.z, windowDims.z);

        logo.getShader().setMat4("view", view);
        logo.getShader().setMat4("projection", proj);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            glClearColor(0.05f, 0.0f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            logo.update(windowDims);

            GLCall(glDrawElements(GL_TRIANGLES, logo.getIndicesCount(), GL_UNSIGNED_INT, 0));

            glfwSwapBuffers(window);
        }
    }
    
    glfwTerminate();
    return 0;
}