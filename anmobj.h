#if !defined(AFX_ANMOBJ_H__46249C44_7C55_4407_AAE7_790A324FB6DE__INCLUDED_)
#define AFX_ANMOBJ_H__46249C44_7C55_4407_AAE7_790A324FB6DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct animation	//模型的动作序列结构
{
	char name[16];	//16个动作
	int start;		//动作起点
	int end;		//动作终点
};
struct MAN
{
	float qd[3];	//起点位置
	float zd[3];	//终点位置
	int dz;			//动作
	bool death;
};

class anmobj
{
public:
	anmobj();
	virtual ~anmobj();
public:
	bool manmove(int i);		//对象的移动
	int re[RNSHU];				//模型的面向角度
	md2_model_t* model[2];		//定义模型数组
	Texture* texture[2];		//定义贴图指针
	animation* anim[2];			//定义动作序列数组
	int size[2];				//动作数
	float frame[RNSHU];			//动作序列号
	MAN man[RNSHU];				//模型对象
	int counter[RNSHU];			//计数器
	void getobj(CString na);	//调入模型
	animation* animations(md2_model_t* model,int p);//调入动作序列
	void setman(int i,float y);	//显示模型
	void drawModel(int i,float x,float y,float z,int iFrame,int iAngel);//新的显示模型函数
};

#endif // !defined(AFX_ANMOBJ_H__46249C44_7C55_4407_AAE7_790A324FB6DE__INCLUDED_)