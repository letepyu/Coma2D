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
* filename	DisplayObject.h
* fileinfo	ȭ�� ǥ�� ��ü Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "EventDispatcher.h"
#include <math.h>
#include <d2d1.h>

COMA_NS_BEGIN

class DisplayObjectContainer;
class Camera;

class DisplayObject :
	public EventDispatcher
{
protected:
	DisplayObject();
private:
	static DisplayObjectContainer* world;
public:
	virtual ~DisplayObject();

	virtual void update(){}
	virtual void render(ID2D1HwndRenderTarget* renderTarget){}
	
//Getter
	Camera* getCamera()		{ return camera; }
	DisplayObjectContainer* getWorld(){ return world; }
	Point getPosition()		{ return position; }
	float getX()			{ return position.x; }
	float getY()			{ return position.y; }
	Size getLocalSize()		{ return localSize; }

	Size getSize()			{ return Size{ localSize.width * scale.width, localSize.height * scale.height }; }
	float getWidth()		{ return localSize.width * scale.width; }
	float getHeight()		{ return localSize.height * scale.height; }

	Size getScale()			{ return scale; }
	float getScaleX()		{ return scale.width; }
	float getScaleY()		{ return scale.height; }

	float getRotation()		{ return rotation; }
	float getRotationRad()	{ return DEGREE_TO_RADIAN(rotation); }

	Point getAnchorPoint()	{ return anchorPoint; }

	Matrix3x2 getScaleMatrix()			{ return Matrix3x2::Scale(scale, anchorPoint); }				//ȭ�� ���� ����� ��ȯ�մϴ�.
	Matrix3x2 getTranslationMatrix()	{ return Matrix3x2::Translation(position.x, position.y); }		//�̵� ����� ��ȯ�մϴ�.
	Matrix3x2 getRotationMatrix()		{ return Matrix3x2::Rotation(rotation, anchorPoint); }			//ȸ�� ����� ��ȯ�մϴ�.
	Matrix3x2 getCameraMatrix();																		//ī�޶��� ��ȯ ����� ��ȯ�մϴ�.
	Matrix3x2 getMatrix()				{ return getScaleMatrix() * getTranslationMatrix() * getRotationMatrix(); }	//�ش� Object�� ��ȯ ����� ��ȯ�մϴ�.
	Matrix3x2 getWorldMatrix();
	Matrix3x2 getScreenMatrix();	//�ش� ������Ʈ�� ������ ���� ������Ʈ�� ����� ���� ��ȯ�մϴ�.                                                                      ���)

	DisplayObjectContainer* getParentObject()	{ return parentObject; }
	void _registerParent(DisplayObjectContainer* parent) { parentObject = parent; }
	void _unregisterParent() { parentObject = nullptr; }

	bool isVisible(){ return visible; }
	float getAlpha(){ return alpha; }

//Setter
	void setCamera(Camera* camera);
	void setWorld(DisplayObjectContainer* world);
	void unsetCamera();
	void setPosition(float x, float y)	{ setPosition(Point{x, y}); }
	void setPosition(Point position)	{ this->position = position; }
	void setX(float value)				{ this->position.x = value; }
	void setY(float value)				{ this->position.y = value; }
	void translate(Point vector)		{ this->position.x += vector.x; this->position.y += vector.y; }
	void translate(float x, float y)	{ translate(D2D1::Point2F(x, y)); }
	void translateX(float value)		{ this->position.x += value; }
	void translateY(float value)		{ this->position.y += value; }

	void setSize(float width, float height){ setSize(Size{ width, height }); }
	void setSize(Size size)		{ if (localSize.width == 0 || localSize.height == 0)return; scale = Size{ size.width / localSize.width, size.height / localSize.height }; }
	void setWidth(float value)	{ if (localSize.width == 0)return; scale.width = value / scale.width; }
	void setHeight(float value)	{ if (localSize.height == 0)return; scale.height = value / scale.height; }
	
	void setScale(float scaleX, float scaleY){ setScale(Size{ scaleX, scaleY });}
	void setScale(Size scale)		{ this->scale = scale; }
	void setScaleX(float value)		{ this->scale.width = value; }
	void setScaleY(float value)		{ this->scale.height = value; }

	void setRotation(float rotation){ this->rotation = rotation; }
	void setRotationRad(float rotation){ this->rotation = RADIAN_TO_DEGREE(rotation); }
	
	void setAnchorPoint(float x, float y){ setAnchorPoint(Point{ x, y }); }
	void setAnchorPoint(Point point){ anchorPoint = point; }

	void setAlpha(float alpha)
	{
		this->alpha = alpha;
		if (alpha < 0) this->alpha = 0;
		else if (alpha > 1) this->alpha = 1;
	}
	void setVisible(bool visibility){ visible = visibility; }


	Point worldToLocal(Point point){ return getWorldMatrix().TransformPoint(point); }
	Point localToWorld(Point point){ 
		Matrix3x2 invertWorldMatrix = getWorldMatrix();
		invertWorldMatrix.Invert();
		return invertWorldMatrix.TransformPoint(point);
	}
	Point screenToLocal(Point point){ return getScreenMatrix().TransformPoint(point); }
	Point localToScreen(Point point){
		Matrix3x2 invertScreenMatrix = getScreenMatrix();
		invertScreenMatrix.Invert();
		return invertScreenMatrix.TransformPoint(point);
	}
	
protected:
	void setLocalSize(Size size) { localSize = size; }
	void setLocalSize(float width, float height) { setLocalSize(Size{ width, height }); }

private:
	DisplayObjectContainer* parentObject;
	Camera* camera;
	Point position;
	Size scale;
	float rotation;
	Point anchorPoint;

	bool visible;
	float alpha;

	Size localSize;
};

COMA_END