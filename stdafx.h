// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <afxwin.h>		//����MFC
#include <windows.h>	// Windows��ͷ�ļ�

#include <mmsystem.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <gl\gl.h>		// OpenGL32���ͷ�ļ�
#include <gl\glu.h>		// GLu32���ͷ�ļ�
#include <gl\glaux.h>	// GLaux���ͷ�ļ�

#include "../include/vectorlib.h"
#include "../include/3DS.H"
#include "../include/md2.h"
#include "../include/texture.h"
#include "../include/MDLFormat.h"
#include "../include/MDLModel.h"
#include "explosion.h"				//��ը
#include "../include/InputSystem.h"//���ӿڣ�����DirectX 8.0 �赼����ؿ�
#include "mykey.h"					//�Զ����������ӿ�

#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "opengl32.lib")	// OpenGL32���ӿ�
#pragma comment( lib, "glu32.lib")		// GLu32���ӿ�
#pragma comment( lib, "glaux.lib")		// GLaux���ӿ�
#pragma comment (linker,"/NODEFAULTLIB:libcp.lib")//VS2005���ѱ�ɾ��
#pragma comment (linker,"/NODEFAULTLIB:libc.lib")
#pragma comment(lib,"dxguid.lib")		//MS DX8���ӿ�
#pragma comment(lib,"dinput8.lib")		//MS DX8���ӿ�
#pragma comment(lib,"texture.lib")		//����PCX��ͼ��˿�

#define MAP_W       32       // size of map along x-axis 32 
#define MAP_SCALE   24.0f     // the scale of the terrain map
#define MAP			MAP_W*MAP_SCALE/2
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define RAND_COORD(x)   ((float)rand()/RAND_MAX * (x))
#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
#define RNSHU 20

#define GAME_NULL -1
#define GAME_PRE_ANI 0
//��Ϸ��ʼ�˵�
#define GAME_MENU 1
//��Ϸ������
#define GAME_IN 2
#define GAME_WIN 3
#define GAME_FAIL 4
//�����ͼǰ��ʼ��
#define GAME_IN_INIT 5
#define GAME_PASS 6
#define GAME_ERR 10

//����
#define FONT0 0
#define FONT1 1
#define FONT2 2
#define FONT3 3
#define FONT4 4
#define FONT5 5

//��������ʱ�� ��λ: ��
#define TIME_PRE_ANI 4
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
