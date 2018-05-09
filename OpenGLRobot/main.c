//
//  main.c
//  OpenGLRobot
//
//  Created by Tsz Ting Yu on 5/3/18.
//  Copyright © 2018 Tsz Ting Yu. All rights reserved.
//
// System Headers
/*
 
 
 //---------------------------------------------------------------------------------------------------------------
 //learnGl.com
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <stdio.h>


//Variables
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//color object/fill in
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
//triangles
float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f, -0.5f, 0.0f, // right
    0.0f,  0.5f, 0.0f  // top
};

//Rectangle
float rectangle[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

//Object
typedef struct cell{
    
}Cell;
//Prototype
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow*);
void renderGrid();
void drawTrangle();
//--------------------------------------------------------------------------------------------------------------------
//Function definitions

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//process key input
void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,1);
    }
}
//rendering
void renderGrid(){

}
void drawTriangle(){
    
}

//-------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   //needed for mac... Not sure why

    GLFWwindow* window = glfwCreateWindow(800,600,"Test",NULL,NULL);
    if(window == NULL){
        printf("Failed to create window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    //load Glad --> change some settings depends on operating system
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }
    
    
    //initialize buffer
    unsigned int VBO,VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    
    //bind array first then set the buffer
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO later; 0 = cancel the connection between GL_ARRAY_BUFFER and VBO
    glBindVertexArray(0); //unbind VAO later
    
    //initialize shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }
    //attaching shader to a shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::SHADERPROGRAM::LINKING_FAILED\n");
    }
    //we can delete the shading program after we link it to the project/program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
 

    while(!glfwWindowShouldClose(window)) {
        //check input
        processInput(window);
        //rendering
        //1.clearScreen-->clearing screen color buffer
        glClearColor(1.0f,1.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //actural drawing
        

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    
    //de-allocate resources
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate(); //Needs to terminate window before exit
    return 0;

}*/


//---------------------------------------------------------------------------------------------
//GLFW 2D
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//Struct
typedef struct cell{
    int x;  //coordinates
    int y;
    
    int value; //1 or 0 represent obstacles
}Cell;

typedef struct car{
    int x;
    int y;
}Car;


enum Control{
    Up,
    Down,
    Left,
    Right
};

//Prototype
void drawGrid(void);
void drawObstacle(Cell**); //take in the gameMap array to check whether value = 1, if so, draw cube
void drawCar(Car*);


Cell** initCell(void);
void generateRandomObstacle(Cell**);
void updateCar(Car*, int);

//const Variables
const int gridSize = 32;
const int gridNum = 10;
const int SCREEN_WIDTH = gridSize*gridNum + 100;
const int SCREEN_HEIGHT = gridSize*gridNum + 100;


Car* car = NULL;
//Function Definition
static void inputK(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        updateCar(car,Left);
    }
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        updateCar(car,Right);
    }
    if(key == GLFW_KEY_UP && action == GLFW_PRESS){
        updateCar(car,Up);
    }
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        updateCar(car,Down);
    }
}

static void error_callback(int error, const char* description){
    fputs(description, stderr);
}

void updateCar(Car* car, int num){
    //see enum Control
    if(num == 0){
        if(car->y > 50){
        car->y = (car->y) - gridSize;
        }
    }
    if(num == 1){
        if(car->y <SCREEN_HEIGHT-(50+gridSize)){
        car->y = (car->y) + gridSize;
        }
    }
    if(num == 2){
        if(car->x >50){
        car->x = (car->x) - gridSize;
        }

    }
    if(num == 3){
        if(car->x < SCREEN_WIDTH-(50+gridSize)){
        car->x = (car->x) + gridSize;
        }
    }
}
void drawCar(Car* car){
    //draw obstacle
    glColor3d(1.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(car->x, car->y);
    glVertex2f(car->x+gridSize, car->y);
    glVertex2f(car->x+gridSize, car->y+gridSize);
    glVertex2f(car->x, car->y+gridSize);
    glEnd();

}

void drawGrid(){
    glColor3d(0.8, 0.8, 0.8);
    //attempt to draw lines
    glBegin(GL_LINES);
    //horizontal
    for (int i = 50; i <= SCREEN_HEIGHT-50; i+=gridSize){
        glVertex2f(50, i);
        glVertex2f(SCREEN_WIDTH-50 ,i);
    }
    //vertical
    for (int i = 50; i <= SCREEN_WIDTH-50; i += gridSize){
        glVertex2f(i,50);
        glVertex2f(i, SCREEN_HEIGHT-50);
    }
    glEnd();
}

Cell** initCell(){ //initialize a 10x10 cell
    Cell** gameMap = (Cell**)malloc(gridNum*sizeof(Cell*));
    int x = 50;
    int y = 50;
    
    srand(time(0));
    for(int i = 0; i<gridNum;i++){
        *(gameMap+i) = (Cell*)calloc(gridNum, sizeof(Cell));
        for(int k = 0; k<gridNum;k++){
            if(rand()%10 < 2){
                
                gameMap[i][k].value = 1;
            }
            else{
                
                gameMap[i][k].value = 0;
            }
            gameMap[i][k].x = x;
            gameMap[i][k].y = y;
            x+=gridSize;
        }
        x=50;
        y+=gridSize;
    }
    return gameMap;
}


void drawObstacle(Cell** gameMap){
    //draw obstacle
    glColor3d(0.0, 0.7, 1.0);
    for(int i = 0 ; i<gridNum; i++){
        for(int k = 0; k<gridNum; k++){
            if(gameMap[i][k].value != 0){
                glBegin(GL_QUADS);
                glVertex2f(gameMap[i][k].x, gameMap[i][k].y);
                glVertex2f(gameMap[i][k].x+gridSize, gameMap[i][k].y);
                glVertex2f(gameMap[i][k].x+gridSize, gameMap[i][k].y+gridSize);
                glVertex2f(gameMap[i][k].x, gameMap[i][k].y+gridSize);
                glEnd();
            }
            else{}
        }
    }
}


int main(void){
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MSSIN_no", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, inputK);
    
    Cell** gameMap = initCell();
    //initial car and its position
    car = malloc(sizeof(Car));
    car->x = 50;
    car->y = 50;
    
    while (!glfwWindowShouldClose(window)){
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClearColor(1.0f,1.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        
        glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT,0, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        drawGrid();
        drawObstacle(gameMap);
        drawCar(car);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
