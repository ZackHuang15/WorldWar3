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
#define TREECOUNT 100//��������

// int iGameState;//��Ϸ״̬
// int iEnemyNum;	//��������
struct OBJPOSI			//�����λ�ýṹ
{
	float x,z;			//λ������
	float h;			//�����
	float size;			//��С����
	int cactus;			//����
};
class baiscobj  
{
public:
	baiscobj();
	virtual ~baiscobj();
public:
	OBJPOSI		objposi[TREECOUNT];			//����λ�ýṹ����
	people* m_people;
	void settml(int p);						//��ʾ�ϰ�λ�ã���С
	void zangan(float x,float z);			//��ײ����
	BOOL iftf(int i);						//�ж��ϰ�
	bool Hitexam(float x,float y,float z);	//�ӵ���ײ���
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

	CExplosion* explosion;				//��ը���������
	bool isExplosion;					//��ը��ʶ
	float px,py,pz;					//��ըλ��
	void Explosion(float x,float y,float z,int b,float a);//��ը��ʼ��
	void plosion();
	CInputSystem *	inputSys; 
	float		rocketX,rocketY,rocketZ; //��ըλ��
	int Expl;							//�ӵ����м���
	void fire();
	void showStart();
	void showInfo();
	void show();		//OpenGL->Render���ø÷���
};

#endif // !defined(AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_)
