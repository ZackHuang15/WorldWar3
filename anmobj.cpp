#include "stdafx.h"
#include "anmobj.h"
#include "baiscobj.h"

int dongzuo[7] = {0,2,2,7,12,14,14};
extern baiscobj* m_baiscobj;
//����ģ�ͳ�ʼ��
anmobj::anmobj()
{
// 	model[0] = NULL;model[1] = NULL;		//ģ�����
// 	texture[0] = NULL;texture[1] = NULL;	//��ͼ�ÿ�
// 	getobj("data/ģ��/ʿ��0/");				//ʿ��ģ��
// 	for(int i =0;i<RNSHU;i++)				//ѭ����20�����󸳳�ֵ
// 	{	
// 		man[i].qd[0] = MAP +80+rand()%20;	//���X
// 		man[i].qd[1] = MAP -10+i*1;			//���Z
// 		man[i].zd[0] = MAP +0-rand()%5;		//�յ�X
// 		man[i].zd[1] = MAP -10+i*1;			//�յ�Z
// 		man[i].dz = 1;						//��ʼ��������
// 	}
}

anmobj::~anmobj()
{

}

//����ģ��
void anmobj::getobj(CString na)
{
	anim[0]=anim[1]=NULL;			//���������ÿ�
	if(model[0]!=NULL)				//ģ��0���ǿ�
	{
		delete[] model[0];			
		model[0] = NULL;			//ģ��0���
	}
	if(model[1]!=NULL)				//ģ��1���ǿ�
	{
		delete[] model[1];
		model[1] = NULL;			//ģ��1���
	}
	model[0] = md2_readModel(na+"tris.md2");	//����ģ��0 ����ģ��
	texture[0] = new Texture(na+"tris.PCX");	//������ͼ0
	model[1] = md2_readModel(na+"weapon.md2");	//����ģ��1	����ģ��
	texture[1] =new Texture(na+"weapon.PCX");//������ͼ1
	if(model[1]!=NULL)
		size[1] = md2_getAnimationCount(model[1]);		//ȡģ��1�Ķ�����
	if(model[0]!=NULL)
		size[0] = md2_getAnimationCount(model[0]);		//ȡģ��0�Ķ�����
	animations(model[0],0);						//ȡģ��0�Ķ�������
	for (int i = 0;i<RNSHU;i++)					//��RNSHU�����󸳳�ֵ
	{
		counter[i] = 0;							//��������0
		frame[i] = (float)(40+rand()%5);		//�������к���������
	}
}

//��ȡ��������
animation* anmobj::animations(md2_model_t* model,int p)//��ȡģ��p�Ķ�������anim������������Ϊ��Ӧ����name�����֡start���յ�֡end
{
	if (size[p]==0)return 0;					//������Ϊ0����
	if(anim[p]!=NULL)delete[] anim[p];			//�������в��ǿգ�ɾ��
	anim[p] = new animation[size[p]];			//�½�������������
	for(int i =0;i<size[p];i++)					//�����ж�����ѭ��
	{
		strcpy(anim[p][i].name,md2_getAnimationName(model,i));				//�����������е�anim[p]
		md2_getAnimationFrames(model,i,&anim[p][i].start,&anim[0][i].end);	//���������и���ģ��
	}
	return 0;
}

//��ʾMD2ģ��
void anmobj::setman(int i,float y)					//��ʾģ�� iΪģ����ţ�yΪ���θ߶�
{	
	if(model[0]==NULL) return;						//ģ��Ϊ�շ���
	srand(timeGetTime());
	man[i].qd[2]=y;
	counter[i]++;									//ģ��i����ָ���һ
	if(counter[i]>1)								//��������1�����ڶ�����ʱ
	{	
		counter[i]=0;								//ģ��i��������
		//frame[i]++;
		if (man[i].dz!=19) frame[i]++;
		else frame[i]=man[i].death;
		if (man[i].dz==1)							//�ܶ���
		{
			if (manmove(i)==true)					//��Ŀ���
			{
				if (man[i].dz>15)
				{
					if(man[i].dz==16)man[i].death=177;	//����֡
					if(man[i].dz==17)man[i].death=183;	//����֡
					if(man[i].dz==18)man[i].death=189;	//����֡
					man[i].dz=19;frame[i]-=1;
					return;
				}
			}
			man[i].dz=dongzuo[rand()%7];			//���ѡȡһ������
			frame[i]=anim[0][man[i].dz].start;		//ȡ��ѡȡ�����Ŀ���֡
		}
	}
	if (frame[i]>anim[0][man[i].dz].end)			//������β֡����
	{
		if(man[i].dz>15)
		{
			if(man[i].dz==16)man[i].death=177;
			if(man[i].dz==17)man[i].death=183;
			if(man[i].dz==18)man[i].death=189;
			man[i].dz=19;frame[i]-=1;
			return;
		}
		if(man[i].dz!=1)
		{
			man[i].dz=dongzuo[rand()%7];
			if (rand()%10==0)
			{
				man[i].dz=1;
				man[i].zd[0]=RAND_COORD((MAP_W-1)*MAP_SCALE);//���Ŀ��X��
				man[i].zd[1]=RAND_COORD((MAP_W-1)*MAP_SCALE);//���Ŀ��Z��
			}
		}
		frame[i]=anim[0][man[i].dz].start;				//ȡ��ѡȡ�����Ŀ�ʼ֡
	}

// 		if(man[i].dz!=1) 
// 			man[i].dz=dongzuo[rand()%7];			//���ѡȡһ������
// 		frame[i]=anim[0][man[i].dz].start;			//ȡ��ѡȡ�����Ŀ���֡
// 		}
// 	}
	glPushAttrib(GL_CURRENT_BIT);					//����������ɫ��ʵ��
	glPushMatrix();									//ѹ���ջ
	glTranslatef(man[i].qd[0],/*y*/man[i].qd[2], -man[i].qd[1]);	//ģ����ʾλ��
	//glRotatef(-180,0,1,0);							//ģ����Y��ת180��
	glRotatef(re[i]+90,0,1,0);
	glScaled(.06f,.06f,.06f);						//����ģ����С��3%
	glEnable(GL_TEXTURE_2D);						//��ͼ��Ч
	if(model[0]!=NULL)								//����ģ�ʹ���
	{	
		texture[0]->ChangeSettings(GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR,
		GL_CLAMP,GL_CLAMP,0);						//����������ͼ
		md2_drawModel (model[0],(int)frame[i],0,0);	//��ʾ����ģ��
	}
	if(model[1]!=NULL /*&& man[i].dz<size[1]-1*/)	//����ģ�ʹ���
	{	
		texture[1]->ChangeSettings(GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR,
		GL_CLAMP,GL_CLAMP,0);						//����������ͼ
		md2_drawModel (model[1],(int)frame[i],0,0);	//��ʾ����ģ��
	}
	glDisable(GL_TEXTURE_2D);						//ȡ����ͼ
	glPopMatrix();									//������ջ
	glPopAttrib();									//�ָ�ǰһ����
}

bool anmobj::manmove(int i)
{
	float spx=.5f,spz=.5f;				//�ƶ��ٶ�
	float qx=man[i].qd[0]-man[i].zd[0];	//X��ǰ��Ŀ��λ�ò�
	float qz=man[i].qd[1]-man[i].zd[1];	//Z��ǰ��Ŀ��λ�ò�
	float qxa=abs(qx);					//Xλ�ò����ֵ
	float qza=abs(qz);					//Zλ�ò����ֵ
	if ((int)qx==0&&(int)qz==0)return true;
	if(qxa<spx) spx = qxa;				//λ�ò�㲽��
	if(qza<spz) spz = qza;
	if((int)qx!=0) man[i].qd[0]-=(qxa/qx*spx);//��ǰλ�ü�����
	if((int)qz!=0) man[i].qd[1]-=(qza/qz*spz);
	if((int)qx>0&&(int)qz<0)
	{re[i]=45;return false;}			//ȡ������
	if((int)qx>0&&(int)qz>0)
	{re[i]=135;return false;}			//ȡ������
	if((int)qx<0&&(int)qz>0)
	{re[i]=225;return false;}			//ȡ������
	if((int)qx<0&&(int)qz<0)
	{re[i]=295;return false;}			//ȡ������
	if((int)qz<0)
	{re[i]=0;return false;}				//ȡ����
	if((int)qx>0)
	{re[i]=90;return false;}			//ȡ����
	if((int)qz>0)
	{re[i]=180;return false;}			//ȡ����
	if((int)qz<0)
	{re[i]=270;return false;}			//ȡ����
	return false;
}

void anmobj::drawModel(int id,float x,float y,float z,int iframe,int iAngle)
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();

	glTranslatef(x,y,z);
	//��ת
	glRotatef(iAngle*90,0,1,0);
	//��С
	glScaled(.06f,.06f,.06f);

	//role ģ�Ͳ�Ϊ�գ��� iframeС�����֡��
	if(model[0]!=NULL && model[0]->header.numFrames>iframe)
	{
		md2_drawModel (model[0],iframe,0,0);
	}
	//weapon
	if(model[1]!=NULL && model[1]->header.numFrames>iframe)
	{	
		md2_drawModel (model[1],iframe,0,0);
	}

	glPopMatrix();
	glPopAttrib();
}