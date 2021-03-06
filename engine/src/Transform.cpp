﻿#include "Transform.h"
#include "Group.h"
#include "Scene.h"
void ScaleStatic::apply() {
	glScalef(x, y, z);
}

void RotateStatic::apply() {
	glRotatef(angle, x, y, z);
}

// time -> the number of seconds to perform a full 360 degrees rotation around the specified axis
void RotateAnim::apply() {
	float mstime = time * 1000;
	float angle = fmod(glutGet(GLUT_ELAPSED_TIME), mstime) / mstime * 360;
	glRotatef(angle, x, y, z);
	glutPostRedisplay();
}

void TranslateStatic::apply() {
	glTranslatef(x, y, z);
}

/*
A set of points will be provided to define a Catmull-Rom cubic curve, as well as the number of seconds to run the whole curve.
Due to Catmull-Rom�s curve definition it is always required an initial point before the initial
curve segment and another point after the last segment. The minimum number of points is 4.
*/
void TranslateAnim::apply() {

	float pos[4] = { 0 };
	float der[4] = { 0 };
	float gt = glutGet(GLUT_ELAPSED_TIME) / (1000.0 * time);

	getGlobalCatmullRomCurvePoint(points, gt, pos, der);
	glTranslatef(pos[0], pos[1], pos[2]);
	normalize(der);
	normalize(y);
	float z[3];
	cross(der, y, z);
	normalize(z);
	float m[16];
	buildRotMatrix(der, y, z, m);
	glMultMatrixf(m);
	cross(z, der, y);

	glutPostRedisplay();
}
