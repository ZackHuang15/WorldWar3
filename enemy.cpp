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
	//���Խ�ջ
	glPushAttrib(GL_CURRENT_BIT);
	glDisable(GL_TEXTURE_2D);    
	glDisable(GL_LIGHTING);      	
	//��ɫ��
	//�����ƶ�
	glTranslatef(-0.1f, 0.15, -1.0);

	glColor3f (0.0, 0.0, 0.0);
	//��դλ������ƶ�-0.01����ԭλ�õ���2������
	glRasterPos3f (0.0, 0.0,-0.01);
	for(i=0;i<iAttackMaxLife/10;i++)
	{
		glBitmap (8, 12, 0.0, 0.0, 8.0, 0.0, rasterallf);
	}
	//��ɫ��ʾ����
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