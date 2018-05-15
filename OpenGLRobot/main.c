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
struct Cell{
    int x;  //coordinates
    int y;
    
    int value; //1 represent obstacles, 2 represent chest
    int score;
};
typedef struct Cell Cell;


struct Car{
    int x;
    int y;
    int direaction;
};

typedef struct Car Car;


struct Treasure{
    int x;
    int y;
    int value;
};


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

enum Object{
    Empty,
    Obstacle,
    Chest,
    OpenChest
};
//Prototype
void drawGrid(void);
void drawObject(Cell**); //take in the gameMap array to check whether value = 1, if so, draw cube
void drawCar(Car*);
void drawGameOver(void);  //Not working yet

Cell** initCell(void);
void generateRandomObstacle(Cell**);
void generateRandomTreasure(Cell**);
void updateCar(Car*, int);
void updateCarAuto();
int collisionCheck(Car*,int);
void treasureCheck();
void bombBlock(void);
void delay(unsigned int);

//const Variables-ish
const int gridSize = 32;
const int gridNum = 10;
const int SCREEN_WIDTH = gridSize*gridNum + 100;
const int SCREEN_HEIGHT = gridSize*gridNum + 100;
const int _numOfTreasure = 4;
const int gameOver[] = {0,0,1,1,1,1,1,1,0,0,
0,1,0,0,0,0,0,0,1,0,
1,1,1,1,0,0,1,1,1,1,
1,1,1,0,1,1,1,1,0,1,
1,1,1,1,0,0,1,1,1,1,
1,0,0,0,0,0,0,0,0,1,
1,0,0,1,0,0,1,0,0,1,
0,1,0,0,1,1,0,0,1,0,
0,0,1,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,0};



Car* car = NULL;
Cell** gameMap = NULL;
int MODE = Manual;
int openedChest = 0;
int score = 0;
int bomb = 5;    //number of bomb

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
        car->direaction = Left;
        updateCar(car,Left);
    }
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS && MODE == Manual){
        car->direaction = Right;
        updateCar(car,Right);
    }
    if(key == GLFW_KEY_UP && action == GLFW_PRESS && MODE == Manual){
        car->direaction = Up;
        updateCar(car,Up);
    }
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS && MODE == Manual){
        car->direaction = Down;
        updateCar(car,Down);
    }
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS && MODE == Manual){
        bombBlock();
    }
}

void bombBlock(){
    int row = ((car->y)-50)/gridSize;
    int col = ((car->x)-50)/gridSize;
    if(collisionCheck(car, (car->direaction))==0 && bomb != 0){
        if(car->direaction == Left){
            gameMap[row][col-1].value = Empty;
        }
        if(car->direaction == Right){
            gameMap[row][col+1].value = Empty;
        }
        if(car->direaction == Up){
            gameMap[row-1][col].value = Empty;
        }
        if(car->direaction == Down){
            gameMap[row+1][col].value = Empty;
        }
        bomb--;
        printf("\n  boom! You have %d more bomb(s) left.",bomb);
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

void treasureCheck(){
    int col = ((car->x)-50)/gridSize;
    int row = ((car->y)-50)/gridSize;
                                    
    if (gameMap[row][col].value == Chest){
        score += gameMap[row][col].score;
        printf("\nYou found a treasure! There's $ %dG in it.", gameMap[row][col].score);
        gameMap[row][col].value = OpenChest;
        gameMap[row][col].score = 0;
        openedChest++;
    }
}

int collisionCheck(Car* car,  int num){
    int row = ((car->y)-50)/gridSize;
    int col = ((car->x)-50)/gridSize;
    if(num == 0){
        if(row > 0){
            if(gameMap[row-1][col].value == Obstacle){
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
            if(gameMap[row+1][col].value == Obstacle){
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
            if(gameMap[row][col-1].value == Obstacle){
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
            if(gameMap[row][col+1].value == Obstacle){
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
            if(rand()%10 < 3){  //adjust probability
                
                gameMap[i][k].value = Obstacle;
            }
            else{
                
                gameMap[i][k].value = Empty;
            }
            gameMap[i][k].x = x;
            gameMap[i][k].y = y;
            gameMap[i][k].score = 0;
            x+=gridSize;
        }
        x=50;
        y+=gridSize;
    }
    gameMap[0][0].value = Empty; //car initial position -> NO obstacle
}


void generateRandomTreasure(Cell** gameMap){
    int row = 0;
    int col = 0 ;
    for(int i = 0; i<_numOfTreasure;i++){
        do{
            row = rand() % 10;
            col = rand() % 10;
        }while(gameMap[row][col].value != Empty || (row == 0 && col == 0));
        gameMap[row][col].value = Chest;
        gameMap[row][col].x = col*gridSize+50;
        gameMap[row][col].y = row*gridSize+50;
        gameMap[row][col].score = ((rand()%9)+1) * 10;
    }
}


Cell** initCell(){ //initialize a 10x10 cell
    Cell** gameMap = (Cell**)malloc(gridNum*sizeof(Cell*));
    for(int i = 0; i<gridNum;i++){
        *(gameMap+i) = (Cell*)calloc(gridNum, sizeof(Cell));
    }
    generateRandomObstacle(gameMap);
    generateRandomTreasure(gameMap);
    return gameMap;
}


void drawObject(Cell** gameMap){
    //draw obstacle
        for(int i = 0 ; i<gridNum; i++){
        for(int k = 0; k<gridNum; k++){
            if(gameMap[i][k].value == Obstacle){
                glColor3d(0.98, 0.94, 0.83);
                glBegin(GL_QUADS);
                glVertex2f(gameMap[i][k].x, gameMap[i][k].y);
                glVertex2f(gameMap[i][k].x+gridSize, gameMap[i][k].y);
                glVertex2f(gameMap[i][k].x+gridSize, gameMap[i][k].y+gridSize);
                glVertex2f(gameMap[i][k].x, gameMap[i][k].y+gridSize);
                glEnd();
                
                if(i<gridNum-1){
                //wall
                glColor3d(0.73, 0.66, 0.49);
                glBegin(GL_QUADS);
                glVertex2f(gameMap[i+1][k].x, gameMap[i+1][k].y);
                glVertex2f(gameMap[i+1][k].x+gridSize, gameMap[i+1][k].y);
                glVertex2f(gameMap[i+1][k].x+gridSize, gameMap[i+1][k].y+gridSize);
                glVertex2f(gameMap[i+1][k].x, gameMap[i+1][k].y+gridSize);
                glEnd();
                }
            }
            else if(gameMap[i][k].value == Chest){   //if change to openChest; initial treasure will be hidden
                glColor3d(0.2, 0.8, 0.3);
                glBegin(GL_QUADS);
                glVertex2f(gameMap[i][k].x, gameMap[i][k].y);
                glVertex2f(gameMap[i][k].x+gridSize, gameMap[i][k].y);
                glVertex2f(gameMap[i][k].x+gridSize, gameMap[i][k].y+gridSize);
                glVertex2f(gameMap[i][k].x, gameMap[i][k].y+gridSize);
                glEnd();
            }
        }
    }
}


void drawGameOver(){
    int index = 0;
    for(int k = 0; k<gridNum; k++){
        for(int i = 0; i<gridNum; i++){
            if(gameOver[index] == 1){
                glColor3d(0.54, 0.49, 0.42);
                glBegin(GL_QUADS);
                
                glVertex2f(i*gridSize+50, k*gridSize+50);
                glVertex2f(i*gridSize+gridSize+50, k*gridSize+50);
                glVertex2f(i*gridSize+gridSize+50, k*gridSize+gridSize+50);
                glVertex2f(i*gridSize+50, k*gridSize+gridSize+50);
                
                glEnd();
            }
            else{}
            index++;
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
    
    printf("\n\n"
           "\n***********************"
           "\n*    Instructions     *"
           "\n* Press M for Manual  *"
           "\n* Press A for Auto    *"
           "\n* Press Space to bomb *"
           "\n***********************");
    
    
    
    gameMap = initCell();
    //initial car and its position
    car = malloc(sizeof(Car));
    car->x = 50;
    car->y = 50;
    car->direaction = Down;
    glfwSetTime	(0);
    while (!glfwWindowShouldClose(window)){

        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        
        glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT,0, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        
        if(openedChest == _numOfTreasure){
            double elapsedTime = glfwGetTime();
            printf("\n\nCongratulation! You found all the treasure!"
                   "\nYou hunt for the treasure for %f second(s)"
                   "\nYou have $ %dG in your pocket.",elapsedTime,score);
            while(!glfwWindowShouldClose(window)){
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
                drawGameOver();
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }
        else{
            
        }
            drawGrid();
            drawObject(gameMap);
        
            treasureCheck(); //check current posisition
        
            if(MODE == Auto){
                updateCarAuto();
                drawCar(car);
                //delay(1);
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
