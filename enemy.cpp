#include "stdafx.h"
#include "people.h"
/*
enemy::enemy()
{

}

enemy::~enemy()
{

}

void enemy::init()
{

}

void enemy::showEnemyHp()
{
	int i;

	unsigned char rasterallf[12] = {
		0xff, 0xff,0xff, 0xff,0xff, 0xff,
		0xff, 0xff,0xff, 0xff,0xff, 0xff
	};

	glLoadIdentity();
	//属性进栈
	glPushAttrib(GL_CURRENT_BIT);
	glDisable(GL_TEXTURE_2D);    
	glDisable(GL_LIGHTING);      	
	//颜色条
	//坐标移动
	glTranslatef(-0.1f, 0.15, -1.0);

	glColor3f (0.0, 0.0, 0.0);
	//光栅位置向后移动-0.01，比原位置低了2个像素
	glRasterPos3f (0.0, 0.0,-0.01);
	for(i=0;i<iAttackMaxLife/10;i++)
	{
		glBitmap (8, 12, 0.0, 0.0, 8.0, 0.0, rasterallf);
	}
	//绿色显示生命
	glColor3f (0.0, 1.0, 0.0);
	glRasterPos3f (0.0, 0.0,0.0);
	for(i=0;i<iAttackLife/10;i++)
	{
		glBitmap (8, 8, 0.0, 0.0, 8.0, 0.0, rasterallf);
	}

	/////////////////////////
	glEnable(GL_LIGHTING);         
	glEnable(GL_TEXTURE_2D);          
	glPopAttrib();

}
*/