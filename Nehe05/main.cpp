#include <iostream>
#include <Windows.h>
#include <gl\glew.h>
#include <gl\freeglut.h>
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"freeglut.lib")


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int DrawGLScene(GLvoid);


GLvoid Reshape(GLsizei width, GLsizei height);


GLvoid init(GLvoid);

GLvoid KillGLWindow(GLvoid);

BOOL CreateGLWindow(char* title, int weidht, int height, int bit, bool fullScreenFlag);
BOOL keys[256];
bool active = true;
bool fullscreen = false;
HDC hDC = NULL;
HGLRC hRC = NULL;
HWND  hWnd = NULL;
HINSTANCE hInstance;

GLfloat angle = 0.0;

int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glTranslatef(-1.5, 0.0, -6);
	glRotatef(angle, 0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0f, -1.0, 1.0);

		glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
		glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);

		glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
		glColor3f(0.0, 1.0, 0.0);

	glVertex3f(-1.0, -1.0, -1.0);
		glColor3f(1.0f, 0.0f, 0.0f);		// 红色
	glVertex3f(0.0f, 1.0f, 0.0f);			// 三角形的上顶点 (左侧面)
		glColor3f(0.0f, 0.0f, 1.0f);		// 蓝色
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 三角形的左下顶点 (左侧面)
		glColor3f(0.0f, 1.0f, 0.0f);		// 绿色
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 三角形的右下顶点 (左侧面)
	glEnd();								// 金字塔绘制结束

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -7.0f);		// 先右移再移入屏幕
	glRotatef(angle, 1.0f, 1.0f, 1.0f);		// 在XYZ轴上旋转立方体
	glBegin(GL_QUADS);						// 开始绘制立方体
	glColor3f(0.0f, 1.0f, 0.0f);			// 颜色改为蓝色
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右上顶点 (顶面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左上顶点 (顶面)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的左下顶点 (顶面)
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的右下顶点 (顶面)
	
	glColor3f(1.0f, 0.5f, 0.0f);			// 颜色改成橙色
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的右上顶点(底面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的左上顶点(底面)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 四边形的左下顶点(底面)
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右下顶点(底面)
	
	glColor3f(1.0f, 0.0f, 0.0f);			// 颜色改成红色
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的右上顶点(前面)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的左上顶点(前面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的左下顶点(前面)
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的右下顶点(前面)
	
	glColor3f(1.0f, 1.0f, 0.0f);			// 颜色改成黄色
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右上顶点(后面)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 四边形的左上顶点(后面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左下顶点(后面)
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右下顶点(后面)
	
	glColor3f(0.0f, 0.0f, 1.0f);			// 颜色改成蓝色
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的右上顶点(左面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左上顶点(左面)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 四边形的左下顶点(左面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的右下顶点(左面)
	
	glColor3f(1.0f, 0.0f, 1.0f);			// 颜色改成紫罗兰色
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右上顶点(右面)
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的左上顶点(右面)
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的左下顶点(右面)
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右下顶点(右面)
	glEnd();								// 立方体绘制结束

	angle += 0.2f;							// 增加三角形的旋转变量
	angle -= 0.15f;							// 减少四边形的旋转变量
	return TRUE;							// 继续运行

	glEnd();

	return TRUE;
}
BOOL CreateGLWindow(char* title, int width, int height, int bit, bool fullScreenFlag)
{
	GLuint		PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;

	RECT WindowRect;
	WindowRect.left = 0;
	WindowRect.right = width;
	WindowRect.top = 0;
	WindowRect.bottom = height;

	fullscreen = fullScreenFlag;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"OpenGL";
	RegisterClass(&wc);

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPEDWINDOW;

	AdjustWindowRectEx(&WindowRect, dwStyle, NULL, dwExStyle);

	hWnd = CreateWindowEx(dwExStyle, L"OpenGL", (LPCWSTR)title, dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN
		, 0, 0, WindowRect.right, WindowRect.bottom, NULL, NULL, hInstance, NULL);



	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};
	hDC = GetDC(hWnd);
	PixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, PixelFormat, &pfd);

	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	//调用opemGL API
	Reshape(width, height);
	init();
	return TRUE;
}
GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass(L"OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}
GLvoid init(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


GLvoid Reshape(GLsizei width, GLsizei height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	LPSTR lpCmdLine,
	int cmdShow)
{
	MSG msg;
	BOOL done = false;

	CreateGLWindow("openGL", 640, 480, 32, true);

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done = TRUE;
				}
				else
				{
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}
			if (keys[VK_F1])
			{
				keys[VK_F1] = FALSE;
				KillGLWindow();
				fullscreen = !fullscreen;
				if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
				{
					return 0;
				}
			}
		}
	}
	//注册窗口类

	//程序初始化

	//消息循环
	return (msg.wParam);
}



LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE

		angle += 10;
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		Reshape(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
