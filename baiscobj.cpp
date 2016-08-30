
#include "stdafx.h"
#include "baiscobj.h"
#include "anmobj.h"
#include "mdlobj.h"
#include "../include/BITMAP.H"
#include "../include/3DS.H"

extern GLfloat	r; 
float  gao=1.8f;
extern CString	test;
extern anmobj* m_anmobj;
extern mdlobj* m_mdlobj;
extern HWND		hWnd;
extern bool		Lbutdown;
int emecount = 0;
//////////////////////////////////////////////////////////////////////
baiscobj::baiscobj()
{	
	g_eye[0]= MAP;//
	g_eye[2]=-MAP;//
	g_Angle=0;//
	g_elev=-0;//
////////////////////////////////////////////////////////////////////////
// 	char	appdir[256];
// 	GetCurrentDirectoryA(256,appdir);
// 	CString dir=appdir;
// 	if(dir.Right(8)!="运行程序")
// 		SetCurrentDirectoryA("../运行程序");
	////////////////////////////////////////////////////////////////////////
	m_mdlobj->InitGL(0,"data/mdl/qian1.mdl");					//调入指定的MDL动画模型
	g_imageData = LoadBit("data/images/Terrain1.bmp",&g_bit);	//调等高地形图
	LoadT8("data/images/sand0.bmp",	 g_cactus[0]);	//地面帖图
	//LoadT16("data/images/start.bmp",g_cactus[1]);	//开局图片 出错
	LoadT8("data/images/4RBack.bmp",g_cactus[2]);	//天空贴图后
	LoadT8("data/images/4Front.bmp",g_cactus[3]);	//天空贴图前
	LoadT8("data/images/4Top.bmp",	 g_cactus[4]);	//天空贴图顶
	LoadT8("data/images/4Left.bmp", g_cactus[5]);	//天空贴图左
	LoadT8("data/images/4Right.bmp",g_cactus[6]);	//天空贴图右
	LoadT16("data/images/CACTUS0.BMP",g_cactus[11]);    //树1帖图
	LoadT16("data/images/CACTUS1.BMP",g_cactus[12]);    //树2帖图
	LoadT16("data/images/CACTUS2.BMP",g_cactus[13]);    //树3帖图
	LoadT16("data/images/CACTUS3.BMP",g_cactus[14]);    //树4帖图
	InitTerrain(5);//初始化地面
	//爆炸
	LoadT16("data/images/explosion.bmp",g_cactus[15]); 
	isExplosion = true; 
	explosion=NULL;     
	Explosion(0,0,0,1,1); 
	//
	m_3ds=new CLoad3DS();
	load3dobj("data/3ds","Penguin2.3DS",0);//导入3DS文件
	//鼠标
	inputSys = new CInputSystem;			//建立鼠标接口
	bool useDInput =
		inputSys->Initialize(hWnd,(HINSTANCE)GetModuleHandle(NULL),
		true,IS_USEKEYBOARD|IS_USEMOUSE);	//鼠标接口初始化
	
	Lbutdown=false;                     

	m_anmobj=new anmobj;
	m_anmobj->model[0]=NULL;
	m_anmobj->model[1]=NULL;
	m_anmobj->getobj("data/模型/士兵0/");	
	for(int i =0;i<RNSHU;i++)				//循环对20个对象赋初值
	{	
		m_anmobj->man[i].qd[0]=MAP+80+rand()%50;
		m_anmobj->man[i].qd[1]=MAP-10+rand()%50;//
		m_anmobj->man[i].zd[0]=MAP+20-rand()%5;
		m_anmobj->man[i].zd[1]=MAP-10+i*1;//
		m_anmobj->man[i].dz=1;	
		m_anmobj->man[i].death=0;
	}

	srand(100);								//产生树的固定随机数种子
	for(int i=0;i<TREECOUNT;i++)			//树的数量
	{
		objposi[i].x= RAND_COORD((MAP_W-1)*MAP_SCALE);	//随机产生的位置X
		objposi[i].z= RAND_COORD((MAP_W-1)*MAP_SCALE);	//随机产生的位置Z
		objposi[i].size=5.0f+rand()%5;					//大小5~10随机
		objposi[i].h=-objposi[i].size/10;				//深浅
		objposi[i].cactus=rand()%4+11;					//树形随机4种
	}
	rocketX = 0;rocketZ = 0;rocketY = 2000;				//子弹位置初值
	rad_xz = 0;											//视点方位角初值                   
	Expl=0;												//子弹飞行计数
	emecount = RNSHU;									//活动敌人数
	glEnable(GL_TEXTURE_2D);							//启用贴图
}
baiscobj::~baiscobj()
{	
	for(int i=0;i<16;i++) glDeleteTextures(1, &g_cactus[i]);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
void baiscobj::light0()
{	
	GLfloat light_position[] = {1.0,5.0,1.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}
BOOL baiscobj::DisplayScene()					//摄像视点
{ 
	float speed=0.5f;	
	float x=g_eye[0],y=g_eye[1],z=g_eye[2];
	mouseXold =0,mouseYold =0;
	inputSys->Update();   
	inputSys->GetMouseMovement(mouseX,mouseY);
	//mouse
	/*  */
	g_Angle +=  (mouseX-mouseXold)*.2f;            
	g_elev  += -(mouseY-mouseYold)*.2f;   
	if(mouseX<50 || mouseX>750 || mouseY<50 || mouseY>550)
	{
		SetCursorPos(400,300);
	}
	mouseXold=mouseX;
	mouseYold=mouseY;
	if (KEY_DOWN(VK_SHIFT))  speed   =speed*2;
	if (KEY_DOWN(VK_LEFT))   g_Angle-=speed*2;
	if (KEY_DOWN(VK_RIGHT))  g_Angle+=speed*2;
	rad_xz = float (3.13149* g_Angle/180.0f);		//转换成弧度角
	//仰角
	if (KEY_DOWN(33))		   g_elev +=speed;
	if (KEY_DOWN(34))		   g_elev -=speed;
	if (g_elev<-100)		   g_elev  =-100;
	if (g_elev> 100)		   g_elev  = 100;
	if (KEY_DOWN(VK_UP))		
	{ g_eye[2]+=(float)sin(rad_xz)*speed;	
	g_eye[0]+=(float)cos(rad_xz)*speed;	
	}
	if (KEY_DOWN(VK_DOWN))	
	{ g_eye[2]-=(float)sin(rad_xz)*speed;
	g_eye[0]-=(float)cos(rad_xz)*speed;	
	}
	//w s a d 移动 支持上下键移动
	if (KEY_DOWN('W') || KEY_DOWN(VK_UP) )					
	{
		g_eye[2]+=(float)sin(rad_xz)*speed;	
		g_eye[0]+=(float)cos(rad_xz)*speed;	
	}
	if (KEY_DOWN('S') || KEY_DOWN(VK_DOWN) )					
	{
		g_eye[2]-=(float)sin(rad_xz)*speed;	
		g_eye[0]-=(float)cos(rad_xz)*speed;
	}
	if (KEY_DOWN('A'))					
	{
		g_eye[2]-=(float)cos(rad_xz)*speed;	
		g_eye[0]+=(float)sin(rad_xz)*speed;	
	}
	if (KEY_DOWN('D'))		
	{
		g_eye[2]+=(float)cos(rad_xz)*speed;	
		g_eye[0]-=(float)sin(rad_xz)*speed;	
	}


	if(g_eye[0]<  MAP_SCALE)			g_eye[0]=  MAP_SCALE;
	if(g_eye[0]> (MAP_W-2)*MAP_SCALE)	g_eye[0]= (MAP_W-2)*MAP_SCALE;
	if(g_eye[2]<-(MAP_W-2)*MAP_SCALE)	g_eye[2]=-(MAP_W-2)*MAP_SCALE;
	if(g_eye[2]> -MAP_SCALE)			g_eye[2]= -MAP_SCALE;
		
	g_eye[1] =GetHeight((float)g_eye[0],(float)g_eye[2])+gao;

	g_look[0] = (float)(g_eye[0] +100*cos(rad_xz));
	g_look[2] = (float)(g_eye[2] +100*sin(rad_xz));
	g_look[1] = g_eye[1] +g_elev;	

	gluLookAt(g_eye[0],g_eye[1],g_eye[2],	
		g_look[0],g_look[1],g_look[2],
		0.0,1.0,0.0	
		);
	////////////////////////////////////////////////////////////////
	int r0=abs((int)g_Angle);
	test.Format("[方位=%03d X=%3.0f y=%3.0f 高=%2.1f 俯仰角=%2.0f,re=%03.0f]",
		r0%360,g_eye[0],-g_eye[2],g_eye[1],g_elev,r);
	r+=1.0f;if(r>360) r=0;

	if (KEY_DOWN(' ')||Lbutdown==true)
	{
		rocketX=g_eye[0],rocketZ=g_eye[2];
		rocketY=GetHeight(rocketX, rocketZ)+1.6f;
		fire();	
		m_mdlobj->fire(1);						//射击动作转换
		sndPlaySound("data/sounds/explode1.wav",SND_ASYNC);
	}
	zangan(x,z);
	return TRUE;
}
//==========================================================================
void baiscobj::InitTerrain(float h)
{ 
	int index = 0;
	int Vertex;
	for (int z = 0; z < MAP_W; z++)
		for (int x = 0; x < MAP_W; x++)
		{ 
			Vertex = z * MAP_W + x;
			g_terrain [Vertex][0] = float(x)*MAP_SCALE;
			//g_terrain [Vertex][1] = (float)(g_imageData[(z*MAP_W+x)*3]/3);
			g_terrain [Vertex][1] = h + FRAND * h;
			g_terrain [Vertex][2] = -float(z)*MAP_SCALE;
			g_texcoord[Vertex][0] = (float) x;
			g_texcoord[Vertex][1] = (float) z;	
			g_index [index++] = Vertex;
			g_index [index++] = Vertex+ MAP_W;
		}
	glEnableClientState(GL_VERTEX_ARRAY);	
	glVertexPointer    (3,GL_FLOAT,0,g_terrain);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer  (2,GL_FLOAT,0,g_texcoord);
}
void baiscobj::DrawSand()
{ 
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]);
	glTexEnvf    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	for (int z = 0; z < MAP_W-1; z++)
		glDrawElements(GL_TRIANGLE_STRIP,MAP_W*2,GL_UNSIGNED_INT,&g_index[z*MAP_W*2]);
}
float baiscobj::GetHeight(float x, float z)
{ 	
	float CameraX = x/MAP_SCALE;
	float CameraZ =-z/MAP_SCALE;  
	int Col0 = int(CameraX);  
	int Row0 = int(CameraZ);
	int Col1 = Col0 + 1;
	int Row1 = Row0 + 1; 
	if (Col1 > MAP_W)	Col1 = 0;
	if (Row1 > MAP_W)	Row1 = 0;
	float h00=g_terrain[Col0 + Row0*MAP_W][1];
	float h01=g_terrain[Col1 + Row0*MAP_W][1];
	float h11=g_terrain[Col1 + Row1*MAP_W][1];
	float h10=g_terrain[Col0 + Row1*MAP_W][1];
	float tx =CameraX - int(CameraX);
	float ty =CameraZ - int(CameraZ);
	float txty = tx * ty;
	return h00*(1.0f-ty-tx+txty) 
		+ h01*(tx-txty)
		+ h11*txty
		+ h10*(ty-txty); 
}
void baiscobj::CreateSkyBox(int a,int wi,int he,int le)
{	
	float width =MAP*wi;
	float height=MAP*he;
	float length=MAP*le;
	float x = MAP  -width /2;
	float y = MAP/a-height/2;
	float z = -MAP -length/2;
	///////////////////////////////////////////////////////////////////////////////
	texture(g_cactus[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,0.0f); glVertex3f(x+width,y,		 z);
	glTexCoord2f(1.0f,1.0f); glVertex3f(x+width,y+height,z); 
	glTexCoord2f(0.0f,1.0f); glVertex3f(x,		y+height,z);
	glTexCoord2f(0.0f,0.0f); glVertex3f(x,		y,		 z);
	glEnd();
	texture(g_cactus[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,0.0f); glVertex3f(x,		y,		 z+length);
	glTexCoord2f(1.0f,1.0f); glVertex3f(x,		y+height,z+length);
	glTexCoord2f(0.0f,1.0f); glVertex3f(x+width,y+height,z+length); 
	glTexCoord2f(0.0f,0.0f); glVertex3f(x+width,y,		 z+length);
	glEnd();

	texture(g_cactus[4]);
	glBegin(GL_QUADS);	
	glTexCoord2f(0.0f,1.0f); glVertex3f(x+width,y+height,z);
	glTexCoord2f(0.0f,0.0f); glVertex3f(x+width,y+height,z+length); 
	glTexCoord2f(1.0f,0.0f); glVertex3f(x,		y+height,z+length);
	glTexCoord2f(1.0f,1.0f); glVertex3f(x,		y+height,z);
	glEnd();
	texture(g_cactus[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,1.0f); glVertex3f(x,		y+height,z);	
	glTexCoord2f(0.0f,1.0f); glVertex3f(x,		y+height,z+length); 
	glTexCoord2f(0.0f,0.0f); glVertex3f(x,		y,		 z+length);
	glTexCoord2f(1.0f,0.0f); glVertex3f(x,		y,		 z);		
	glEnd();
	texture(g_cactus[6]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f); glVertex3f(x+width,y,		 z);
	glTexCoord2f(1.0f,0.0f); glVertex3f(x+width,y,		 z+length);
	glTexCoord2f(1.0f,1.0f); glVertex3f(x+width,y+height,z+length); 
	glTexCoord2f(0.0f,1.0f); glVertex3f(x+width,y+height,z);
	glEnd();
}
void baiscobj::texture(UINT textur)
{	
	glBindTexture  (GL_TEXTURE_2D, textur);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}

bool baiscobj::LoadT8(char *filename, GLuint &texture)
{	
	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);
	if(pImage == NULL)		return false;
	glGenTextures(1, &texture);	
	glBindTexture    (GL_TEXTURE_2D,texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4, pImage->sizeX, 
		pImage->sizeY,GL_RGB, GL_UNSIGNED_BYTE,pImage->data);
	free(pImage->data);
	free(pImage);	
	return true;
}
void baiscobj::LoadT16(char *filename, GLuint &texture)
{ 
	glGenTextures(1, &texture);  
	glBindTexture(GL_TEXTURE_2D, texture);
	BITMAPINFOHEADER bitHeader;
	unsigned char *buffer;  
	buffer=LoadBitmapFileWithAlpha(filename,&bitHeader);
	gluBuild2DMipmaps	
		(
		GL_TEXTURE_2D,  
		4,    
		bitHeader.biWidth, 
		bitHeader.biHeight,
		GL_RGBA, 
		GL_UNSIGNED_BYTE,
		buffer  
		); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	free(buffer);  
}
unsigned char * baiscobj::LoadBit(char *filename, BITMAPINFOHEADER *bitmap)
{ 
	FILE *filePtr;  
	BITMAPFILEHEADER  Header; 
	unsigned char    *Image; 
	unsigned int      imageIdx = 0; 
	unsigned char     tempRGB;  
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)    return NULL;
	fread(&Header, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if (Header.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}
	fread(bitmap, sizeof(BITMAPINFOHEADER), 1, filePtr);
	fseek(filePtr, Header.bfOffBits, SEEK_SET);
	Image = (unsigned char*)malloc(bitmap->biSizeImage);
	if (!Image)
	{ 
		free(Image);
		fclose(filePtr);
		return NULL;
	}
	fread(Image, 1, bitmap->biSizeImage, filePtr);
	if (Image == NULL)
	{ 
		fclose(filePtr);
		return NULL;
	}
	for (imageIdx = 0; imageIdx < bitmap->biSizeImage; imageIdx+=3)
	{ 
		tempRGB = Image[imageIdx];
		Image[imageIdx] = Image[imageIdx + 2];
		Image[imageIdx + 2] = tempRGB;
	}
	fclose(filePtr);
	return Image;
}
/////////////////////////////////////////////////////////////////////////////
void baiscobj::ShowTree(float x,float z,float h,float s,int cactus)
{ 
	glEnable(GL_BLEND);													//启用混色
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);					//指定混合的属性
	glEnable(GL_ALPHA_TEST);											//启用透明
	glAlphaFunc(GL_GREATER, 0);											//设置透明测试
	float mat[16];														//定义数组保存场景矩阵
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);								//取得场景矩阵的数据
	vector3_t X(mat[0], mat[4], mat[8]);								//场景矩阵的X方向矢量
	vector3_t Z(mat[1], mat[5], mat[9]);								//场景矩阵的Z方向矢量
	glBindTexture(GL_TEXTURE_2D, g_cactus[cactus]);						//选择树
	vector3_t pos(x,0.0,-z);											//树的位置x,z矩阵变换
	pos.y = GetHeight(x, -z) + h + s;									//树的位置Y分量
	glBegin(GL_QUADS);													//绘制四边形
	glTexCoord2f(0.0,0.0);glVertex3fv((pos+(X+Z)*-h).v);//左下点
	glTexCoord2f(1.0,0.0);glVertex3fv((pos+(X-Z)* h).v);//右下点
	glTexCoord2f(1.0,1.0);glVertex3fv((pos+(X+Z)* h).v);//右上点
	glTexCoord2f(0.0,1.0);glVertex3fv((pos+(Z-X)* h).v);//左上点
	glEnd();
	glDisable(GL_ALPHA);												//关闭透明
	glDisable(GL_BLEND);												//关闭透明
}

void baiscobj::ShowTree0(float x,float z,float h,float s,int cactus)
{ 
	glPushMatrix();//
	float y = GetHeight(x,-z) + h + s;
	glTranslatef(x,y, -z);
	glRotatef(180, 1.0, 0.0, 0.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glBindTexture(GL_TEXTURE_2D, g_cactus[cactus]);
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-h, h, 0.0f);		// 右上点
	glTexCoord2f(0.0f, 0.0f); glVertex3f( h, h, 0.0f);		// 右上点
	glTexCoord2f(0.0f, 1.0f); glVertex3f( h,-h, 0.0f);		// 右下点
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-h,-h, 0.0f);		// 左下点
	glEnd();
	glDisable(GL_ALPHA);
	glDisable(GL_BLEND);
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////
void baiscobj::load3dobj(char* dir,char* cn,int a)
{	
	char	appdir[256];
	GetCurrentDirectory(256,appdir);
	SetCurrentDirectory(dir);
	m_3ds->Init(cn,a);
	SetCurrentDirectory(appdir);
}
void baiscobj::Scene(int obj,float x,float h,float z,float r,int re,float size)//obj模型序号 x,h,z 位置定位 r模型运动半径 re旋转角度 size模型大小
{
	glPushMatrix();
	float y=GetHeight(x,z)+h;
	glTranslatef(x,y,z);
	glRotatef(re, 0.0, 1.0, 0.0);
	m_3ds->show3ds(obj,0,0.0f,r,size);
	glPopMatrix();
}

void baiscobj::Explosion(float x,float y,float z,int b,float a)//爆炸初始化
{
	if(explosion!=NULL) {delete[] explosion;explosion=NULL;}
	explosion = new CExplosion(b,CVector(0,0,0),a,g_cactus[15]);
	px=x,pz=z,py=y;
	isExplosion = false;
	Expl=0;
}
void baiscobj::plosion()										//爆炸
{ 
	glTranslatef(px,py,pz);			//爆炸定位
	if(isExplosion == false)		//爆炸准备就绪
	{
		explosion->Render();		//引爆
		isExplosion = true;			//已爆炸
	}
	if(isExplosion)					
	{
		explosion->Update(0.10f);	//消除爆炸粒子,括号内为延时参数	
		isExplosion = false;
	}
}

void baiscobj::fire()
{
	if(rocketY>1000) return;						//子弹飞得太高，放弃
	rocketX+=7.0f*(float)cos(rad_xz);				//X方向的步进
	rocketZ+=7.0f*(float)sin(rad_xz);				//Z方向的步进
	rocketY+=9.0f*(float)tan(g_elev*PI/360);		//Y方向的步进
	if(Hitexam(rocketX,rocketY,rocketZ))			//子弹碰撞检测
	{
		Lbutdown=false;
		Explosion(rocketX,rocketY,rocketZ,100,1);
		sndPlaySound("data/sounds/explode.wav",SND_ASYNC);
		rocketY=2000;
		Expl=0;
		return;
	}
	float y=GetHeight(rocketX, rocketZ);			//获得地形高度
	Expl++;											//子弹距离计数
	if((rocketY-y)<0||Expl>40)						//判断子弹是否打到天或地
	{
		Lbutdown=false;								//清楚鼠标按键
		Explosion(rocketX,rocketY,rocketZ,100,1);	//爆炸初始化
		sndPlaySound("data/images/explode2.wav",SND_ASYNC);//枪声
		rocketY=2000;								//清楚子弹
		Expl=0;										//计数清0
		return;										
	}
	glPushAttrib(GL_CURRENT_BIT);					//保存现有颜色属性
	glPushMatrix();									//压入堆栈
	glTranslatef(rocketX,rocketY,rocketZ);			//子弹的定位
	auxWireSphere(.01);								//用一个球代表子弹
	glPopMatrix();									//弹出堆栈
	glPopAttrib();									//恢复前一属性
}

void baiscobj::zangan(float x,float z)
{ 
	float pp;
	for(int i=0;i<TREECOUNT;i++)	
	{ 
		if(iftf(i))	
		{
			pp=g_eye[0];g_eye[0]=x;
			if(!iftf(i))  return;
			else g_eye[0]=pp;
			pp=g_eye[2];g_eye[2]=z;
			if(!iftf(i))  return;	
			else g_eye[2]=pp;
			return;
		}
  }
}
BOOL baiscobj::iftf(int i)				//判断障碍
{ 
	if(fabs(g_eye[0]-objposi[i].x)<objposi[i].size/2&&
		fabs(g_eye[2]+objposi[i].z)<objposi[i].size/2)
		return TRUE;					//遇到障碍
	else return FALSE;
}
void baiscobj::settml(int p)			//显示对象边缘 便于调试碰撞算法
{ 
	float y=GetHeight(objposi[p].x, -objposi[p].z)+1;
	glPushAttrib(GL_CURRENT_BIT);
	glDisable(GL_TEXTURE_2D);//
	glPushMatrix();//
	glTranslatef(objposi[p].x,y,-objposi[p].z);
	auxWireBox(objposi[p].size,objposi[p].size,objposi[p].size);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glPopAttrib();
}
bool baiscobj::Hitexam(float x,float y,float z)
{ 
	//原理：子弹每次刷新坐标,增加距离7.0
	//		检测时，从当前坐标循环6次,每次增加一个单位做检测
	for(int k=0;k<6;k++)	
	{
		for(int i=0;i<RNSHU;i++)
		{
			if(m_anmobj->man[i].dz>15) 
				continue;
			if(	abs(m_anmobj->man[i].qd[0]-x)>1.0f&&
				abs(m_anmobj->man[i].qd[1]+z)>1.0f) 
				continue;								//打偏
			if(	abs(m_anmobj->man[i].qd[0]-x)<.1f&&
				abs(m_anmobj->man[i].qd[2]-y)<.1f&&
				abs(m_anmobj->man[i].qd[1]+z)<.1f)		//击中
			{
				m_anmobj->man[i].dz=16+rand()%3;
				m_anmobj->frame[i]=m_anmobj->anim[0][m_anmobj->man[i].dz].start;
				rocketX=x;	 rocketZ=z;	 rocketY=y;	
				emecount--;	
				return true;
			}
		}
		x+=1.0f*cos(rad_xz);
		z+=1.0f*sin(rad_xz);	
		y+=1.0f*tan(g_elev*PI/360);
	}
	return false;
}


void baiscobj::showStart()
{
	//移动到当前位置
	glTranslatef(0,0,-8.0);
	texture(g_cactus[1]);	
// 	画正方形，变长2.0f*2
// 		glBegin(GL_QUADS);
// 		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f,  0.0f);
// 		glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, -2.0f,  0.0f);
// 		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  2.0f,  0.0f);
// 		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  2.0f,  0.0f);
// 		glEnd();
// 		//移动动画
// 		//指定位置画正方形
// 		glPushAttrib(GL_CURRENT_BIT);
// 		glPushMatrix();							
// 		glDisable(GL_TEXTURE_2D);
// 	
// 		glTranslatef(0,0.0,0.1);
// 		glColor3f(0.0, 0.0, 0.0);
// 		glBegin(GL_QUADS);
// 		glVertex3f(-3.0, -3.0,  0.0f);
// 		glVertex3f( 3.0, -3.0,  0.0f);
// 		glVertex3f( 3.0,  3.0,  0.0f);
// 		glVertex3f(-3.0,  3.0,  0.0f);
// 		glEnd();	
// 	
// 		glEnable(GL_TEXTURE_2D);
// 		glPopMatrix();							
// 		glPopAttrib();
// 		//tSquare(param1*0.2, 0.0, 0.1, 3.0);
}
/*
void baiscobj::showInfo()
{
	char info[50]={0};

	sprintf(info, "enemy number: %d  ",iEnemyNum);
	myfont.settext(50,50,info,FONT1,1,1,1);

	sprintf(info, "HP: %d  ",iHp);
	if(iHp>30)
	{
		//白色显示
		myfont.settext(50,550,info,FONT1,1,1,1);
	}
	else
	{
		myfont.settext(50,550,info,FONT1,1,0,0);	//红色
	}

// 	//攻击提示 敌人生命
// 	if(iAttackLife)
// 	{
// 		glLoadIdentity();
// 		//画头像图标
// 		glDisable(GL_LIGHTING);				
// 		texture0(g_cactus[10]);	
// 		glTranslatef(-0.14,0.15,-1.0);
// 		tPic(0.04f);
// 		glEnable(GL_LIGHTING);
// 		//画生命值		
// 		showEnemyHp();
// 	}


	//获胜
	if(GAME_WIN==iGameState)
	{
		sprintf(info, "胜 利");
		myfont.settext(350,250,info,FONT3,1,1,0);		
	}
	if(GAME_FAIL==iGameState)
	{
		sprintf(info, "失 败");
		myfont.settext(350,250,info,FONT3,1,1,1);		
	}
	if(GAME_PASS==iGameState)
	{
		sprintf(info, "通 关");
		myfont.settext(350,250,info,FONT4,1,1,0);		
	}

// 	if(iShowWorldFrame)
// 	{
// 		sprintf(info, "WORLD: %d",iMatch+1);
// 		myfont.settext(350,250,info,FONT3,1,1,0);		
// 
// 		iShowWorldFrame++;
// 		//地图信息显示时间 TIME_WORLD_INFO
// 		if(iShowWorldFrame > TIME_WORLD_INFO)
// 		{
// 			iShowWorldFrame=0;
// 		}
// 	}
}
*/

void baiscobj::show()
{
	//显示开局图片
	// 	for(int i =0;i<=10000;i++)
	// 		m_baiscobj->showStart();
	DisplayScene();
	CreateSkyBox(3,6,3,6);
	DrawSand();
	srand(100);
	for(int i=0;i<300;i++)
	{
		float x= RAND_COORD((MAP_W-1)*MAP_SCALE);
		float z= RAND_COORD((MAP_W-1)*MAP_SCALE);
		float size=4.0f+rand()%4;	
		float h=-size/10;	
		int   cactus=rand()%4+11;
		ShowTree(x,z,size,h,cactus);
	}
	//m_baiscobj->picter(MAP+10,0,-MAP);
	//显示3DS模型
	Scene(0,MAP+30,0.0f,-MAP,0,180,5.0f);
	//调入MD2
	for(int i=0;i<RNSHU;i++)
	{
		float y = GetHeight(m_anmobj->man[i].qd[0],-m_anmobj->man[i].qd[1]);
		m_anmobj->setman(i,y+1.4f);  
	}
	
// 	for(int i=0;i<RNSHU;i++)
// 	{
// 		if(m_people->MapEnemyArray[i].show)
// 		{				
// 			m_anmobj->drawModel(m_people->MapEnemyArray[i].id,
// 				m_people->MapEnemyArray[i].x,
// 				m_people->MapEnemyArray[i].y+1.4f,
// 				m_people->MapEnemyArray[i].z,
// 				m_people->MapEnemyArray[i].iframe,
// 				m_people->MapEnemyArray[i].iAngle);
// 		}
// 	}
	r+=1.0f;if(r>360) r=0;
	//调入MDL（第一人称模型）
	float xx =g_eye[0];						//取X位置/*+0.6f*cos(rad_xz)*/
	float zz =g_eye[2];						//取Z位置/*+0.6f*sin(rad_xz)*/
	m_mdlobj->DrawModels(
		xx,									//X位置
		GetHeight(xx,zz)+gao,				//Y位置，高
		zz,									//Z位置
		0,									//模型序号
		0.1f,								//模型显示比例
		-g_Angle,							//俯仰角
		g_elev								//方位角
		);				

	//爆炸
// 	if(rand()%32==1)												//随机进入下面爆炸程序
// 	{int x=MAP+10+rand()%30,z=-MAP-10+rand()%20;					//产生爆炸区域X，Z
// 	Explosion(	x,										//爆炸区域X
// 				GetHeight(x,z),				//由地形得爆炸区域Y
// 				z,										//爆炸区域Z
// 				160,									//粒子数
// 				2										//爆炸范围
// 			);											//爆炸初始化
// 	sndPlaySound("data/sounds/explode.wav",SND_ASYNC);				//爆炸声音
// 	}
	////////////////////////////////////////
	fire();
	plosion();											//爆炸
}