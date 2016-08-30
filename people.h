#if !defined AFX_PEOPLE_H
#define AFX_PEOPLE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



struct ROLE
{
	int id;	//ID
	//坐标
	int x;
	int y;
	int z;

	int w;
	int h;

	int iframe;
	int iCurrentAni;	

	//移动部分
	int iAngle;
	int iMoveDir;
	int iMoveSpeed;

	//人物属性
	int hp;//生命值
	int hpMax;

	int show;	//是否显示

	int r;//旋转角度
};

class people
{
public:
	people();
	~people();
	void init();
	void show();
	//void checkRole();		//放到baiscobj
	void showEnemyHp();		//显示敌人血量
	//data

	//enemy
	struct ROLE MapEnemyArray[RNSHU];
	int iMapEnemyCursor;
	//map人物活动区域
	RECT maprect[RNSHU];
	unsigned int  maprectTex[RNSHU];
	int iMapRectNum;
	//
	int iEnemyNum;	//敌人数量
	int iHp;	//玩家生命值
	//攻击提示
	int iAttackLife;
	int iAttackMaxLife;
};


#endif // !defined(AFX_ANMOBJ_H__46249C44_7C55_4407_AAE7_790A324FB6DE__INCLUDED_)