#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 Posnface = glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
int cameraspin=0;
float deltaTime=0.0f;
float lastFrame=0.0f;
glm::mat4 model = glm::mat4(1.0f);
int main()
{
    int val;
    std::cin>>val;
    glfwInit();
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "A0", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    Shader newshader(0);
    float elongatedsquaredipyramidalvertices[]={
    	//Triangle1
    	0.0f,0.0f,1.0f,  0.0f,0.0f,0.0f,
    	0.5f,0.5f,0.5f, 0.0f,0.0f,0.0f,
    	-0.5f,0.5f,0.5f,  0.0f,0.0f,0.0f,
    	//Triangle2
    	0.0f,0.0f,1.0f,  0.5f,0.0f,0.0f,
    	0.5f,0.5f,0.5f, 0.5f,0.0f,0.0f,
    	0.5f,-0.5f,0.5f,  0.5f,0.0f,0.0f,
    	//Triangle3
    	0.0f,0.0f,1.0f,  1.0f,0.0f,0.0f,
    	0.5f,-0.5f,0.5f, 1.0f,0.0f,0.0f,
    	-0.5f,-0.5f,0.5f,  1.0f,0.0f,0.0f,    
    	//Triangle4
    	0.0f,0.0f,1.0f,  1.0f,0.5f,0.0f,
    	-0.5f,0.5f,0.5f, 1.0f,0.5f,0.0f,
    	-0.5f,-0.5f,0.5f,  1.0f,0.5f,0.0f,
    	//Square1
    	0.5f,0.5f,0.5f,  1.0f,1.0f,0.0f,
    	0.5f,-0.5f,0.5f, 1.0f,1.0f,0.0f,
    	0.5f,0.5f,-0.5f,  1.0f,1.0f,0.0f,
    	0.5f,-0.5f,-0.5f, 1.0f,1.0f,0.0f,
    	//Square2
    	0.5f,0.5f,0.5f, 1.0f,1.0f,0.5f,
    	-0.5f,0.5f,0.5f, 1.0f,1.0f,0.5f,
    	0.5f,0.5f,-0.5f, 1.0f,1.0f,0.5f,
    	-0.5f,0.5f,-0.5f, 1.0f,1.0f,0.5f,
    	//Square3
    	-0.5f,-0.5f,0.5f,1.0f,1.0f,1.0f,
    	-0.5f,0.5f,0.5f,1.0f,1.0f,1.0f,
    	-0.5f,-0.5f,-0.5f,1.0f,1.0f,1.0f,
    	-0.5f,0.5f,-0.5f,1.0f,1.0f,1.0f,
    	//Square4
    	-0.5f,-0.5f,0.5f,1.0f,0.0f,1.0f,
    	0.5f,-0.5f,0.5f,1.0f,0.0f,1.0f,
    	-0.5f,-0.5f,-0.5f,1.0f,0.0f,1.0f,
    	0.5f,-0.5f,-0.5f,1.0f,0.0f,1.0f,
    	//Triangle5
    	0.0f,0.0f,-1.0f,  0.5f,0.5f,0.5f,
    	0.5f,0.5f,-0.5f, 0.5f,0.5f,0.5f,
    	-0.5f,0.5f,-0.5f,  0.5f,0.5f,0.5f,
    	//Triangle6
    	0.0f,0.0f,-1.0f,  0.5f,0.5f,0.0f,
    	0.5f,0.5f,-0.5f, 0.5f,0.5f,0.0f,
    	0.5f,-0.5f,-0.5f,  0.5f,0.5f,0.0f, 	
    	//Triangle7
    	0.0f,0.0f,-1.0f,  0.0f,0.5f,0.5f,
    	0.5f,-0.5f,-0.5f, 0.0f,0.5f,0.5f,
    	-0.5f,-0.5f,-0.5f,  0.0f,0.5f,0.5f,
    	//  Triangle8
    	0.0f,0.0f,-1.0f,  0.5f,0.0f,0.5f,
    	-0.5f,0.5f,-0.5f, 0.5f,0.0f,0.5f,
    	-0.5f,-0.5f,-0.5f,  0.5f,0.0f,0.5f,
    };
    unsigned int elongatedsquaredipyramidalindices[]={
    	0,1,2,
    	3,4,5,
    	6,7,8,
    	9,10,11,
    	//Square1
    	12,13,14,
    	13,14,15,
    	//Square2
    	16,17,18,
    	17,18,19,
    	//Square3
    	20,21,22,
    	21,22,23,
    	//Square4
    	24,25,26,
    	25,26,27,
    	//Triangles
    	28,29,30,
    	31,32,33,
    	34,35,36,
    	37,38,39,
    };
    float n=(sqrt(5)+1)/2;
    float b=(float)1/n;
    b=b/((float) 2);
    float c=1-(n/2);
    std::cout << b << "  ni  " <<  c << "\n";
    float dodecahedronvertices[] = {
        // positions         // colors
        //First Face
        c,  0.0f,  0.5f,  0.0f, 0.0f, 0.0f,
        -c,  0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 
        -b,  b,  b,  0.0f, 0.0f, 0.0f, 
        0.0f,  0.5f,  c,  0.0f, 0.0f, 0.0f,
        b,  b,  b,  0.0f, 0.0f, 0.0f,  
        //Second Face
        -c,  0.0f,  0.5f,  0.5f, 0.0f, 0.0f,
        c,  0.0f,  0.5f,  0.5f, 0.0f, 0.0f,
        b,  -b,  b,  0.5f, 0.0f, 0.0f,
        0.0f, -0.5f, c,  0.5f, 0.0f, 0.0f,
        -b,  -b,  b,  0.5f, 0.0f, 0.0f,
        //ThirdFace
        c,  0.0f,  -0.5f,  1.0f, 0.0f, 0.0f,
        -c,  0.0f,  -0.5f,  1.0f, 0.0f, 0.0f,
        -b,  -b,  -b,  1.0f, 0.0f, 0.0f,
        0.0f,  -0.5f,  -c,  1.0f, 0.0f, 0.0f,
        b,  -b,  -b,  1.0f, 0.0f, 0.0f,
        //FourthFace
        -c,  0.0f,  -0.5f,  1.0f, 0.5f, 0.0f,
        c,  0.0f,  -0.5f,  1.0f, 0.5f, 0.0f,
        b,  b,  -b,  1.0f, 0.5f, 0.0f,
        0.0f,  0.5f,  -c,  1.0f, 0.5f, 0.0f,
        -b,  b,  -b,  1.0f, 0.5f, 0.0f,
        //FifithFace
        0.0f,  0.5f,  -c,  1.0f, 1.0f, 0.0f,
        0.0f,  0.5f,  c,  1.0f, 1.0f, 0.0f,
        b,  b,  b,  1.0f, 1.0f, 0.0f,
        0.5f,c,0.0f, 1.0f,1.0f,0.0f,
        b,  b,  -b,  1.0f, 1.0f, 0.0f,
        //SixthFace
        0.0f,  0.5f,  c,  1.0f, 1.0f, 0.5f,
        0.0f,  0.5f,  -c,  1.0f, 1.0f, 0.5f,
        -b,  b,  -b,  1.0f, 1.0f, 0.5f,
        -0.5f,c,0.0f, 1.0f,1.0f,0.5f,
        -b,  b,  b,  1.0f, 1.0f, 0.5f,
        //Seventh Faces
        0.0f,  -0.5f,  -c,  1.0f, 1.0f, 1.0f,
        0.0f,  -0.5f,  c,  1.0f, 1.0f, 1.0f,
        -b,  -b,  b,  1.0f, 1.0f, 1.0f,
        -0.5f,-c,0.0f, 1.0f,1.0f,1.0f,
        -b,  -b,  -b,  1.0f, 1.0f, 1.0f,    
        //Eigth Face
        0.0f,  -0.5f,  c,  0.25f, 0.25f, 0.25f,
        0.0f,  -0.5f,  -c,  0.25f, 0.25f, 0.25f,
        b,  -b,  -b,  0.25f, 0.25f, 0.25f,
        0.5f,-c,0.0f, 0.25f,0.25f,0.25f,
        b,  -b,  b,  0.25f, 0.25f, 0.25f,
        //Ninth Face
        0.5f,c,0.0f, 0.5f,0.5f,0.0f,
        0.5f,-c,0.0f, 0.5f,0.5f,0.0f,   
        b,-b,b, 0.5f,0.5f,0.0f,
        c,0.0f,0.5f,  0.5f,0.5f,0.0f,
        b,b,b, 0.5f,0.5f,0.0f,
        //Tenth Face
        0.5f,-c,0.0f, 0.0f,0.5f,0.5f,
        0.5f,c,0.0f, 0.0f,0.5f,0.5f,    
        b,b,-b, 0.0f,0.5f,0.5f,
        c,0.0f,-0.5f,  0.0f,0.5f,0.5f,
        b,-b,-b, 0.0f,0.5f,0.5f,
        //11th face
        -0.5f,c,0.0f, 0.5f,0.0f,0.5f,
        -0.5f,-c,0.0f, 0.5f,0.0f,0.5f,  
        -b,-b,-b, 0.5f,0.0f,0.5f,
        -c,0.0f,-0.5f,  0.5f,0.0f,0.5f,
        -b,b,-b, 0.5f,0.0f,0.5f,
        //12th face
        -0.5f,-c,0.0f, 0.75f,0.0f,0.5f,
        -0.5f,c,0.0f, 0.75f,0.0f,0.5f,  
        -b,b,b, 0.75f,0.0f,0.5f,
        -c,0.0f,0.5f,  0.75f,0.0f,0.5f,
        -b,-b,b, 0.75f,0.0f,0.5f,   
    };
    unsigned int dodecahedronindices[]={
        //First Pentagon
        0,1,2,
        0,2,3,
        0,3,4,
        //Second Pentagon
        5,6,7,
        5,7,8,
        5,8,9,
        //Third Pentagon
        10,11,12,
        10,12,13,
        10,13,14,
        //FourthPentagon
        15,16,17,
        15,17,18,
        15,18,19,
        //FifthPentagon
        20,21,22,
        20,22,23,
        20,23,24,
        //Sixth
        25,26,27,
        25,27,28,
        25,28,29,
        //Seventh
        30,31,32,
        30,32,33,
        30,33,34,
        //Eight
        35,36,37,
        35,37,38,
        35,38,39,
        //Nine
        40,41,42,
        40,42,43,
        40,43,44,
        //Ten
        45,46,47,
        45,47,48,
        45,48,49,
        //11
        50,51,52,
        50,52,53,
        50,53,54,
        //12
        55,56,57,
        55,57,58,
        55,58,59,
    };
    //std::cout << sin(30*(3.14159265359)/180) << "\n" << sin(30*(3.14159265359)/180);
    float hexagonaldipyramidalvertices[]={
        //Traingle1
        0.0f,0.0f,1.0f, 0.0f, 0.0f, 0.0f,
        0.0f,1.0f,0.0f, 0.0f, 0.0f, 0.0f,
        cos(30*(3.14159265359)/180),sin(30*(3.14159265359)/180),0.0f, 0.0f, 0.0f, 0.0f,
        //Triangle2
        0.0f,0.0f,1.0f, 0.5f,0.0f,0.0f,
        0.0f,1.0f,0.0f, 0.5f,0.0f,0.0f,
        -cos(30*(3.14159265359)/180),sin(30*(3.14159265359)/180),0.0f, 0.5f,0.0f,0.0f,
        //Triangle3
        0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,
        -cos(30*(3.14159265359)/180),sin(30*(3.14159265359)/180),0.0f, 1.0f,0.0f,0.0f,
        -cos(30*(3.14159265359)/180),-sin(30*(3.14159265359)/180),0.0f, 1.0f,0.0f,0.0f,
        //Triangle4
        0.0f,0.0f,1.0f, 1.0f,0.5f,0.0f,
        cos(30*(3.14159265359)/180),sin(30*(3.14159265359)/180),0.0f, 1.0f,0.5f,0.0f,
        cos(30*(3.14159265359)/180),-sin(30*(3.14159265359)/180),0.0f, 1.0f,0.5f,0.0f,      
        //Traingle5
        0.0f,0.0f,1.0f, 1.0f, 1.0f, 0.0f,
        0.0f,-1.0f,0.0f, 1.0f, 1.0f, 0.0f,
        -cos(30*(3.14159265359)/180),-sin(30*(3.14159265359)/180),0.0f, 1.0f, 1.0f, 0.0f,
        //Triangle6
        0.0f,0.0f,1.0f, 1.0f,1.0f,0.5f,
        0.0f,-1.0f,0.0f, 1.0f,1.0f,0.5f,
        cos(30*(3.14159265359)/180),-sin(30*(3.14159265359)/180),0.0f, 1.0f,1.0f,0.5f,
        //Traingle7
        0.0f,0.0f,-1.0f, 1.0f, 1.0f, 1.0f,
        0.0f,1.0f,0.0f, 1.0f, 1.0f, 1.0f,
        cos(30*(3.14159265359)/180),sin(30*(3.14159265359)/180),0.0f, 1.0f, 1.0f, 1.0f,
        //Triangle8
        0.0f,0.0f,-1.0f, 0.25f,0.25f,0.25f,
        0.0f,1.0f,0.0f, 0.25f,0.25f,0.25f,
        -cos(30*(3.14159265359)/180),sin(30*(3.14159265359)/180),0.0f, 0.25f,0.25f,0.25f,
        //Triangle9
        0.0f,0.0f,-1.0f, 0.5f,0.5f,0.5f,
        -cos(30*(3.14159265359)/180),sin(30*(3.14159265359)/180),0.0f, 0.5f,0.5f,0.5f,
        -cos(30*(3.14159265359)/180),-sin(30*(3.14159265359)/180),0.0f, 0.5f,0.5f,0.5f,
        //Triangle10
        0.0f,0.0f,-1.0f, 0.5f,0.5f,0.0f,
        cos(30*(3.14159265359)/180),sin(30*(3.14159265359)/180),0.0f, 0.5f,0.5f,0.0f,
        cos(30*(3.14159265359)/180),-sin(30*(3.14159265359)/180),0.0f, 0.5f,0.5f,0.0f,      
        //Traingle11
        0.0f,0.0f,-1.0f, 0.5f, 0.0f, 0.5f,
        0.0f,-1.0f,0.0f, 0.5f, 0.0f, 0.5f,
        -cos(30*(3.14159265359)/180),-sin(30*(3.14159265359)/180),0.0f, 0.5f, 0.0f, 0.5f,
        //Triangle12
        0.0f,0.0f,-1.0f, 0.5f,1.0f,0.5f,
        0.0f,-1.0f,0.0f, 0.5f,1.0f,0.5f,
        cos(30*(3.14159265359)/180),-sin(30*(3.14159265359)/180),0.0f, 0.5f,1.0f,0.5f,
    };
    unsigned int hexagonaldipyramidalindices[]={
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11,
        12,13,14,
        15,16,17,
        18,19,20,
        21,22,23,
        24,25,26,
        27,28,29,
        30,31,32,
        33,34,35,
    };
    unsigned int VBO, VAO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if(val==1){
    glBufferData(GL_ARRAY_BUFFER, sizeof(elongatedsquaredipyramidalvertices), elongatedsquaredipyramidalvertices, GL_STATIC_DRAW);
    }
    if(val==2){
    glBufferData(GL_ARRAY_BUFFER, sizeof(dodecahedronvertices), dodecahedronvertices, GL_STATIC_DRAW);
    }
    if(val==3){
    glBufferData(GL_ARRAY_BUFFER, sizeof(hexagonaldipyramidalvertices), hexagonaldipyramidalvertices, GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    if(val==1){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elongatedsquaredipyramidalindices),elongatedsquaredipyramidalindices,GL_STATIC_DRAW);
    }
    if(val==2){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dodecahedronindices),dodecahedronindices, GL_STATIC_DRAW);
    }
    if(val==3){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hexagonaldipyramidalindices), hexagonaldipyramidalindices, GL_STATIC_DRAW);
    }
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
   	glUseProgram(newshader.ID);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    newshader.setMat4("projection", projection);
    while (!glfwWindowShouldClose(window))
    {
        float curr=glfwGetTime();
        deltaTime=curr-lastFrame;
        lastFrame=curr;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        newshader.use();
        glm::mat4 view;
        if(cameraspin==0)
        	view = glm::lookAt(cameraPos, Posnface, cameraUp);
        else{
       		const float radius=length(cameraPos);
       		float camX=sin(glfwGetTime()) * radius;
       		float camY = cos(glfwGetTime()) * radius;
       		view = glm::lookAt(glm::vec3(camX,0.0,camY),Posnface,cameraUp);
        }
        newshader.setMat4("view", view);
        unsigned int modelLoc = glGetUniformLocation(newshader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        if(val==2)
        glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);
        if(val==3)
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
        if(val==1)
        glDrawElements(GL_TRIANGLES,51,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1,&EBO);
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window,GLFW_KEY_P)==GLFW_PRESS)
    	model=glm::translate(model,glm::vec3(0.01f,0.0f,0.0f));
    if (glfwGetKey(window,GLFW_KEY_O)==GLFW_PRESS)
    	model=glm::translate(model,glm::vec3(-0.01f,0.0f,0.0f));
    if (glfwGetKey(window,GLFW_KEY_L)==GLFW_PRESS)
    	model=glm::translate(model,glm::vec3(0.0f,0.01f,0.0f));
    if (glfwGetKey(window,GLFW_KEY_K)==GLFW_PRESS)
    	model=glm::translate(model,glm::vec3(0.0f,-0.01f,0.0f));
    if (glfwGetKey(window,GLFW_KEY_M)==GLFW_PRESS)
    	model=glm::translate(model,glm::vec3(0.0f,0.0f,0.01f));
    if (glfwGetKey(window,GLFW_KEY_N)==GLFW_PRESS)
    	model=glm::translate(model,glm::vec3(0.0f,0.0f,-0.01f));
    if (glfwGetKey(window,GLFW_KEY_R)==GLFW_PRESS)
    	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f)); 
    float cameraSpeed = 0.5 * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
    if (glfwGetKey(window,GLFW_KEY_Z) == GLFW_PRESS)
    	cameraPos=glm::vec3(1.0f,0.0f,3.0f);
    if (glfwGetKey(window,GLFW_KEY_X) == GLFW_PRESS)
    	cameraPos=glm::vec3(1.0f,1.0f,3.0f);
    if (glfwGetKey(window,GLFW_KEY_C) == GLFW_PRESS)
    	cameraPos=glm::vec3(-1.0f,0.5f,3.0f);
    if(glfwGetKey(window,GLFW_KEY_T))
    	cameraspin=1;
    if(glfwGetKey(window,GLFW_KEY_Y))
    	cameraspin=0;

}	
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
