//
//  path.h
//  OpenGLRobot
//
//  Created by Tsz Ting Yu on 5/9/18.
//  Copyright © 2018 Tsz Ting Yu. All rights reserved.
//

#ifndef path_h
#define path_h

typedef struct node{
    int value;
    struct node* next;
}Node;

void push();
void pop();

#endif /* path_h */
