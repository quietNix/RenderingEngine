#include <iostream>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLCheckError.h"
#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace std;

//global attributes
Window mainWindow= Window(800, 640);
int bufferLength;
glm::mat4 proj;
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 1.0f, 0.05f);

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

//function attributes
void CreateTriangle(vector<float>& position, vector<unsigned int>& indice);

void RenderingGraphics(VertexArray& va, IndexBuffer& ib, Shader& shader, Texture& tex1);


int main(void)
{
    /************************************************Basic open gl Setup***************************************/

    mainWindow.Initialise();


    /**************************************Creation And Loading of graphics***************************************/
    {       //scope
        vector<float> position;
        vector<unsigned int> indice;

        //Algorithm for core graphics creation
        CreateTriangle(position, indice);

        //Setting cordinates to gpu buffer
        float* positions = &position[0];
        unsigned int* indices = &indice[0];


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        VertexArray va;
        VertexBuffer vb(positions, position.size() * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(layout);

        vb.Unbind();
        va.Unbind();


        IndexBuffer ib(indices, indice.size() * (sizeof(unsigned int)));

        ib.Unbind();

        /************************************************Shaders***************************************/
        Shader shader("res/shaders/basic.shader");
        shader.Bind();
        

        Texture tex0("res/textures/joker.png");
        Texture tex1("res/textures/initial.png");
        Texture tex2("res/textures/final.png");
        tex0.Bind(0);
        tex1.Bind(1);
        tex2.Bind(2);


        shader.SetUniform1i("u_Texture", 1);      //if there is only one texture, this line is useless...it happens by default.
        //shader.SetUniformMat4f("u_MVP", proj);
        
        shader.Unbind();
        /************************************************camera**********************************************/
        

        /********************************************RenderingGraphics***************************************/
        RenderingGraphics(va, ib, shader, tex1);

        /***********************************Clearing the buffer and gpu's used memory***************************************/
   
        //glDeleteProgram(shader);          //scope is taking care of it...hopefully
        
    }
    
    glfwTerminate();
    return 0;
}

void RenderingGraphics(VertexArray& va, IndexBuffer& ib, Shader& shader, Texture& tex1)
{
    Renderer renderer;
    float r{ 0.0f };
    float inc{ 0.01f };

    renderer.Bind(va, ib, shader);

    glm::mat4 projection = glm::perspective(45.0f, (float)mainWindow.getBufferWidth()/(float)mainWindow.getBufferHeight(), 0.1f, 100.0f);



    while (!mainWindow.getShouldClose())
    {
        
        glClearColor(0.2005, 0.3522, 0.4473, 1.0f);                      //destination buffer color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);             //renderer.Draw(ib);
        
        /**********************************translation, rotation, scaling**********************************************/
        //camera movement
        GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
        deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
        lastTime = now;

        camera.keyControl(mainWindow.getsKeys(), deltaTime);                        //translation motion
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());


        // Create transformations
        
        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f)); 
        glm::mat4 view = camera.calculateViewMatrix();
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * 0.0f, glm::vec3(0.5f, 1.0f, 1.0f));
        shader.SetUniformMat4f("u_Transform", projection * view * model);

        //color changing
        //shader.SetUniform4f("u_Color", r, 0.02f, 0.05f, r);             //src buffer color...using blending glBlendFunc
                                                                        //last alpha only works when texture has transparent bits.
        if (r > 1.0f)
            inc = -0.01f;
        else if (r < 0.0f)
            inc = 0.01f;
        r += inc;

        // Swap front and back buffers
        GLCall(mainWindow.swapBuffers());

        // Poll for and process events
        glfwPollEvents();
    }
}


void CreateTriangle(vector<float>& position, vector<unsigned int>& indice)
{
    //vertexPositions of a vertex
    position = {

        //anticlockwise from top left
        //-0.5f,  0.5f,    0.0f, 0.0f, //left  top     back     0
        //-0.5f, -0.5f,    0.0f, 1.0f, //left  bottom  back     1
        // 0.5f, -0.5f,    1.0f, 1.0f, //right bottom  back     2
        // 0.5f,  0.5f,    1.0f, 0.0f  //right top     back     3


        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,     //left  top     back     0 
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,     //left  bottom  back     1 
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f,     //right bottom  back     2 
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f,     //right top     back     3 
                                         
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,     //left  top     front    4 
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,     //left  bottom  front    5 
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f,     //right bottom  front    6 
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,     //right top     front    7 
                                                      
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,     //left  top     back     8 
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,     //left  bottom  back     9 
        -0.5f, -0.5f,  0.5f,   1.0f, 1.0f,     //left  bottom  front    10
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,     //left  top     front    11

         0.5f,  0.5f, -0.5f,   0.0f, 0.0f,     //right  top     back    12
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,     //right  bottom  back    13
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f,     //right  bottom  front   14
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,     //right  top     front   15

        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,     //left   top     back    16
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,     //right  top     back    17
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,     //right  top     front   18
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,     //left   top     front   19

        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,     //left   bottom  back    20
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,     //right  bottom  back    21
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f,     //right  bottom  front   22
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f      //left   bottom  front   23
    };

    indice = {
        //0, 1, 2,
        //2, 3, 0,


        0, 1, 2,       //back face
        2, 3, 0,       //back face

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
}