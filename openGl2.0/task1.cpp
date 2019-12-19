#include "SOIL2\SOIL2\SOIL2.h"
#include "GL/glew.h"
#include "GL/freeglut.h"

#include <iostream>

static int w = 0, h = 0;

GLuint floor_texture_id;
GLuint car_texture_id;
GLuint knuckles_texture_id;
GLuint uganda_texture_id;

GLfloat dist_x = 0, dist_y = 0;
GLfloat angle = 180;

GLfloat machine_coord_x = 0, machine_coord_y = 0;
GLfloat machine_angle = 0;

GLfloat cam_dist = 20;
GLfloat ang_hor = 0, ang_vert = -60;

GLfloat no_light[] = { 0, 0, 0, 1 };
GLfloat light[] = { 1, 1, 1, 0 };

double cam_x = 0;
double cam_y = 0;
double cam_z = 0;

float amb[] = { 0.8, 0.8, 0.8 };
float dif[] = { 0.2, 0.2, 0.2 };

const double step = 1;

void init() {
	glClearColor(0, 0, 0, 1);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	const GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	floor_texture_id = SOIL_load_OGL_texture("брусчатка_55.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	car_texture_id = SOIL_load_OGL_texture("1.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT7, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, light_diffuse);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void drawFloor() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glBindTexture(GL_TEXTURE_2D, floor_texture_id);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glNormal3f(0, 0, 1); glVertex3f(-10, -10, 0);
	glTexCoord2f(0, 1); glNormal3f(0, 0, 1); glVertex3f(-10, 10, 0);
	glTexCoord2f(1, 1); glNormal3f(0, 0, 1); glVertex3f(10, 10, 0);
	glTexCoord2f(1, 0); glNormal3f(0, 0, 1); glVertex3f(10, -10, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawLamps() {

	const GLfloat light_pos[] = { 0.f, 0.f, 4.6f, 1.f };
	glPushMatrix();
	glTranslatef(-7, -7, 0);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCylinder(0.5, 0.3, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 0.6);
	if (glIsEnabled(GL_LIGHT1))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7, 7, 0);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCylinder(0.5, 0.3, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 0.6);
	if (glIsEnabled(GL_LIGHT2))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7, 7, 0);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCylinder(0.5, 0.3, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 0.6);
	if (glIsEnabled(GL_LIGHT5))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glLightfv(GL_LIGHT5, GL_POSITION, light_pos);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7, -7, 0);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCylinder(0.5, 0.3, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 0.6);
	if (glIsEnabled(GL_LIGHT6))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glLightfv(GL_LIGHT6, GL_POSITION, light_pos);
	glPopMatrix();

}

void drawCar()
{
	glPushMatrix();
	const GLfloat light_pos[] = { 1.f, 0.f, 0.f };
	GLfloat dir[] = { 1, 0, 0, 1 };
	GLfloat pos[] = { 0,0,0 };
	glTranslated(dist_x, dist_y, 1);
	glRotated(angle, 0, 0, 1);

	//Кузов
	glPushMatrix();
	glScaled(2, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glBindTexture(GL_TEXTURE_2D, car_texture_id);
	glutSolidCube(1);

	glPopMatrix();

	//Кабина
	glPushMatrix();
	glTranslated(1.3, 0, -0.1);
	glutSolidCube(0.8);

	glDisable(GL_TEXTURE_2D);

	//Фары
	glColor3f(0.7, 0.7, 0.2);
	glPushMatrix();
	if (glIsEnabled(GL_LIGHT3))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glTranslated(0.4, 0.3, 0);
	glutSolidSphere(0.1, 20, 20);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glLightfv(GL_LIGHT3, GL_POSITION, pos);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 60);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir);
	glTranslated(0, -0.6, 0);
	if (glIsEnabled(GL_LIGHT4))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glutSolidSphere(0.1, 20, 20);
	glLightfv(GL_LIGHT4, GL_POSITION, pos);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 60);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glPopMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(-1.7, -0.5, -0.6);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.2, 20, 20);
	glTranslated(0, 0, -1);
	glutSolidTorus(0.15, 0.2, 20, 20);
	glPopMatrix();
	glTranslated(0, -0.5, -0.5);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.2, 20, 20);
	glTranslated(0, 0, -1);
	glutSolidTorus(0.15, 0.2, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
}

void update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	double ang_vert_r = ang_vert / 180 * 3.1416;
	double ang_hor_r = ang_hor / 180 * 3.1416;
	cam_x = cam_dist * std::sin(ang_vert_r) * std::cos(ang_hor_r);
	cam_y = cam_dist * std::sin(ang_vert_r) * std::sin(ang_hor_r);
	cam_z = cam_dist * std::cos(ang_vert_r);

	gluLookAt(cam_x, cam_y, cam_z, 0., 0., 0., 0., 0., 1.);
	drawLamps();
	drawFloor();
	drawCar();
	glFlush();
	glutSwapBuffers();
}

void updateCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, (float)w / h, 1.0f, 1000.f);
	glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		if (glIsEnabled(GL_LIGHT1))
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);
		break;
	case '2':
		if (glIsEnabled(GL_LIGHT2))
			glDisable(GL_LIGHT2);
		else
			glEnable(GL_LIGHT2);
		break;
	case '5':
		if (glIsEnabled(GL_LIGHT3 ))
		{
			glDisable(GL_LIGHT3);
			glDisable(GL_LIGHT4);
		}
		else
		{
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
		}	
		break;
	case '3':
		if (glIsEnabled(GL_LIGHT5)) {
			glDisable(GL_LIGHT5);
		}
		else {
			glEnable(GL_LIGHT5);
		}
		break;
	case '4':
		if (glIsEnabled(GL_LIGHT6)) {
			glDisable(GL_LIGHT6);
		}
		else {
			glEnable(GL_LIGHT6);
		}
		break;
	case '6':
		if (glIsEnabled(GL_LIGHT0)) {
			glDisable(GL_LIGHT0);
		}
		else {
			glEnable(GL_LIGHT0);
		}
		break;
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	w = width;
	h = height;

	glViewport(0, 0, w, h);
	updateCamera();
}

void SpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		dist_x += std::cos(angle / 180 * 3.1416) * 0.3;
		dist_y += std::sin(angle / 180 * 3.1416) * 0.3;
		break;
	case GLUT_KEY_DOWN:
		dist_x -= std::cos(angle / 180 * 3.1416) * 0.3;
		dist_y -= std::sin(angle / 180 * 3.1416) * 0.3;
		break;
	case GLUT_KEY_LEFT:angle -= 5;break;
	case GLUT_KEY_RIGHT:angle += 5;break;
	case GLUT_KEY_SHIFT_L: ang_vert -= 5;; break;
	case GLUT_KEY_SHIFT_R: ang_vert += 5; break;
	case GLUT_KEY_CTRL_L: ang_hor -= 5; break;
	case GLUT_KEY_CTRL_R: ang_hor += 5; break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Car");

	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(update);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);

	glutMainLoop();

	return 0;
}
