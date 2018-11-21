#include "imageloader.h"
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include<cstring>

float angle = 0.0f;
float lx=0.0f,lz=-1.0f;
float lxx=1.0f,lzz=0.0f;
float x=0.0f, z=110.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
float deltaMoveX = 0;
int xOrigin = -1;
int h,w;
int day=1;
int view=1;
float xPriv,zPriv;

GLUquadricObj *quadratic = NULL;

GLuint _textureId;
GLuint _textureId1;
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;

void changeSize(int ww, int hh) {

	h = hh;
	w = ww;
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);

	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();

	gluOrtho2D(0, w, h, 0);

	glMatrixMode(GL_MODELVIEW);
}

void computePosZ(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computePosX(float deltaMoveX) {

    x += deltaMoveX * lxx * 0.1f;
	z += deltaMoveX * lzz * 0.1f;
}
void renderScene(void) {

    if(day==1){
        glClearColor(0.40f, 0.40f, 1.0f,0.0);
    }else{
        glClearColor(0.0f, 0.0f, 0.0f,0.0);
    }

    if (deltaMove)
		computePosZ(deltaMove);

    if (deltaMoveX)
		computePosX(deltaMoveX);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    if(view == 0)
        gluLookAt(	-30, 80.0f, -80,-30+lx, -10.0f, -80+lz, 0.0f, 1.0f,  0.0f);

	if((x>-190 && x<90) && (z>-50 && z<111)){
        gluLookAt(	x, 1.0f, z,x+lx, 1.0f,  z+lz,0.0f, 1.0f,  0.0f);
        xPriv = x;
        zPriv = z;
    }else{
        gluLookAt(	xPriv, 1.0f, zPriv,xPriv+lx, 1.0f,  zPriv+lz,0.0f, 1.0f,  0.0f);
    }

// ground
glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0f);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.50f, 0.50f, 0.50f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
		glVertex3f(-200.0f, 0.0f, -60.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-200.0f, 0.0f,  60.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 100.0f, 0.0f,  60.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 100.0f, 0.0f, -60.0f);
	glEnd();
glPopMatrix();
//end ground

//field
glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0f);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
        glNormal3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0, 0.0);
		glVertex3f(-200.0f, 0.0f, 100.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(100.0f, 0.0f,  100.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(100.0f, 0.0f,  60.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-200.0f, 0.0f, 60.0f);
	glEnd();
glPopMatrix();
//end field

//road
glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0f);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.50f, 0.50f, 0.50f);
	glBegin(GL_QUADS);
        glNormal3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0, 0.0);
		glVertex3f(-200.0f, 0.0f, 120.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(100.0f, 0.0f,  120.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(100.0f, 0.0f,  100.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-200.0f, 0.0f, 100.0f);
	glEnd();
glPopMatrix();
//end road

//fountain
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(-30.0f ,-0.3f, 10.0f);
        glScalef(15.0,1.0,12.0);
        glutSolidCube(1.2);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslatef(-30.0f ,0.0f, 10.0f);
        glScalef(15.0,1.0,12.0);
        glutSolidCube(1);
    glPopMatrix();
//end fountain

//Main Building
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, GL_TRUE);
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    glPushMatrix();
        glTranslatef(0.0f ,10.0f, 10.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId3);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glColor3f(1.0f, 1.0f, 1.0f);
        glRotatef(90.0,1.0,0.0,0.0);
        gluSphere(quadratic, 15.75, 20, 20);

    glPopMatrix();
//end Main Building

//annex1
    glPushMatrix();
        glTranslatef(-60.0f ,5.0f, 40.0f);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glScalef(8.0,1.0,1.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();


    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-60.0f ,10.0f, 40.0f);
        glScalef(81.0,2.0,8.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-10.0f ,12.0f, 40.0f);
        glScalef(20.0,3.0,8.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(40.0f ,10.0f, 40.0f);
        glScalef(81.0,2.0,8.0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(40.0f ,5.0f, 40.0f);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glScalef(8.0,1.0,1.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
//end annex1
//annex 2

    glPushMatrix();
        glTranslatef(-100.0f ,5.0f, 30.0f);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glScalef(8.0,3.0,1.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
//end annex2
//between 2&3

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glTranslatef(-61.0f ,5.0f, 20.0f);
        glScalef(0.60,1.0,1.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();


    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glTranslatef(-61.0f ,5.0f, 0.0f);
        glScalef(0.60,1.0,1.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glTranslatef(-60.0f ,15.0f, 10.0f);
        glScalef(1.0,1.0,3.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
//end between 2&3
//annex 3
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glTranslatef(-100.0f ,5.0f, -10.0f);
        glScalef(8.0,3.0,1.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
//end annex 3
//annex 7
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glTranslatef(-145.0f ,5.0f, 10.0f);
        glScalef(1.0,8.0,5.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
//end annex 7

//annex 4
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glTranslatef(-55.0f ,5.0f, -40.0f);
        glScalef(2.0,3.0,5.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
//end annex 4

//annex 5
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glTranslatef(-30.0f ,5.0f, -40.0f);
        glScalef(2.0,3.0,5.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
//end annex 5

//annex 6
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glColor3f(0.94f, 0.26f, 0.07f);
        glTranslatef(0.0f ,5.0f, -40.0f);
        glScalef(2.0,5.0,5.0);
        glutSolidCube(10);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
//end annex 6

	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();

	restorePerspectiveProjection();

	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int xx, int yy) {

	switch (key) {
		case 27:exit(0);break;
        case 100:day=1;break;
		case 110:day=0;break;
		case 102:view=1;break;
		case 117:view=0;break;
	}
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
		case GLUT_KEY_LEFT : deltaMoveX -= 0.5; break;
		case GLUT_KEY_RIGHT : deltaMoveX += 0.5; break;

	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0;break;
		case GLUT_KEY_DOWN : deltaMove = 0;break;
		case GLUT_KEY_LEFT : deltaMoveX = 0;break;
		case GLUT_KEY_RIGHT : deltaMoveX = 0;break;
	}
}

void mouseMove(int x, int y) {
	if (xOrigin >= 0) {
		deltaAngle = (x - xOrigin) * 0.001f;
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {

		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {
			xOrigin = x;
		}
	}
	if(button == GLUT_MIDDLE_BUTTON){
        if (state == GLUT_UP) {
			deltaMove = 0.5f;
		}
		else if(state == GLUT_DOWN){
			deltaMove = -0.5f;
		}
	}
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void initialize() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 1.00, 1.0, 200.0);
	Image* image = loadBMP("C:\\Users\\Iftekhar\\Desktop\\texture mapping code\\double_texture\\grass.bmp");
	Image* image1 = loadBMP("C:\\Users\\Iftekhar\\Desktop\\texture mapping code\\double_texture\\floor.bmp");
	Image* image2 = loadBMP("C:\\Users\\Iftekhar\\Desktop\\texture mapping code\\double_texture\\room.bmp");
	Image* image3 = loadBMP("C:\\Users\\Iftekhar\\Desktop\\texture mapping code\\double_texture\\main.bmp");
	Image* image4 = loadBMP("C:\\Users\\Iftekhar\\Desktop\\texture mapping code\\double_texture\\road.bmp");
	_textureId = loadTexture(image);
	_textureId1 = loadTexture(image1);
	_textureId2 = loadTexture(image2);
	_textureId3 = loadTexture(image3);
	_textureId4 = loadTexture(image4);
	delete image;
}

void lightSetting(){

	GLfloat ambientIntensity[4] = {0.6, 0.6, 0.6, 1.0};

	GLfloat position[4] = {0.0, 1.0, 0.0, 0.0};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientIntensity);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
}
int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("AIUB 3D");
    glClearColor(0.40f, 0.40f, 1.0f,0.0);
    initialize();
    lightSetting();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glutMainLoop();

	return 1;
}

