#if !defined AFX_PEOPLE_H
#define AFX_PEOPLE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



struct ROLE
{
	int id;	//ID
	//����
	int x;
	int y;
	int z;

	int w;
	int h;

	int iframe;
	int iCurrentAni;	

	//�ƶ�����
	int iAngle;
	int iMoveDir;
	int iMoveSpeed;

	//��������
	int hp;//����ֵ
	int hpMax;

	int show;	//�Ƿ���ʾ

	int r;//��ת�Ƕ�
};

class people
{
public:
	people();
	~people();
	void init();
	void show();
	//void checkRole();		//�ŵ�baiscobj
	void showEnemyHp();		//��ʾ����Ѫ��
	//data

	//enemy
	struct ROLE MapEnemyArray[RNSHU];
	int iMapEnemyCursor;
	//map��������
	RECT maprect[RNSHU];
	unsigned int  maprectTex[RNSHU];
	int iMapRectNum;
	//
	int iEnemyNum;	//��������
	int iHp;	//�������ֵ
	//������ʾ
	int iAttackLife;
	int iAttackMaxLife;
};


#endif // !defined(AFX_ANMOBJ_H__46249C44_7C55_4407_AAE7_790A324FB6DE__INCLUDED_)