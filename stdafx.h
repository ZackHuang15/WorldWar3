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
#include <afxwin.h>		//加载MFC
#include <windows.h>	// Windows的头文件

#include <mmsystem.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <gl\gl.h>		// OpenGL32库的头文件
#include <gl\glu.h>		// GLu32库的头文件
#include <gl\glaux.h>	// GLaux库的头文件

#include "../include/vectorlib.h"
#include "../include/3DS.H"
#include "../include/md2.h"
#include "../include/texture.h"
#include "../include/MDLFormat.h"
#include "../include/MDLModel.h"
#include "explosion.h"				//爆炸
#include "../include/InputSystem.h"//鼠标接口，基于DirectX 8.0 需导入相关库
#include "mykey.h"					//自定义键盘输入接口

#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "opengl32.lib")	// OpenGL32连接库
#pragma comment( lib, "glu32.lib")		// GLu32连接库
#pragma comment( lib, "glaux.lib")		// GLaux连接库
#pragma comment (linker,"/NODEFAULTLIB:libcp.lib")//VS2005后已被删除
#pragma comment (linker,"/NODEFAULTLIB:libc.lib")
#pragma comment(lib,"dxguid.lib")		//MS DX8鼠标接口
#pragma comment(lib,"dinput8.lib")		//MS DX8鼠标接口
#pragma comment(lib,"texture.lib")		//加载PCX贴图需此库

#define MAP_W       32       // size of map along x-axis 32 
#define MAP_SCALE   24.0f     // the scale of the terrain map
#define MAP			MAP_W*MAP_SCALE/2
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define RAND_COORD(x)   ((float)rand()/RAND_MAX * (x))
#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
#define RNSHU 20

#define GAME_NULL -1
#define GAME_PRE_ANI 0
//游戏开始菜单
#define GAME_MENU 1
//游戏进行中
#define GAME_IN 2
#define GAME_WIN 3
#define GAME_FAIL 4
//进入地图前初始化
#define GAME_IN_INIT 5
#define GAME_PASS 6
#define GAME_ERR 10

//字体
#define FONT0 0
#define FONT1 1
#define FONT2 2
#define FONT3 3
#define FONT4 4
#define FONT5 5

//开屏动画时间 单位: 秒
#define TIME_PRE_ANI 4
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
