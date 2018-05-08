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

//------------------------------------------------------------------------------------------------------------
//GLUT 3D
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__              //version check
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif


#define PI 3.14159265

//global variable
int _WindowPositionX = 200;
int _WindowPositionY = 200;
int _WindowWidth = 512;
int _WindowHeight = 512;
char _WindowTitle[] = "test";
int tn = 0;
double t = 0;
double dt = 1;
double omega = PI / 180.0;  //angle for the camera
int isClockwise = 0;
//Prototypes
void initialize(void);
void display(void);
void renderGround(void);
void idle(void);
void normalKeyboard(unsigned char, int, int);
void specialKey(int, int, int);
//----------------------------------------------------
// define viewPoint
//----------------------------------------------------
double _ViewPointX = 200.0;
double _ViewPointY = 0.0;
double _ViewPointZ = 20.0;
//----------------------------------------------------
// defining rectangle/self-defined object
//----------------------------------------------------
GLdouble vertex[][3] = {
    { 0.0, 0.0, 0.0 },
    { 2.0, 0.0, 0.0 },
    { 2.0, 2.0, 0.0 },
    { 0.0, 2.0, 0.0 },
    { 0.0, 0.0, 30.0 },
    { 2.0, 0.0, 30.0 },
    { 2.0, 2.0, 30.0 },
    { 0.0, 2.0, 30.0 }
};
int face[][4] = {//defining face of the rectangle
    { 0, 1, 2, 3 },
    { 1, 5, 6, 2 },
    { 5, 4, 7, 6 },
    { 4, 0, 3, 7 },
    { 4, 5, 1, 0 },
    { 3, 2, 6, 7 }
};
GLdouble normal[][3] = {//defining the in/out of the face for the defined object
    { 0.0, 0.0,-1.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    {-1.0, 0.0, 0.0 },
    { 0.0,-1.0, 0.0 },
    { 0.0, 1.0, 0.0 }
};
//----------------------------------------------------
// defining texture
//----------------------------------------------------
typedef struct MaterialStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
}MaterialStruct;
//jade

MaterialStruct ms_jade = {
    {0.135,     0.2225,   0.1575,   1.0},
    {0.54,      0.89,     0.63,     1.0},
    {0.316228,  0.316228, 0.316228, 1.0},
    12.8};
//ruby
MaterialStruct ms_ruby  = {
    {0.1745,   0.01175,  0.01175,   1.0},
    {0.61424,  0.04136,  0.04136,   1.0},
    {0.727811, 0.626959, 0.626959,  1.0},
    76.8};
//----------------------------------------------------
// color definition
//----------------------------------------------------
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess = 30.0;
//-----------------------------------------

int main(int argc, char **argv) {
    
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(_WindowPositionX, _WindowPositionY);
    glutInitWindowSize(_WindowWidth, _WindowHeight);
    glutCreateWindow(_WindowTitle);//create the window; parameter = title
    glutIdleFunc(idle); //must have if there's animation involve
    
    glutDisplayFunc(display); //call render function
    initialize();
    
    //Processing keyboard input
    glutKeyboardFunc(normalKeyboard);
    glutSpecialFunc(specialKey);
    
    glutMainLoop();
    return 0;
    
}

//Initialize window setting
void initialize(void){
    glClearColor(1.0,1.0,1.0,0.0); //background
    glEnable(GL_DEPTH_TEST);
    
    //------------------------------------------------
    //settling light source
    //--------------------------------------
    GLfloat light_position0[] = { 50.0, 50.0, 20.0, 1.0 }; //light0 coordinate
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //setting light zero; GL_LIGHT{0-8} at least
    
    /*
     //Projection
     glMatrixMode(GL_PROJECTION);//Specify matrix（GL_PROJECTION : camera、GL_MODELVIEW：model/object）
     glLoadIdentity();//initialize matrix
     gluPerspective(30.0, (double)_WindowWidth/(double)_WindowHeight, 0.1, 1000.0); //defining a view frustum;gluPerspactive(th, w/h, near, far);
     //setting viewpoint from point (a) viewing point (b)
     gluLookAt(
     0.0, -100.0, 50.0, // Viewpoint position x,y,z; (a)
     0.0, 100.0, 20.0,   // position of the reference point x,y,z (b)
     0.0, 0.0, 1.0);  //direction of the up vector x,y,z; in this case, z is the height, y is depth
 
}
 */
/*
void idle(){
    glutPostRedisplay(); //calling glutDisplayFunc() for once
}

void specialKey(int key , int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            tn = isClockwise<0? -tn:tn;
            t = dt * tn;
            _ViewPointX = 200.0 * cos( omega * t);
            _ViewPointY = 200.0 * sin( omega * t);
            isClockwise = 1;
            tn+=10;
            
            break;
        case GLUT_KEY_RIGHT:
            tn = isClockwise>0? -tn:tn;
            isClockwise = -1;
            t = dt * tn;
            _ViewPointX = 200.0 * cos( omega * t);
            _ViewPointY = -200.0 * sin( omega * t);
            tn+=10;
            break;
        case GLUT_KEY_UP:
            _ViewPointZ +=10;
            break;
        case GLUT_KEY_DOWN:
            _ViewPointZ -=10;
            break;
        default:
            break;
    }
}

void normalKeyboard(unsigned char key, int x, int y){
    switch ( key ){
        case 'd': //Counterclocwise
            tn = isClockwise>0? -tn:tn;
            isClockwise = -1;
            t = dt * tn;
            _ViewPointX = 200.0 * cos( omega * t);
            _ViewPointY = -200.0 * sin( omega * t);
            tn++;
            
            break;
        case 'a': //Clockwise
            tn = isClockwise<0? -tn:tn;
            t = dt * tn;
            _ViewPointX = 200.0 * cos( omega * t);
            _ViewPointY = 200.0 * sin( omega * t);
            isClockwise = 1;
            tn++;
            break;
        case 'q':
            exit(0);
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}



//main function to render; can call other drawing function.
void display(void) {   //function for rendering
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear buffer
    
    //Projection matrix-------------------------------------------
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (double)_WindowWidth/(double)_WindowHeight, 0.1, 1000.0);
    //viewPoint---------------------------------------------------
    gluLookAt(
              _ViewPointX,  _ViewPointY    ,  _ViewPointZ,
              0.0, 0.0,   0.0,
              0.0,    0.0,   1.0 );
    //------------------------------------------------------------
    
    
    //setting the viewpoint to modelview--------------------------
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//initialize model matrix
    glViewport(0, 0, _WindowWidth, _WindowHeight);
    //------------------------------------------------------------
    //shadow ON---------------------------------------------------
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);//using light0
    //------------------------------------------------------------
    
    //Cube
    glPushMatrix(); //save current state ; often use with popMatrix so that we can return to original state
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
    //glColor3d(0.0, 1.0, 0.0);//color setting; if light present, this function call will become useless
    glTranslated(-20.0, 0.0, 20.0);//translation
    glutSolidCube(10.0);//draw cube：(side length)
    glPopMatrix(); //load savefile
    
    //Sphere
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);
    glTranslated(0.0, 10.0, 20.0);
    glutSolidSphere(4.0, 20, 20);//Parameter:(radius, The number of subdivisions around the Z axis (similar to lines of longitude), The number of subdivisions along the Z axis (similar to lines of latitude))
    glPopMatrix();
    
    //Cone
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
    glTranslated(20.0, 100.0, 0.0);
    glutSolidCone(5.0,10.0,20,20);//Parameter：(radius, height, "longitude", "Latitude")
    glPopMatrix();
    
    //torus
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);
    glRotated(90, 0, 1 , 0);
    glutSolidTorus(3,4.0,20,20);
    glPopMatrix();
    
    //Rectangle
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, ms_jade.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_jade.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ms_jade.specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &ms_jade.shininess);
    glColor3d(0.0, 1.0, 1.0);
    glTranslated(30.0, 50.0, 0.0);
    glBegin(GL_QUADS);
    for (int j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]); //assigning normal vector
        for (int i = 0; i < 4; ++i) {
            glVertex3dv(vertex[face[j][i]]);
        }
    }
    glEnd();
    //shadow OFF-------------------------------------------------
    glDisable(GL_LIGHTING);
    //-----------------------------------------------------------
    
    renderGround();
    
    glutSwapBuffers(); //update use glFlush() when using GLUE_SINGLE mode
}



void renderGround(){
    
    double ground_max_x = 300.0;
    double ground_max_y = 300.0;
    glColor3d(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    for(double ly = -ground_max_y ;ly <= ground_max_y; ly+=20.0){
        glVertex3d(-ground_max_x, ly,0);
        glVertex3d(ground_max_x, ly,0);
    }
    for(double lx = -ground_max_x ;lx <= ground_max_x; lx+=20.0){
        glVertex3d(lx, ground_max_y,0);
        glVertex3d(lx, -ground_max_y,0);
    }
    glEnd();
}

*/
//---------------------------------------------------------------------------------------------
//GLFW 2D
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

//Struct
typedef struct cell{
    int x;  //coordinates
    int y;

    int value; //1 or 0 represent obstacles
}Cell;

//Prototype
void drawGrid(void);
void drawObstacle(Cell**); //take in the gameMap array to check whether value = 1, if so, draw cube

Cell** initCell(void);
void generateRandomObstacle(void);

//const Variables
const int gridSize = 32;

const int SCREEN_WIDTH = gridSize*10 + 100;
const int SCREEN_HEIGHT = gridSize*10 + 100;

//Function Definition
static void inputK(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}

static void error_callback(int error, const char* description){
    fputs(description, stderr);
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
    Cell** gameMap = malloc(sizeof(Cell*)*10);
    int x = 50;
    int y = 50;
    for(int i = 0; i<10;i++){
        *(gameMap+i) = calloc(10, sizeof(Cell));
        for(int k = 0; k<10;k++){
            gameMap[i][k].value = 1;
            gameMap[i][k].x = 50;
            gameMap[i][k].y = 50;
            x+=gridSize;
            y+=gridSize;
        }
    }
    return gameMap;
}

void drawObstacle(Cell** gameMap){
    //draw obstacle
    glColor3d(0.0, 1.0, 1.0);
    for(int i = 0 ; i<10; i++){
        for(int k = 0; k<10; k++){
            if(gameMap[i][k].value != 0){
                glBegin(GL_POLYGON);
                glVertex2d(gameMap[i][k].x, gameMap[i][k].y);
                glVertex2d(gameMap[i][k].x+50, gameMap[i][k].y);
                glVertex2d(gameMap[i][k].x, gameMap[i][k].y+50);
                glVertex2d(gameMap[i][k].x+50, gameMap[i][k].y+50);
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
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
