#if !defined(AFX_MDLOBJ_H__D8D0E709_8777_4103_B7C3_7C9513E6E4A2__INCLUDED_)
#define AFX_MDLOBJ_H__D8D0E709_8777_4103_B7C3_7C9513E6E4A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class mdlobj
{
public:
	mdlobj();
	virtual ~mdlobj();
	unsigned int Animation;			//动作变换标志

	int		InitGL(int a,char* na);	//调入模型
	void	DrawModels(float x,float y,float z,int a,float size,float rz,float ry);
									//显示模型
	void	DrawModel(int a);		//显示接口
	void	fire(int a);			//射击动作变换
};

#endif // !defined(AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_)
