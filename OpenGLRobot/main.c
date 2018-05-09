//
//  main.c
//  OpenGLRobot
//
//  Created by Tsz Ting Yu on 5/3/18.
//  Copyright © 2018 Tsz Ting Yu. All rights reserved.
//
// System Headers

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

typedef struct node{
    int value;
    struct node* next;
}Node;

enum Control{
    Up,
    Down,
    Left,
    Right
};

enum Mode{
    Manual,
    Auto
};


//Prototype
void drawGrid(void);
void drawObstacle(Cell**); //take in the gameMap array to check whether value = 1, if so, draw cube
void drawCar(Car*);


Cell** initCell(void);
void generateRandomObstacle(Cell**);
void updateCar(Car*, int);
void updateCarAuto();
int collisionCheck(Car*,int);

void delay(unsigned int);

//const Variables-ish
const int gridSize = 32;
const int gridNum = 10;
const int SCREEN_WIDTH = gridSize*gridNum + 100;
const int SCREEN_HEIGHT = gridSize*gridNum + 100;
Car* car = NULL;
Cell** gameMap = NULL;
int MODE = Manual;

//Function Definition
static void inputK(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_M && action == GLFW_PRESS){
        MODE = Manual;
        printf("\nManual Mode");
    }
    if(key == GLFW_KEY_A && action == GLFW_PRESS){
        MODE = Auto;
        printf("\nAutonomous Mode");
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS && MODE == Manual){
        updateCar(car,Left);
    }
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS && MODE == Manual){
        updateCar(car,Right);
    }
    if(key == GLFW_KEY_UP && action == GLFW_PRESS && MODE == Manual){
        updateCar(car,Up);
    }
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS && MODE == Manual){
        updateCar(car,Down);
    }
}

void delay(unsigned int sec){
    unsigned int retTime = time(0) + sec;   // Get finishing time.
    while (time(0) < retTime);
}

void updateCarAuto(){
    int num;
        num = (rand()%4);
        if(num == 0){
            if(collisionCheck(car, num)){
                car->y = (car->y) - gridSize;
            }
        }
        if(num == 1){
            if(collisionCheck(car, num)){
                car->y = (car->y) + gridSize;
            }
        }
        if(num == 2){
            if(collisionCheck(car, num)){
                car->x = (car->x) - gridSize;
            }
            
        }
        if(num == 3){
            if(collisionCheck(car, num)){
                car->x = (car->x) + gridSize;
            }
        }

}
static void error_callback(int error, const char* description){
    fputs(description, stderr);
}

int collisionCheck(Car* car,  int num){
    int row = ((car->y)-50)/gridSize;
    int col = ((car->x)-50)/gridSize;
    if(num == 0){
        if(row > 0){
            if(gameMap[row-1][col].value == 1){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    else if(num == 1){
        if(row < gridNum-1){
            if(gameMap[row+1][col].value == 1){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    else if(num == 2){
        if(col > 0){
            if(gameMap[row][col-1].value == 1){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }

    }
    else if(num == 3){
        if(col < gridNum-1){
            if(gameMap[row][col+1].value == 1){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    else{return 0;}
}

void updateCar(Car* car, int num){
    //see enum Control
    if(num == 0){
        if(collisionCheck(car, num)){
            car->y = (car->y) - gridSize;
        }
    }
    if(num == 1){
        if(collisionCheck(car, num)){
        car->y = (car->y) + gridSize;
        }
    }
    if(num == 2){
        if(collisionCheck(car, num)){
        car->x = (car->x) - gridSize;
        }

    }
    if(num == 3){
        if(collisionCheck(car, num)){
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

void generateRandomObstacle(Cell** gameMap){
    int x = 50;
    int y = 50;
    srand(time(0));
    for(int i = 0; i<gridNum;i++){
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
    gameMap[0][0].value = 0; //car initial position -> NO obstacle
}

Cell** initCell(){ //initialize a 10x10 cell
    Cell** gameMap = (Cell**)malloc(gridNum*sizeof(Cell*));
    for(int i = 0; i<gridNum;i++){
        *(gameMap+i) = (Cell*)calloc(gridNum, sizeof(Cell));
    }
    generateRandomObstacle(gameMap);
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
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Final Test", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, inputK);
    
    gameMap = initCell();
    //initial car and its position
    car = malloc(sizeof(Car));
    car->x = 50;
    car->y = 50;
    
    printf("\n\n"
           "\n***********************"
           "\n*    Instructions     *"
           "\n* Press M for Manual  *"
           "\n* Press A for Auto    *"
           "\n***********************");
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
        
        if(MODE == Auto){
            updateCarAuto();
            drawCar(car);
            delay(1);
        }
        else{
            drawCar(car);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
