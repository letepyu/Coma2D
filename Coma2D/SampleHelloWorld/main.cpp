#include <Windows.h>
#include <iostream>
#include <Coma2D/coma2d.h>

using namespace coma2d;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	ComaWindow* window = new ComaWindow(hInstance, nCmdShow);
	window->SetScreenSize(800, 480);
	window->SetTitle(TEXT("HELLO WORLD!"));

	ComaRenderer* renderer = new ComaRenderer();
	renderer->SetBackgroundColor(0.0f, 0.0f, 0.0f);

	ComaDevice* device = ComaDevice::GetDevice();
	device->SetWindowRenderer(window, renderer);

	if (!device->InitDevice())
	{
		MessageBox(NULL, TEXT("Coma2D device initialization failed."), TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	Scene* scene = new Scene();
	TextView* textView = new TextView(Size{600,40}, L"Hello Coma2D World!", L"Ariel", 40.0f, Color{1,1,1}, ALIGN_CENTER);
	textView->SetPosition(100, 220);

	scene->AddChild(textView);

	device->GetSceneManager()->ChangeScene(scene);

	if (!device->Run())
	{
		MessageBox(NULL, TEXT("Coma2D failed to run."), TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	if (textView) delete textView;
	if (device) device->ReleaseAll();

	return 0;
}

