/* 
* filename	ComaDevice.cpp
* fileinfo	�����ӿ�ũ ���� �̱��� Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "ComaDevice.h"

#include "Bitmap.h"

COMA_USING_NS

ComaDevice* ComaDevice::device;

ComaDevice::ComaDevice() :window_(nullptr), renderer_(nullptr), running_(false), initialized_(false), resourceManager_(nullptr), sceneManager_(nullptr), inputManager_(nullptr), physicsManager_(nullptr)
{}

ComaDevice::~ComaDevice()
{
	if (resourceManager_) delete resourceManager_;
	if (sceneManager_) delete sceneManager_;
	if (physicsManager_) delete physicsManager_;
	//inputManager�� window���� �������Ƿ� ������ �ʿ䰡 ����.
}

ComaDevice* ComaDevice::GetDevice()
{
	if (device == 0) device = new ComaDevice();
	return device;
}

void ComaDevice::Release()
{
	if (initialized_)
	{
		if (window_)
		{
			window_->RemoveEventListener(WindowEvent::DESTROY, this);
			window_->RemoveEventListener(WindowEvent::MINIMIZED, this);
			window_->RemoveEventListener(WindowEvent::RESTORED, this);
			window_->RemoveEventListener(WindowEvent::RESIZE, this);
			window_->RemoveEventListener(WindowEvent::ENTER_RESIZEMOVE, this);
			window_->RemoveEventListener(WindowEvent::EXIT_RESIZEMOVE, this);
			window_->RemoveEventListener(WindowEvent::UPDATE, this);
		}
		if (renderer_)
		{
			renderer_->RemoveEventListener(RendererEvent::UPDATE, this);
			renderer_->RemoveEventListener(RendererEvent::RENDER, this);
		}
	}
	delete device;
}

void ComaDevice::ReleaseAll()
{
	if (window_) delete window_;
	if (renderer_) delete renderer_;
	delete device;
}

bool ComaDevice::SetWindow(ComaWindow* window)
{
	if (initialized_)
		return false;
	this->window_ = window;
	return true;
}
bool ComaDevice::SetRenderer(ComaRenderer* renderer)
{
	if (initialized_)
		return false;
	this->renderer_ = renderer;
	return true;
}
bool ComaDevice::SetWindowRenderer(ComaWindow* window, ComaRenderer* renderer)
{
	if (!SetWindow(window))
		return false;
	if (!SetRenderer(renderer))
		return false;
	return true;
}

bool ComaDevice::InitDevice()
{
	if (initialized_)
		return false;
	if (!InitWindow())
		return false;
	if (!InitRenderer())
		return false;
	if (!InitManagers())
		return false;
	if (!InitOthers())
		return false;
	initialized_ = true;
	return true;
}
bool ComaDevice::InitDevice(HINSTANCE hInstance)
{
	if (initialized_)
		return false;
	if (!InitWindow(hInstance))
		return false;
	if (!InitRenderer())
		return false;
	if (!InitManagers())
		return false;
	if (!InitOthers())
		return false;
	initialized_ = true;
	return true;
}

bool ComaDevice::Run()
{
	if (running_ || !initialized_ || !window_ || !renderer_)
		return false;
	running_ = true;

	if (!renderer_->isRunning())
		renderer_->run();

	if (!window_->isRunning())
		window_->run();

	return true;
}

bool ComaDevice::InitWindow()
{
	if (!window_)
		return false;
	if (!window_->isCreated())
		if (!window_->createWindow())
			return false;

	window_->SetEventListener(WindowEvent::DESTROY, BIND(ComaDevice::WindowDestroyListener), this);
	window_->SetEventListener(WindowEvent::MINIMIZED, BIND(ComaDevice::WindowMinimizeListener), this);
	window_->SetEventListener(WindowEvent::RESTORED, BIND(ComaDevice::WindowRestoreListener), this);
	window_->SetEventListener(WindowEvent::RESIZE, BIND(ComaDevice::WindowResizeListener), this);
	window_->SetEventListener(WindowEvent::ENTER_RESIZEMOVE, BIND(ComaDevice::WindowEnterResizeMoveListener), this);
	window_->SetEventListener(WindowEvent::EXIT_RESIZEMOVE, BIND(ComaDevice::WindowExitResizeMoveListener), this);
	window_->SetEventListener(WindowEvent::UPDATE, BIND(ComaDevice::WindowUpdateListener), this);
	return true;
}
bool ComaDevice::InitWindow(HINSTANCE hInstance)
{
	if (window_)
		return InitWindow();

	window_ = new ComaWindow(hInstance);
	return InitWindow();
}

bool ComaDevice::InitRenderer()
{
	if (!window_)
		return false;

	if (!renderer_)
		renderer_ = new ComaRenderer();

	if (!renderer_->isInitialized())
		if (!renderer_->initRenderer(window_->getWindow()))
			return false;

	renderer_->SetEventListener(RendererEvent::UPDATE, BIND(ComaDevice::RendererUpdateListener), this);
	renderer_->SetEventListener(RendererEvent::RENDER, BIND(ComaDevice::RendererRenderListener), this);
		
	return true;
}
bool ComaDevice::InitManagers()
{
	resourceManager_ = new ResourceManager();
	sceneManager_ = new SceneManager();
	inputManager_ = window_->getInputManager();
	physicsManager_ = new PhysicsManager();
	physicsManager_->initBox2D(Vector{ 0.0f, 10.0f });
	return true;
}
bool ComaDevice::InitOthers()
{
	Bitmap::setRenderer(renderer_);
	return true;
}

void ComaDevice::WindowDestroyListener(const Event* event)
{
	
}
void ComaDevice::WindowMinimizeListener(const Event* event)
{
	renderer_->pause();
}
void ComaDevice::WindowRestoreListener(const Event* event)
{
	renderer_->run();
}
void ComaDevice::WindowEnterResizeMoveListener(const Event* event)
{
	renderer_->pause();
}
void ComaDevice::WindowExitResizeMoveListener(const Event* event)
{
	renderer_->resetSize();
	renderer_->run();
}
void ComaDevice::WindowUpdateListener(const Event* event)
{
	renderer_->update();
}
void ComaDevice::WindowResizeListener(const Event* event)
{
	if (!window_->isResizing() && !window_->isMinimized())
		renderer_->resetSize();
}

void ComaDevice::RendererUpdateListener(const Event* event)
{
	RendererEvent* rEvent = (RendererEvent*)event;

	inputManager_->updateGamepad(rEvent->DeltaTime());

	physicsManager_->nextStep(rEvent->DeltaTime());
	if (!sceneManager_ || !sceneManager_->getScene())
		return;
	sceneManager_->getScene()->update(rEvent->DeltaTime());
}
void ComaDevice::RendererRenderListener(const Event* event)
{
	RendererEvent* rEvent = (RendererEvent*)event;

	if (!sceneManager_ || !sceneManager_->getScene())
		return;
	sceneManager_->getScene()->render(rEvent->GetRenderTarget(), rEvent->DeltaTime());
}