//
//  rotation.c
//  openGLProject
//
//  Created by 김혜지 on 2016. 5. 17..
//  Copyright © 2016년 김혜지. All rights reserved.
//

#include <stdio.h>
#include <GLUT/GLUT.h>
#define PI 3.1415926
float x, y, z;
float radius;
float theta;
float phi;

int beforeX, beforeY;

GLfloat vertices[][3] = {
    { -1.0, -1.0, 1.0 },
    { -1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0 },
    { 1.0, -1.0, 1.0 },
    { -1.0, -1.0, -1.0 },
    { -1.0, 1.0, -1.0 },
    { 1.0, 1.0, -1.0 },
    { 1.0, -1.0, -1.0 }};

GLfloat colors[][3] = {
    { 1.0, 0.0, 0.0 },  // red
    { 1.0, 1.0, 0.0 },  // yellow
    { 0.0, 1.0, 0.0 },  // green
    { 0.0, 0.0, 1.0 },  // blue
    { 1.0, 1.0, 1.0 },  // white
    { 1.0, 0.0, 1.0 }}; // magenta

void polygon(int a, int b, int c, int d)
{
    glColor3fv(colors[a]);
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}

// 6개의 면을 만든다.
void createCube(void)
{
    polygon(0, 3, 2, 1);    // front
    polygon(2, 3, 7, 6);    // right
    polygon(3, 0, 4, 7);    // bottom
    polygon(4, 5, 6, 7);    // back
    polygon(1, 2, 6, 5);    // top
    polygon(5, 4, 0, 1);    // right
}

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0) ;
    glColor3f(1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);    // 깊이 활성화
}

void reshape (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    //glOrtho (-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    gluPerspective(60.0, 1.0, 1.0, 100.0);  // 멀고 가까움을 표현.
    
    radius = 10.0;
    theta = 10.0;
    phi = -10.0;
}
void display (void)
{
    x = radius * cos(phi) * cos(theta);
    y = radius * cos(phi) * sin(theta);
    z = radius * sin(phi);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    // (앞의 세 인자는 카메라의 위치, 중간의 세 인자는 카메라의 초점,
    //  뒤의 세 인자는 법선벡터 방향 (0, 1, 0))으로 해줘야 세워져 보인다.
    
    glBegin(GL_LINES);  // X, Y, Z 선 표시
    glColor3f(1.0, 0.0, 0.0); // X축
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    
    glColor3f(0.0, 1.0, 0.0); // Y축
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    
    glColor3f(0.0, 0.0, 1.0); // Z축
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    
    createCube();// 큐브 생성
    
    glFlush ();
    glutSwapBuffers();
}

void specialKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            theta -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            theta += 0.1;
            break;
        case GLUT_KEY_UP:
            phi += 0.1;
            break;
        case GLUT_KEY_DOWN:
            phi -= 0.1;
            break;
    }
    
    glutPostRedisplay();
    
    if ( theta > 2.0 * PI ) // 360도 넘어가면
        theta -= (2.0 * PI);
    else if ( theta < 0.0 )
        theta += (2.0 * PI);
}

void processMouse(int button, int state, int x, int y)
{
    
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            beforeX = x;
            beforeY = y;
            printf("down- x:%d , y:%d\n ",x,y);
        }
        else{
            printf("up- x:%d , y:%d\n ",x,y);
        }
    }
}

void processMouseMotion(int x, int y)
{
    printf("process- x:%d , y:%d\n ",x,y);
    
    if(abs(beforeX-x) > abs(beforeY-y)){
        if(beforeX < x)
        {
            theta -= 0.1;
        }else if(beforeX > x){
            theta += 0.1;
        }
    }else {
        if(beforeY < y){
            phi -= 0.1;
        }else if(beforeY > y){
            phi -= 0.1;
        }
    }
    
    beforeX = x;
    beforeY = y;
    
    glutPostRedisplay();
    
    if ( theta > 2.0 * PI ) // 360도 넘어가면
        theta -= (2.0 * PI);
    else if ( theta < 0.0 )
        theta += (2.0 * PI);
}

void main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (500, 500);
    glutCreateWindow ("Cube");
    init();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
    //glutSpecialFunc(specialKey);
    glutIdleFunc(display);
    glutMainLoop();
}