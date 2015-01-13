#pragma once

#ifndef _CUBETRANSFORM_H_INCLUDED_
#define _CUBETRANSFORM_H_INCLUDED_

void startRotating();
void stopRotating(); 
int getRotating();

void setRotated(int rot);
int getRotated();

void cTransformN(int n);
void cTransform(char *id);

struct elem
{
	int side;
	int place;
};

struct cubeTransformStep
{
	int target_side;
	int target_place;
	int source_side;
	int source_place;
};


#endif