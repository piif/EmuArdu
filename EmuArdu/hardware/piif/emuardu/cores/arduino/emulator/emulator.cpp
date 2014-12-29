#define MUST_DEFINE_HARDWARE
#include "Arduino.h"
#include "emulator.h"
#include "description.h"
#include "inout.h"
#include "timer.h"

// Menus: http://www.lighthouse3d.com/tutorials/glut-tutorial/popup-menus/
// Text : http://www.lighthouse3d.com/tutorials/glut-tutorial/bitmap-fonts/
// Images ??? => https://www.opengl.org/wiki/Related_toolkits_and_APIs


// printf,perror
#include <stdio.h>
// getopt
#include <unistd.h>
// graphics functions
#include <GL/freeglut.h>
// texture
#include <GL/gl.h>
// arduino image loading
#include <gd.h>

void emulatorRender(void);

void emulatorLoop(void) {
	// TODO handle kbd input to buffer into Serial queue
	emulatorRender();
	glutMainLoopEvent();
}

bool hasToRender = true;
GLuint arduinoTexture;

void emulatorRender(void) {
	if (!hasToRender) {
		return;
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 1.42, 0, 0, 0, 0, 1, 0);
	glScaled(1.0 / hardware.pictureWidth, -1.0 / hardware.pictureHeight, 1.0 / hardware.pictureWidth);
	glTranslated(-hardware.pictureWidth / 2.0, -hardware.pictureHeight / 2.0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, arduinoTexture);
	glBegin(GL_QUADS);
		glTexCoord2i(0,0);glVertex3i(0, 0, 0);
		glTexCoord2i(1,0);glVertex3i(hardware.pictureWidth, 0, 0);
		glTexCoord2i(1,1);glVertex3i(hardware.pictureWidth, hardware.pictureHeight, 0);
		glTexCoord2i(0,1);glVertex3i(0, hardware.pictureHeight, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);

	PinState *state = pinsState;
	PinDescriptor *desc = hardware.pins;
	double level;
	for (int i = 0; i < pinsNumber; i++) {
		if (state->mode & IO_MODE_PWM) {
			level = state->value / 256.0;
		} else if (state->mode & IO_MODE_ANALOG_IN) {
			level = state->value / 1000.0;
		} else {
			level = (state->value == 0) ? 0.0 : 1.0;
		}
		glColor3d(1, 1, 1);
		glVertex3i(desc->x, desc->y, 1);
		glVertex3i(desc->x + desc->w, desc->y, 1);
		glVertex3i(desc->x + desc->w, desc->y + desc->h, 1);
		glVertex3i(desc->x, desc->y + desc->h, 1);
		glColor3d(0, level, 0);
		glVertex3i(desc->x + 1, desc->y + 1, 2);
		glVertex3i(desc->x + desc->w - 2, desc->y + 1, 2);
		glVertex3i(desc->x + desc->w - 2, desc->y + desc->h - 2, 2);
		glVertex3i(desc->x + 1, desc->y + desc->h - 2, 2);
		state++;
		desc++;
	}
	glEnd();

	glutSwapBuffers();
	glutPostRedisplay();

	hasToRender = false;
}

void emulatorChangeSize(int w, int h) {
	hasToRender = true;
	// http://www.lighthouse3d.com/tutorials/glut-tutorial/preparing-the-window-for-a-reshape/
	if(h == 0)
		h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, 1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
}

void mouseClick(int button, int event, int x, int y) {
	// TODO
	// http://www.lighthouse3d.com/tutorials/glut-tutorial/the-mouse/
	// GLUT_LEFT_BUTTON
	// GLUT_MIDDLE_BUTTON
	// GLUT_RIGHT_BUTTON
	//
	// GLUT_DOWN
	// GLUT_UP

	// find if coords are in one of the pins
	printf("mouse %c %s %d %d\n", "LMR"[button], event ? "release" : "press", x, y);
}

void mouseDrag(int x, int y) {
	// handle "analog in" with this
	printf("drag %d %d\n", x, y);
}

GLubyte *imgPixels;

// options
byte verbose = 0;
char *platformPath = 0;
char *platformName = 0;

void emulatorInit(int argc, char **argv) {
	for(int i = 0; i < argc; i++) {
		printf(" - %s\n", argv[i]);
	}
	int c;
	while ((c = getopt (argc, argv, "qvp:c:")) != -1) {
		switch(c) {
		case 'q':
			verbose = 0;
			break;
		case 'v':
			verbose++;
			break;
		case 'p':
			platformPath = optarg;
			break;
		case 'c':
			platformName = optarg;
			break;
		}
	}
	if (platformPath == 0) {
		fprintf(stderr, "Command line must specify -p platform_path\n");
		exit(1);
	}

	// initialize hardware simulation (pin mode&state)
	inoutInit();
	timerInit();

	// initialize graphic components
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(hardware.pictureWidth, hardware.pictureHeight);
	glutCreateWindow("EmuArdu");

	glClearColor(.5, .5, .5, 0); 	//Change la couleur du fond
	glEnable(GL_DEPTH_TEST); 	//Active le depth test
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D); 	//Active le texturing
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

	char picturePath[100];
	sprintf(picturePath, "%s/emuardu/variants/%s", platformPath, hardware.picturePath);
	FILE *imgFile = fopen(picturePath, "r");
	if (!imgFile) {
		perror("can't open arduino image");
		exit(1);
	}

	// TODO : Look at extension to call jpeg or png function
	gdImagePtr img = gdImageCreateFromJpeg(imgFile);
	fclose(imgFile);

	if (hardware.pictureWidth != img->sx || hardware.pictureHeight != img->sy) {
		fprintf(stderr, "Image size doesn't match %d/%d %d/%d\n",
				hardware.pictureWidth, img->sx, hardware.pictureHeight, img->sy);
		exit(1);
	}

	imgPixels = new GLubyte[hardware.pictureWidth * hardware.pictureHeight * 3];
	GLubyte *pixelPtr = imgPixels;
	for (int y = 0; y < hardware.pictureHeight; y++) {
		for (int x = 0; x < hardware.pictureWidth; x++) {
			int c = gdImageGetPixel(img, x, y);
			if (img->trueColor) {
				*pixelPtr++ = c >> 16;
				*pixelPtr++ = c >> 8;
				*pixelPtr++ = c;
			} else {
				*pixelPtr++ = img->red[c];
				*pixelPtr++ = img->green[c];
				*pixelPtr++ = img->blue[c];
			}
		}
	}

	glGenTextures(1, &arduinoTexture);

	glBindTexture(GL_TEXTURE_2D, arduinoTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, hardware.pictureWidth, hardware.pictureHeight,
			0, GL_RGB, GL_UNSIGNED_BYTE, imgPixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	gdImageDestroy(img);
	glutDisplayFunc(emulatorRender);
	glutReshapeFunc(emulatorChangeSize);

	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseDrag);
}
