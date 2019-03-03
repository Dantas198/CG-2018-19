#ifndef MODEL3D_H
#define MODEL3D_H

#include <iostream>
#include <fstream>
#include <string>

struct Point3D
{
	float x;
	float y;
	float z;
};

class Model3D {
private:
	Point3D *points;

public:
	Model3D();
	Model3D(std::string filename);
	~Model3D();
};

#endif MODEL3D_H