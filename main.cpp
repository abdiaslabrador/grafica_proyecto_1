// scaling operations, then rotations and lastly translations 
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <glad/glad.c>
#include <glfw/glfw3.h>
#include <shaderClass/shaderClass.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void primera_escena(unsigned int *transformLoc, unsigned int *cuadrado_vao);
void segunda_escena(unsigned int *transformLoc, unsigned int *triangulo_vao);
void tercera_escena(unsigned int *transformLoc, unsigned int *pentagono_vao, unsigned int *triangulo_vao, unsigned int *cuadrado_vao);
void check_shader_program_status(int shaderProgram);
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void check_shader_compile_status(int vertexShader);
unsigned int escenario = 1;
 float x = 0.0f;
 float y = 0.0f;
 float acumulador = 1.0f;

int main(){ 
    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
    // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    if (!gladLoadGL()) {
        std::cout << "Failed to initalize glad\n";
        glfwDestroyWindow(window);
        glfwTerminate();
    } 

Shader ourShader("shaders/shader.vs", "shaders/shader.fs");


float vertices_triangulo[] = {
    // positions          // colors 
    -0.5f, -0.5f, 0.0f,  0.57f, 0.16f, 0.12f,
     0.5f, -0.5f, 0.0f,  0.57f, 0.16f, 0.12f,
     0.0f,  0.5f, 0.0f,  0.57f, 0.16f, 0.12f
};

float vertices_cuadrado[] = {
    // positions          // colors           
     0.5f,  0.5f, 0.0f,   0.68f, 0.37f, 0.10f,  // top right 
     0.5f, -0.5f, 0.0f,   0.68f, 0.37f, 0.10f,  // bottom right
    -0.5f, -0.5f, 0.0f,   0.68f, 0.37f, 0.10f,  // bottom left
    -0.5f,  0.5f, 0.0f,   0.68f, 0.37f, 0.10f   // top left 
}; 
unsigned int indices_cuadrado[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};   

float vertices_pentagono[] = {
    // positions          // colors           
     0.3f,  -0.41f, 0.0f,   0.68f, 0.37f, 0.10f,  // top right 
     0.0f, 0.0f, 0.0f,   0.68f, 0.37f, 0.10f,  // bottom right
    -0.3f,  -0.41f, 0.0f,   0.68f, 0.37f, 0.10f,  // bottom left
    -0.49f,  0.16f, 0.0f,   0.68f, 0.37f, 0.10f,   // top left 
     0.0f,  0.51f, 0.0f,   0.68f, 0.37f, 0.10f,   // top left 
     0.49f,  0.16f, 0.0f,   0.68f, 0.37f, 0.10f,   // top left 
}; 
unsigned int indices_pentagono[] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
    2, 1, 3,    // second triangle
    3, 1, 4,    // second triangle
    4, 1, 5,    // second triangle
    5, 1, 0    // second triangle
};

    unsigned int cuadrado_vao;
    glGenVertexArrays(1, &cuadrado_vao);
    glBindVertexArray(cuadrado_vao);

    unsigned int cuadrado_ebo;
    glGenBuffers(1, &cuadrado_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cuadrado_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_cuadrado), indices_cuadrado, GL_STATIC_DRAW); 

    // A partir de ahora, almacenamos los datos de vértices en la memoria de la tarjeta gráfica administrada por un objeto de búfer de vértices llamado VBO .
    unsigned int cuadrado_vbo;//creamos la variable para el objeto de vértices
    glGenBuffers(1, &cuadrado_vbo);  //le asignamos al objeto de los vértices un id
    glBindBuffer(GL_ARRAY_BUFFER, cuadrado_vbo); //elazandolo con el tipo de vertices buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cuadrado), vertices_cuadrado, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int triangulo_vao;
    glGenVertexArrays(1, &triangulo_vao);
    glBindVertexArray(triangulo_vao);

    // A partir de ahora, almacenamos los datos de vértices en la memoria de la tarjeta gráfica administrada por un objeto de búfer de vértices llamado VBO .
    unsigned int triangulo_vbo;//creamos la variable para el objeto de vértices
    glGenBuffers(1, &triangulo_vbo);  //le asignamos al objeto de los vértices un id
    glBindBuffer(GL_ARRAY_BUFFER, triangulo_vbo); //elazandolo con el tipo de vertices buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangulo), vertices_triangulo, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int pentagono_vao;
    glGenVertexArrays(1, &pentagono_vao);
    glBindVertexArray(pentagono_vao);

    unsigned int pentagono_ebo;
    glGenBuffers(1, &pentagono_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pentagono_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_pentagono), indices_pentagono, GL_STATIC_DRAW); 

    // A partir de ahora, almacenamos los datos de vértices en la memoria de la tarjeta gráfica administrada por un objeto de búfer de vértices llamado VBO .
    unsigned int pentagono_vbo;//creamos la variable para el objeto de vértices
    glGenBuffers(1, &pentagono_vbo);  //le asignamos al objeto de los vértices un id
    glBindBuffer(GL_ARRAY_BUFFER, pentagono_vbo); //elazandolo con el tipo de vertices buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_pentagono), vertices_pentagono, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    ourShader.use();
    unsigned int model = glGetUniformLocation(ourShader.ID, "model");
   

   while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);

        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // note that we're translating the scene in the reverse direction of where we want to move
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 5.0f);
        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projectionLoc  = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        switch (escenario) {
        case 1:
            primera_escena(&model, &triangulo_vao);
            break;
        case 2:
            segunda_escena(&model, &cuadrado_vao);
            break;
        case 3:
            tercera_escena(&model, &pentagono_vao, &triangulo_vao, &cuadrado_vao);
            break;
        }

        
        glfwSetKeyCallback(window, key_callback);
        glfwPollEvents();
        glfwSwapBuffers(window);
    } 
glDeleteVertexArrays(1, &cuadrado_vao);
glDeleteBuffers(1, &cuadrado_vbo);
glDeleteVertexArrays(1, &triangulo_vao);
glDeleteBuffers(1, &triangulo_vao);
glDeleteVertexArrays(1, &pentagono_vao);
glDeleteBuffers(1, &pentagono_vao);

glfwTerminate();
}

void primera_escena(unsigned int *transformLoc, unsigned int *triangulo_vao){
        glClearColor(0.68f, 0.37f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(*triangulo_vao);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(*transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
}

void segunda_escena(unsigned int *transformLoc, unsigned int *cuadrado_vao){
        glClearColor(0.57f, 0.16f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(*cuadrado_vao);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -1.0f));
        glUniformMatrix4fv(*transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}

void tercera_escena(unsigned int *transformLoc, unsigned int *pentagono_vao, unsigned int *triangulo_vao, unsigned int *cuadrado_vao){
        glClearColor(0.16f, 0.71f, 0.39f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(*triangulo_vao);
        glm::mat4 trans = glm::mat4(1.0f);
        x = (cos(acumulador ) * 0.7);
        y = (sin(acumulador ) * 0.7);
        if(acumulador >6.28 )
            acumulador =0.00000;
        else
            acumulador +=0.001;

        trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.2, 0.2, 0));
        glUniformMatrix4fv(*transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glBindVertexArray(*cuadrado_vao);
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-x, -y, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -1.0f));
        trans = glm::scale(trans, glm::vec3(0.2, 0.2, 0));
        glUniformMatrix4fv(*transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(*pentagono_vao);
        trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(*transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}

void check_shader_program_status(int shaderProgram)
{   
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
void check_shader_compile_status(int vertexShader){
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{   
    if(key == GLFW_KEY_RIGHT){
        switch (action ) {
            case GLFW_PRESS:
                    if(escenario < 3){
                        escenario+=1;
                    }
                    else if(escenario == 3){
                        escenario=1;
                    }
                    break;
            case  GLFW_REPEAT:
                    break;
            }
    }
    if(key == GLFW_KEY_LEFT){
        switch (action ) {
            case GLFW_PRESS:
                    if(escenario > 1){
                        escenario-=1;
                    }
                    else if(escenario == 1){
                        escenario=3;
                    }
                    break;
            case  GLFW_REPEAT:
                    break;
            }
    }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  