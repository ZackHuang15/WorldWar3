#include "stdafx.h"
#include "anmobj.h"
#include "baiscobj.h"

int dongzuo[7] = {0,2,2,7,12,14,14};
extern baiscobj* m_baiscobj;
//动作模型初始化
anmobj::anmobj()
{
// 	model[0] = NULL;model[1] = NULL;		//模型清空
// 	texture[0] = NULL;texture[1] = NULL;	//贴图置空
// 	getobj("data/模型/士兵0/");				//士兵模型
// 	for(int i =0;i<RNSHU;i++)				//循环对20个对象赋初值
// 	{	
// 		man[i].qd[0] = MAP +80+rand()%20;	//起点X
// 		man[i].qd[1] = MAP -10+i*1;			//起点Z
// 		man[i].zd[0] = MAP +0-rand()%5;		//终点X
// 		man[i].zd[1] = MAP -10+i*1;			//终点Z
// 		man[i].dz = 1;						//初始动作，跑
// 	}
}

anmobj::~anmobj()
{

}

//调入模型
void anmobj::getobj(CString na)
{
	anim[0]=anim[1]=NULL;			//动作序列置空
	if(model[0]!=NULL)				//模型0不是空
	{
		delete[] model[0];			
		model[0] = NULL;			//模型0清空
	}
	if(model[1]!=NULL)				//模型1不是空
	{
		delete[] model[1];
		model[1] = NULL;			//模型1清空
	}
	model[0] = md2_readModel(na+"tris.md2");	//调入模型0 人物模型
	texture[0] = new Texture(na+"tris.PCX");	//调入贴图0
	model[1] = md2_readModel(na+"weapon.md2");	//调入模型1	武器模型
	texture[1] =new Texture(na+"weapon.PCX");//调入贴图1
	if(model[1]!=NULL)
		size[1] = md2_getAnimationCount(model[1]);		//取模型1的动作数
	if(model[0]!=NULL)
		size[0] = md2_getAnimationCount(model[0]);		//取模型0的动作数
	animations(model[0],0);						//取模型0的动作序列
	for (int i = 0;i<RNSHU;i++)					//对RNSHU个对象赋初值
	{
		counter[i] = 0;							//计数器清0
		frame[i] = (float)(40+rand()%5);		//动作序列号置任意数
	}
}

//获取动作序列
animation* anmobj::animations(md2_model_t* model,int p)//获取模型p的动作序列anim，动作序列作为对应动作name的起点帧start和终点帧end
{
	if (size[p]==0)return 0;					//动作数为0返回
	if(anim[p]!=NULL)delete[] anim[p];			//动作序列不是空，删除
	anim[p] = new animation[size[p]];			//新建动作序列数组
	for(int i =0;i<size[p];i++)					//对所有动作数循环
	{
		strcpy(anim[p][i].name,md2_getAnimationName(model,i));				//拷贝动作序列到anim[p]
		md2_getAnimationFrames(model,i,&anim[p][i].start,&anim[0][i].end);	//将动作序列赋给模型
	}
	return 0;
}

//显示MD2模型
void anmobj::setman(int i,float y)					//显示模型 i为模型序号，y为地形高度
{	
	if(model[0]==NULL) return;						//模型为空返回
	srand(timeGetTime());
	man[i].qd[2]=y;
	counter[i]++;									//模型i计数指针加一
	if(counter[i]>1)								//计数大于1，用于动作延时
	{	
		counter[i]=0;								//模型i计数置零
		//frame[i]++;
		if (man[i].dz!=19) frame[i]++;
		else frame[i]=man[i].death;
		if (man[i].dz==1)							//跑动中
		{
			if (manmove(i)==true)					//到目标点
			{
				if (man[i].dz>15)
				{
					if(man[i].dz==16)man[i].death=177;	//死亡帧
					if(man[i].dz==17)man[i].death=183;	//死亡帧
					if(man[i].dz==18)man[i].death=189;	//死亡帧
					man[i].dz=19;frame[i]-=1;
					return;
				}
			}
			man[i].dz=dongzuo[rand()%7];			//随机选取一个动作
			frame[i]=anim[0][man[i].dz].start;		//取被选取动作的开市帧
		}
	}
	if (frame[i]>anim[0][man[i].dz].end)			//到动作尾帧了吗？
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
				man[i].zd[0]=RAND_COORD((MAP_W-1)*MAP_SCALE);//随机目标X量
				man[i].zd[1]=RAND_COORD((MAP_W-1)*MAP_SCALE);//随机目标Z量
			}
		}
		frame[i]=anim[0][man[i].dz].start;				//取被选取动作的开始帧
	}

// 		if(man[i].dz!=1) 
// 			man[i].dz=dongzuo[rand()%7];			//随机选取一个动作
// 		frame[i]=anim[0][man[i].dz].start;			//取被选取动作的开市帧
// 		}
// 	}
	glPushAttrib(GL_CURRENT_BIT);					//保存现有颜色属实性
	glPushMatrix();									//压入堆栈
	glTranslatef(man[i].qd[0],/*y*/man[i].qd[2], -man[i].qd[1]);	//模型显示位置
	//glRotatef(-180,0,1,0);							//模型绕Y轴转180度
	glRotatef(re[i]+90,0,1,0);
	glScaled(.06f,.06f,.06f);						//整个模型缩小到3%
	glEnable(GL_TEXTURE_2D);						//贴图有效
	if(model[0]!=NULL)								//人物模型存在
	{	
		texture[0]->ChangeSettings(GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR,
		GL_CLAMP,GL_CLAMP,0);						//设置人物贴图
		md2_drawModel (model[0],(int)frame[i],0,0);	//显示人物模型
	}
	if(model[1]!=NULL /*&& man[i].dz<size[1]-1*/)	//武器模型存在
	{	
		texture[1]->ChangeSettings(GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR,
		GL_CLAMP,GL_CLAMP,0);						//设置武器贴图
		md2_drawModel (model[1],(int)frame[i],0,0);	//显示武器模型
	}
	glDisable(GL_TEXTURE_2D);						//取消贴图
	glPopMatrix();									//弹出堆栈
	glPopAttrib();									//恢复前一属性
}

bool anmobj::manmove(int i)
{
	float spx=.5f,spz=.5f;				//移动速度
	float qx=man[i].qd[0]-man[i].zd[0];	//X当前，目标位置差
	float qz=man[i].qd[1]-man[i].zd[1];	//Z当前，目标位置差
	float qxa=abs(qx);					//X位置差绝对值
	float qza=abs(qz);					//Z位置差绝对值
	if ((int)qx==0&&(int)qz==0)return true;
	if(qxa<spx) spx = qxa;				//位置差不足步长
	if(qza<spz) spz = qza;
	if((int)qx!=0) man[i].qd[0]-=(qxa/qx*spx);//当前位置减步长
	if((int)qz!=0) man[i].qd[1]-=(qza/qz*spz);
	if((int)qx>0&&(int)qz<0)
	{re[i]=45;return false;}			//取东北向
	if((int)qx>0&&(int)qz>0)
	{re[i]=135;return false;}			//取东南向
	if((int)qx<0&&(int)qz>0)
	{re[i]=225;return false;}			//取西南向
	if((int)qx<0&&(int)qz<0)
	{re[i]=295;return false;}			//取西北向
	if((int)qz<0)
	{re[i]=0;return false;}				//取北向
	if((int)qx>0)
	{re[i]=90;return false;}			//取东向
	if((int)qz>0)
	{re[i]=180;return false;}			//取南向
	if((int)qz<0)
	{re[i]=270;return false;}			//取西向
	return false;
}

void anmobj::drawModel(int id,float x,float y,float z,int iframe,int iAngle)
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();

	glTranslatef(x,y,z);
	//旋转
	glRotatef(iAngle*90,0,1,0);
	//缩小
	glScaled(.06f,.06f,.06f);

	//role 模型不为空，且 iframe小于最大帧数
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