#if !defined(AFX_ANMOBJ_H__46249C44_7C55_4407_AAE7_790A324FB6DE__INCLUDED_)
#define AFX_ANMOBJ_H__46249C44_7C55_4407_AAE7_790A324FB6DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct animation	//ģ�͵Ķ������нṹ
{
	char name[16];	//16������
	int start;		//�������
	int end;		//�����յ�
};
struct MAN
{
	float qd[3];	//���λ��
	float zd[3];	//�յ�λ��
	int dz;			//����
	bool death;
};

class anmobj
{
public:
	anmobj();
	virtual ~anmobj();
public:
	bool manmove(int i);		//������ƶ�
	int re[RNSHU];				//ģ�͵�����Ƕ�
	md2_model_t* model[2];		//����ģ������
	Texture* texture[2];		//������ͼָ��
	animation* anim[2];			//���嶯����������
	int size[2];				//������
	float frame[RNSHU];			//�������к�
	MAN man[RNSHU];				//ģ�Ͷ���
	int counter[RNSHU];			//������
	void getobj(CString na);	//����ģ��
	animation* animations(md2_model_t* model,int p);//���붯������
	void setman(int i,float y);	//��ʾģ��
	void drawModel(int i,float x,float y,float z,int iFrame,int iAngel);//�µ���ʾģ�ͺ���
};

#endif // !defined(AFX_ANMOBJ_H__46249C44_7C55_4407_AAE7_790A324FB6DE__INCLUDED_)