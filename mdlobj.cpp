#include "stdafx.h"
#include "mdlobj.h"
#include "anmobj.h"
#include "baiscobj.h"

TMDLModel MdlModel[2];

//////////////////////////////////////////////////////////////////////////
mdlobj::mdlobj()
{
	Animation=0;			//��������
}
mdlobj::~mdlobj()
{
}
/////////////////////////////////////////////////////////////////////
//��ʼ��
int mdlobj::InitGL(int a,char* na)		//����ģ�ͽӿ�
{	
	MdlModel[a].Init(na);				//�����a����Ϊna��MDLģ��
	MdlModel[a].SetSequence(0);			//����ʼ������Ϊ��0������

	return TRUE;							// Initialization Went OK
}

//����ģ��
void mdlobj::DrawModels(float x,float y,float z,int a,float size,float rz,float ry)
{
	glPushMatrix();

	glEnable(GL_LIGHTING);				//ʹ�ù���
	glEnable(GL_TEXTURE_2D);			//ʹ����ͼ
	//�ƶ���ָ������
	glTranslatef(x, y, z);
	glScalef( size, size,size);	//����
	//��X����ת-90��
	glRotated(-90,1.0f,0.0f,0.0f);
	//��Y����ת���温���Ǳ仯
	glRotated(rz+5,0.0f,0.0f,1.0f);
	//��Z����ת���淽λ�Ǳ仯
	glRotated(-ry*2/3-5,0.0f,1.0f,0.0f);
	static float Previous;				//��һ����ʱ�䣬��̬����
	float Current = GetTickCount()/1000.f;//ȡĿǰʱ�Ӽ�������ֵ
	MdlModel[a].DrawModel();			//����MDL�����ʾ
	Previous = Current;					//����ʱ��
	if(Animation<1)						//�����ǹ˨�������
		MdlModel[a].SetSequence(0);		//����������Ϊ0
	if(Animation>0)
		Animation--;					//��������
	glPopMatrix();
}

void mdlobj::fire(int a)
{
	MdlModel[0].SetSequence(a);
	tagMDLSeqDescription *aa=(tagMDLSeqDescription *)((BYTE *)MdlModel[0].Header
							  + MdlModel[0].Header->SequenceOffset)+a;

	//���������� Animation : 5 , NumFrames:29
	Animation=aa->NumFrames/5;
}
