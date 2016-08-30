// baiscobj.h: interface for the baiscobj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_)
#define AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "explosion.h"
#include "anmobj.h"
#include "people.h"
#define TREECOUNT 100//树的数量

// int iGameState;//游戏状态
// int iEnemyNum;	//敌人数量
struct OBJPOSI			//对象的位置结构
{
	float x,z;			//位置坐标
	float h;			//树深，长
	float size;			//大小，宽
	int cactus;			//树形
};
class baiscobj  
{
public:
	baiscobj();
	virtual ~baiscobj();
public:
	OBJPOSI		objposi[TREECOUNT];			//树的位置结构变量
	people* m_people;
	void settml(int p);						//显示障碍位置，大小
	void zangan(float x,float z);			//碰撞绕行
	BOOL iftf(int i);						//判断障碍
	bool Hitexam(float x,float y,float z);	//子弹碰撞检测
	float		g_terrain	[MAP_W*MAP_W][3];
	GLuint		g_index		[MAP_W*MAP_W* 2];
	float		g_texcoord	[MAP_W*MAP_W][2];
	void		InitTerrain(float h);	
	void		DrawSand();	
	float		GetHeight(float x, float z); 
	int mouseX, mouseY;	
	int mouseXold,mouseYold;
	float	    g_eye [3]; 
	float	    g_look[3];
	float	    rad_xz;	
	float	    g_Angle;
	float	    g_elev;	
	BOOL		DisplayScene();	

	UINT		g_cactus[16];
	BITMAPINFOHEADER  g_bit;
	unsigned char    *g_imageData; 
	void		CreateSkyBox(int a,int wi,int he,int le);
	void		texture(UINT textur);
	void		light0();    

	void		picter(float x,float y,float z); 
	bool		LoadT8(char *filename, GLuint &texture);
	void		LoadT16(char *filename, GLuint &texture);
	unsigned char* LoadBit(char *filename, BITMAPINFOHEADER *bitmap);

	void		ShowTree(float x,float z,float h,float s,int cactus);
	void		ShowTree0(float x,float z,float h,float s,int cactus);

	CLoad3DS* m_3ds;
	void load3dobj(char* dir,char* cn,int a);
	void Scene(int obj,float x,float h,float z,float r,int re,float size);

	CExplosion* explosion;				//爆炸粒子类变量
	bool isExplosion;					//爆炸标识
	float px,py,pz;					//爆炸位置
	void Explosion(float x,float y,float z,int b,float a);//爆炸初始化
	void plosion();
	CInputSystem *	inputSys; 
	float		rocketX,rocketY,rocketZ; //爆炸位置
	int Expl;							//子弹飞行计数
	void fire();
	void showStart();
	void showInfo();
	void show();		//OpenGL->Render调用该方法
};

#endif // !defined(AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_)
