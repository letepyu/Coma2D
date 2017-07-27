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
	void SetLocalSize(const Size& size);
	void SetLocalSize(float width, float height);
	void SetLocalPosition(const Point& position);
	void SetLocalPosition(float x, float y);

	static ID2D1SolidColorBrush* brush;
private:
	static DisplayObjectContainer* world;

	DisplayObjectContainer* parentObject_;
	Camera* camera_;

	Point position_;
	Size scale_;
	float rotation_;
	Point anchorPoint_;
	bool visible_;
	float alpha_;
	Size localSize_;
	Point localPoint_;
	bool drawOutline_;

public:
	virtual ~DisplayObject();

	virtual void Update(double deltaTime); // ������ ������ ȣ��
	virtual void Render(ID2D1HwndRenderTarget* renderTarget, double deltaTime); // ������

//Getter
	static DisplayObjectContainer* GetWorld();
	Camera* GetCamera() const;

	Point GetPosition() const;
	float GetX() const;
	float GetY() const;
	Size GetSize() const;
	float GetWidth() const;
	float GetHeight() const;
	const Size& GetLocalSize() const;
	const Point& GetLocalPosition() const;
	const Size& GetScale() const;
	float GetScaleX() const;
	float GetScaleY() const;
	float GetRotation() const;
	float GetRotationRad() const;
	const Point& GetAnchorPoint() const;
	bool IsVisible() const;
	float GetAlpha() const;
	float GetScreenAlpha() const;
	bool IsOutlineDrawing() const;

	Matrix3x2 GetScaleMatrix() const; //ȭ�� ���� ����� ��ȯ�Ѵ�.
	Matrix3x2 GetTranslationMatrix() const; //�̵� ����� ��ȯ�Ѵ�.
	Matrix3x2 GetRotationMatrix() const; //ȸ�� ����� ��ȯ�Ѵ�.
	Matrix3x2 GetCameraMatrix() const; //ī�޶��� ��ȯ ����� ��ȯ�Ѵ�.
	Matrix3x2 GetMatrix() const; //�ش� Object�� ��ȯ ����� ��ȯ�Ѵ�.
	Matrix3x2 GetWorldMatrix() const; //���� ������Ʈ �������� ��� ��ȯ�� ��ȯ�Ѵ�. ����: ���忡 ���Ե��� ���� ��� ��Ȯ�� ����� ������ ���� �� ����.
	Matrix3x2 GetScreenMatrix() const; //�ش� ������Ʈ�� ������ ���� ������Ʈ�� ����� ���� ��ȯ�Ѵ�. (���)

	DisplayObjectContainer* GetParent() const; //�θ� ��ü�� ��ȯ�Ѵ�.
	virtual bool _RegisterParent(DisplayObjectContainer* parent); //�θ� ��ü�� ����Ѵ�. (�ܺ�ȣ�� ����)
	virtual bool _UnregisterParent(); //�θ� ��ü�� �����Ѵ�. (�ܺ�ȣ�� ����)

//Setter
	static void _SetWorld(DisplayObjectContainer* world);
	void SetCamera(Camera* camera);	//ī�޶� ����
	void UnsetCamera();	//ī�޶� ����

	void SetPosition(float x, float y);
	void SetPosition(Point position);
	void SetX(float value);
	void SetY(float value);
	void Translate(Point vector);
	void Translate(float x, float y);
	void TranslateX(float value);
	void TranslateY(float value);
	void SetSize(float width, float height);
	void SetSize(Size size);
	void SetWidth(float value);
	void SetHeight(float value);
	void SetScale(float scaleX, float scaleY);
	void SetScale(Size scale);
	void SetScaleX(float value);
	void SetScaleY(float value);
	void SetRotation(float rotation);
	void SetRotationRad(float rotation);
	void SetAnchorPoint(float x, float y);
	void SetAnchorPoint(Point point);
	void SetAlpha(float alpha);
	void SetVisible(bool visibility);
	virtual void SetDrawOutline(bool draw);

	//World��ǥ�踦 �������� ��ġ�� ��ȯ�Ѵ�.
	Point WorldToLocal(Point point) const;
	Point LocalToWorld(Point point) const;
	//������ ȭ���� ��ǥ�踦 �������� ��ġ�� ��ȯ�Ѵ�.
	Point ScreenToLocal(Point point) const;
	Point LocalToScreen(Point point) const;

	virtual void _TransformApply();	//��ȯ�� �θ� ��ü���� �˸� �� ȣ���Ѵ�.(�ܺ�ȣ�� ����)

protected:
	virtual void DrawOutline(ID2D1HwndRenderTarget* renderTarget);
};

COMA_END