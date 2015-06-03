#pragma once
#include "EventDispatcher.h"
#include "ComaRenderer.h"
namespace Coma2D
{
	class ComaWindow :
		public EventDispatcher
	{
	public:
		ComaWindow(HINSTANCE hInstance);
		virtual ~ComaWindow();

		//Window Running Func
		bool	createWindow();
		bool	run();
		LRESULT messageProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
	public:
		bool	updateRectData();	//windowRect, windowPosition ����

		//Window Size Getter
		RECT	getWindowRect();
		POINT	getWindowPosition();
		RECT	getScreenSize();

		//Window Size Setter
		bool setWindowPosition	(int x, int y);
		bool setWindowPosition	(POINT position);
		bool setScreenSize		(int width, int height);
		bool setScreenSize		(RECT size);
		bool setWindowRect		(int x, int y, int width, int height);
		bool setWindowRect		(RECT rect);

	private:
		bool changeWindowSize(POINT position, RECT size);	//������ ũ��,��ġ ���� �� ���� ���� ����
	private:
		//Window Essencials
		HINSTANCE	hInstance;
		HWND		hWnd;

		//Window Attributes
		POINT	windowPosition;
		RECT	screenRect;
		RECT	windowRect;
		

		/*
		//Getter
		HINSTANCE		getInstance()	{return hInstance;}
		HWND			getWindow()		{return hWnd;}
		ComaRenderer*	getRenderer()	{return renderer;}
		bool			isRunning()		{return isRunning;}


		//Setter
		bool			setRenderer(ComaRenderer* renderer);
		bool			setSize(int width, int height);
		bool			setMinimumSize(int width, int height);
		bool			setMaximumSize(int width, int height);
		void			setTitle(const char* title);
		

	private:
		//Windows Essensials
		HINSTANCE		hInstance;
		HWND			hWnd;
		ComaRenderer*	renderer;
		
		
		//Windows Attributes
		POINT			clientPosition;
		RECT			clientRect;
		RECT			minimumClientSize;
		RECT			maximumClientSize;
		bool			resizable;
		const char*		title;

		//Windows Status
		
		bool			isAvailable;
		bool			isResizing;
		bool			isRunning; */
	};
}

