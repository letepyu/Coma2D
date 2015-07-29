/*
* The MIT License (MIT)
*
* Copyright (c) 2015 Heonyang Ju
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*
* MIT ���̼��� (MIT)
*
* ���۱�(C) 2015 �����
*
* �� ������ ����, �Ʒ��� ������ ������ �� ���� ���� ����Ʈ��� �ٷ�� ����
* ����Ʈ������ ���纻�� ���õ� ����("����Ʈ����")�� ȹ���ϴ� ������� ������
* ������ ��� �ȴ�. ���� ������ ���, ����, ����, ����, ����, ����, ���� ���̼���
* �׸���/�Ǵ� ����Ʈ������ ���纻�� �Ǹſ� ���޵� ����Ʈ��� ���� �������
* �׷��� �� �� �ֵ��� �㰡�ϴ� ���ѿ� ���� ������ ���� �Ѵ�.
*
* ���� ���۱� ǥ�ÿ� �� �㰡 ǥ�ô� ��� ����Ʈ������ ���纻 �Ǵ� ����� �Ϻκп�
* ���ԵǾ�� �Ѵ�.
*
* �� ����Ʈ����� Ư���� ������ ħ�� ������ ���� �����, ���ռ��� ��������
* ���ѵǴ� ���� �ƴ� ����� �Ǵ� �������� ��� ������ �������� "�ִ� �״��"
* ���� �ȴ�. ��� ��쿡�� ������ �Ǵ� ���۱��ڴ� ����Ʈ������ ���� �Ȱ� ��
* �Ǵ� ����Ʈ������ ��� �Ǵ� �ŷ��κ��� �߻��ϴ� ���, �ҹ� ���� �Ǵ� ��Ÿ ���࿡
* ����, ��� �Ҽ�, ���� �Ǵ� �ٸ� å���� ���ؼ��� å���� ����.
*
* ������ MIT���̼��� ������ �������̸�, ��� �ؼ��� ������ �����Ѵ�.
*/

/*
* filename	Sprite.h
* fileinfo	�ִϸ��̼� ��������Ʈ Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "Sprite.h"
#include "SpriteEvent.h"

COMA_USING_NS

Sprite::Sprite(Bitmap* bitmap, Size imageSize, Size tileSize, unsigned int widthNumber, unsigned int heightNumber, int tileNumber, float frameChangeTime, bool autoReplay)
:Image(bitmap, imageSize), tileSize(tileSize), widthNumber(widthNumber), heightNumber(heightNumber), frameChangeTime(frameChangeTime), autoReplay(autoReplay), playing(true), currentFrame(1)
{
	if (tileNumber == 0)
		totalFrame = widthNumber*heightNumber;
	else
		totalFrame = tileNumber;
}


Sprite::~Sprite()
{
}
void Sprite::update(double deltaTime)
{
	if (isPlaying())
		timeCount += deltaTime;
	currentFrame = ((int)(timeCount / frameChangeTime) % totalFrame) + 1;
	if (currentFrame >= totalFrame && !autoReplay)
		stop();
	DisplayObject::update(deltaTime);

	if (tempFrame != currentFrame)
	{
		tempFrame = currentFrame;
		dispatchEvent(new SpriteEvent(SpriteEvent::ENTER_FRAME, this));
	}
}
void Sprite::render(ID2D1HwndRenderTarget* renderTarget, double deltaTime)
{
	DisplayObject::render(renderTarget, deltaTime);
	if (!isVisible())
		return;
	if (bitmap->isLoaded())
	{
		renderTarget->SetTransform(getScreenMatrix());
		D2D1_RECT_F size = { 0, 0, getLocalSize().width, getLocalSize().height };
		D2D1_RECT_F resSize = {
			((currentFrame - 1) % widthNumber)*tileSize.width,
			((currentFrame - 1) / widthNumber)*tileSize.height,
			((currentFrame - 1) % widthNumber)*tileSize.width+tileSize.width, 
			((currentFrame - 1) / widthNumber)*tileSize.height+tileSize.height };
		renderTarget->DrawBitmap(bitmap->getResource(), size, getScreenAlpha(), D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, resSize);
	}
}

void Sprite::stop()
{
	if (!isPlaying())
		return;
	playing = false;
	timeCount = frameChangeTime * (currentFrame - 1) + frameChangeTime*0.05f;
	dispatchEvent(new SpriteEvent(SpriteEvent::STOPPED, this));
}
void Sprite::play()
{
	if (isPlaying())
		return;
	playing = true;
	timeCount = frameChangeTime * (currentFrame - 1) + frameChangeTime*0.05f;
	dispatchEvent(new SpriteEvent(SpriteEvent::PLAY, this));
}
void Sprite::gotoAndStop(unsigned int frame)
{
	currentFrame = frame;
	timeCount = frameChangeTime * (frame - 1) + frameChangeTime*0.05f;
	stop();
}
void Sprite::gotoAndPlay(unsigned int frame)
{
	currentFrame = frame;
	timeCount = frameChangeTime * (frame - 1) + frameChangeTime*0.05f;
	play();
}
void Sprite::nextFrame()
{
	if (currentFrame < totalFrame)
		currentFrame++;
}
void Sprite::prevFrame()
{
	if (currentFrame > 1)
		currentFrame--;
}