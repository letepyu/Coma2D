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
	void setLocalSize(Size size) { localSize = size;  _transformApply(); }
	void setLocalSize(float width, float height) { setLocalSize(Size{ width, height }); }
	void setLocalPosition(Point position){ localPoint = position; }
	void setLocalPosition(float x, float y){ setLocalPosition(Point{ x, y }); }

	static ID2D1SolidColorBrush* brush;
private:
	static DisplayObjectContainer* world;

	DisplayObjectContainer* parentObject;
	Camera* camera;

	Point position;
	Size scale;
	float rotation;
	Point anchorPoint;
	bool visible;
	float alpha;
	Size localSize;
	Point localPoint;

	bool outlineDrawing;

public:
	virtual ~DisplayObject();

	virtual void update(double deltaTime); // ������ ������ ȣ��
	virtual void render(ID2D1HwndRenderTarget* renderTarget, double deltaTime); // ������
	
//Getter
	static DisplayObjectContainer* getWorld(){ return DisplayObject::world; }
	Camera* getCamera()		{ return camera; }

	Point	getPosition()	{ return position; }
	float	getX()			{ return position.x; }
	float	getY()			{ return position.y; }
	Size	getSize()		{ return Size{ localSize.width * scale.width, localSize.height * scale.height }; }
	float	getWidth()		{ return localSize.width * scale.width; }
	float	getHeight()		{ return localSize.height * scale.height; }
	Size	getLocalSize()	{ return localSize; }
	Point	getLocalPosition(){ return localPoint; }
	Size	getScale()		{ return scale; }
	float	getScaleX()		{ return scale.width; }
	float	getScaleY()		{ return scale.height; }
	float	getRotation()	{ return rotation; }
	float	getRotationRad(){ return DEGREE_TO_RADIAN(rotation); }
	Point	getAnchorPoint(){ return anchorPoint; }
	bool	isVisible()		{ return visible; }
	float	getAlpha()		{ return alpha; }
	float	getScreenAlpha();
	bool	isOutlineDrawing(){ return outlineDrawing; }

	Matrix3x2 getScaleMatrix()			{ return Matrix3x2::Scale(scale, anchorPoint); }				//ȭ�� ���� ����� ��ȯ�Ѵ�.
	Matrix3x2 getTranslationMatrix()	{ return Matrix3x2::Translation(position.x, position.y); }		//�̵� ����� ��ȯ�Ѵ�.
	Matrix3x2 getRotationMatrix()		{ return Matrix3x2::Rotation(rotation, anchorPoint); }			//ȸ�� ����� ��ȯ�Ѵ�.
	Matrix3x2 getCameraMatrix();																		//ī�޶��� ��ȯ ����� ��ȯ�Ѵ�.
	Matrix3x2 getMatrix()				{ return getScaleMatrix()* getRotationMatrix() *getTranslationMatrix(); }	//�ش� Object�� ��ȯ ����� ��ȯ�Ѵ�.
	Matrix3x2 getWorldMatrix();		//���� ������Ʈ �������� ��� ��ȯ�� ��ȯ�Ѵ�. ����: ���忡 ���Ե��� ���� ��� ��Ȯ�� ����� ������ ���� �� ����.
	Matrix3x2 getScreenMatrix();	//�ش� ������Ʈ�� ������ ���� ������Ʈ�� ����� ���� ��ȯ�Ѵ�. (���)

	DisplayObjectContainer* getParent()						{ return parentObject; }	//�θ� ��ü�� ��ȯ�Ѵ�.
	virtual bool _registerParent(DisplayObjectContainer* parent);	//�θ� ��ü�� ����Ѵ�. (�ܺ�ȣ�� ����)
	virtual bool _unregisterParent();								//�θ� ��ü�� �����Ѵ�. (�ܺ�ȣ�� ����)

	

//Setter
	static void _setWorld(DisplayObjectContainer* world);
	void setCamera(Camera* camera);	//ī�޶� ����
	void unsetCamera();				//ī�޶� ����

	void setPosition(float x, float y)		{ setPosition(Point{ x, y }); }
	void setPosition(Point position)		{ this->position = position;	_transformApply(); }
	void setX(float value)					{ this->position.x = value;		_transformApply(); }
	void setY(float value)					{ this->position.y = value;		_transformApply(); }
	void translate(Point vector)			{ this->position.x += vector.x; this->position.y += vector.y;  _transformApply(); }
	void translate(float x, float y)		{ translate(D2D1::Point2F(x, y)); }
	void translateX(float value)			{ this->position.x += value;	_transformApply(); }
	void translateY(float value)			{ this->position.y += value;	_transformApply(); }
	void setSize(float width, float height)	{ setSize(Size{ width, height }); }
	void setSize(Size size)					{ if (localSize.width == 0 || localSize.height == 0)return; scale = Size{ size.width / localSize.width, size.height / localSize.height }; _transformApply(); }
	void setWidth(float value)				{ if (localSize.width == 0)return; scale.width = value / scale.width;  _transformApply(); }
	void setHeight(float value)				{ if (localSize.height == 0)return; scale.height = value / scale.height; _transformApply(); }
	void setScale(float scaleX, float scaleY){ setScale(Size{ scaleX, scaleY }); }
	void setScale(Size scale)				{ this->scale = scale;			_transformApply(); }
	void setScaleX(float value)				{ this->scale.width = value;	_transformApply(); }
	void setScaleY(float value)				{ this->scale.height = value;	_transformApply(); }
	void setRotation(float rotation)		{ this->rotation = rotation;	_transformApply(); }
	void setRotationRad(float rotation)		{ this->rotation = RADIAN_TO_DEGREE(rotation); _transformApply(); }
	void setAnchorPoint(float x, float y)	{ setAnchorPoint(Point{ x, y }); }
	void setAnchorPoint(Point point)		{ anchorPoint = point;			_transformApply(); }
	void setAlpha(float alpha)				{ this->alpha = alpha; if (alpha < 0) this->alpha = 0; else if (alpha > 1) this->alpha = 1;}
	void setVisible(bool visibility)		{ visible = visibility; }
	virtual void setDrawOutline(bool draw)			{ outlineDrawing = draw; }
//World��ǥ�踦 �������� ��ġ�� ��ȯ�Ѵ�.
	Point worldToLocal(Point point){
		Matrix3x2 invertWorldMatrix = getWorldMatrix();
		invertWorldMatrix.Invert();
		return invertWorldMatrix.TransformPoint(point);
	}
	Point localToWorld(Point point){ 
		return getWorldMatrix().TransformPoint(point);
	}
//������ ȭ���� ��ǥ�踦 �������� ��ġ�� ��ȯ�Ѵ�.
	Point screenToLocal(Point point){
		Matrix3x2 invertScreenMatrix = getScreenMatrix();
		invertScreenMatrix.Invert();
		return invertScreenMatrix.TransformPoint(point);
	}
	Point localToScreen(Point point){
		return getScreenMatrix().TransformPoint(point);
	}

	virtual void _transformApply();	//��ȯ�� �θ� ��ü���� �˸� �� ȣ���Ѵ�.(�ܺ�ȣ�� ����)
protected:
	virtual void drawOutline(ID2D1HwndRenderTarget* renderTarget);
};

COMA_END