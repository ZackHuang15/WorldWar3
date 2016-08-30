#include "stdafx.h"
#include "mdlobj.h"
#include "anmobj.h"
#include "baiscobj.h"

TMDLModel MdlModel[2];

//////////////////////////////////////////////////////////////////////////
mdlobj::mdlobj()
{
	Animation=0;			//动作步数
}
mdlobj::~mdlobj()
{
}
/////////////////////////////////////////////////////////////////////
//初始化
int mdlobj::InitGL(int a,char* na)		//调入模型接口
{	
	MdlModel[a].Init(na);				//调入第a个名为na的MDL模型
	MdlModel[a].SetSequence(0);			//将初始动作设为第0个动作

	return TRUE;							// Initialization Went OK
}

//绘制模型
void mdlobj::DrawModels(float x,float y,float z,int a,float size,float rz,float ry)
{
	glPushMatrix();

	glEnable(GL_LIGHTING);				//使用光照
	glEnable(GL_TEXTURE_2D);			//使用贴图
	//移动到指定坐标
	glTranslatef(x, y, z);
	glScalef( size, size,size);	//缩放
	//绕X轴旋转-90度
	glRotated(-90,1.0f,0.0f,0.0f);
	//绕Y轴旋转，随俯仰角变化
	glRotated(rz+5,0.0f,0.0f,1.0f);
	//绕Z轴旋转，随方位角变化
	glRotated(-ry*2/3-5,0.0f,1.0f,0.0f);
	static float Previous;				//上一动作时间，静态变量
	float Current = GetTickCount()/1000.f;//取目前时钟计数器的值
	MdlModel[a].DrawModel();			//调用MDL类的显示
	Previous = Current;					//保存时间
	if(Animation<1)						//如果拉枪栓动作完成
		MdlModel[a].SetSequence(0);		//动作序列设为0
	if(Animation>0)
		Animation--;					//动作计数
	glPopMatrix();
}

void mdlobj::fire(int a)
{
	MdlModel[0].SetSequence(a);
	tagMDLSeqDescription *aa=(tagMDLSeqDescription *)((BYTE *)MdlModel[0].Header
							  + MdlModel[0].Header->SequenceOffset)+a;

	//开火动作序列 Animation : 5 , NumFrames:29
	Animation=aa->NumFrames/5;
}
