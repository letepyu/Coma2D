#include "stdafx.h"
#include "RendererEvent.h"
using namespace Coma2D;

const std::string RendererEvent::UPDATE = "update";

RendererEvent::RendererEvent(std::string type, ComaRenderer* target)
	:Event(type)
{
	renderer = target;
}


RendererEvent::~RendererEvent()
{
}
