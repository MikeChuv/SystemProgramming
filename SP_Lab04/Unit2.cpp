//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
bool btnPictureClicked, btnPlotClicked = false;
bool btnRandomBackgroundClicked, btnRandomRectClicked = false;
bool btnCircleClicked = false;

TRect randomColorRect(200, 200, 800, 400);
TRect circleRect(200, 200, 300, 300);
TRect circleRectBB(150, 150, 350, 350);


TRect btnRect;
void UpdateBtnPos(){
	MainForm -> Canvas -> Brush -> Color = clBtnFace;
	MainForm -> Canvas -> FillRect(btnRect);
	btnRect.Top = MainForm -> Height - 90;
	btnRect.Left = 200;
	btnRect.Bottom = btnRect.Top + 40;
	btnRect.Right = btnRect.Left + 160;
}

void DrawPlotButton(TColor color){
	UpdateBtnPos();
	MainForm -> Canvas -> Brush -> Color = color;
	MainForm -> Canvas -> Pen -> Color = clBlack;
	MainForm -> Canvas -> Pen -> Width = 1;
	MainForm -> Canvas -> Rectangle(btnRect);
	MainForm -> Canvas -> Font -> Name = "Tahoma";
	MainForm -> Canvas -> Font-> Color = clBtnText;
	MainForm -> Canvas -> Font -> Size = 12;
	MainForm -> Canvas -> TextOut(btnRect.Left + 10, btnRect.Top + 10, "Нарисовать график");
}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------------------------
//---------------------------------UTILS-------------------------------------

// Рисование круга по центру и радиусу
void Circle(int x, int y, int r) {
	MainForm -> Canvas -> Ellipse(x - r, y - r, x + r, y + r);
}

// Рисование эллипса по центру и двум полуосям
void SimpleEllipse(int x, int y, int r1, int r2) {
	MainForm -> Canvas -> Ellipse(x - r1, y - r2, x + r1, y + r2);
}

// Рисование треугольника
void Triangle(int x, int y, int size, TBrushStyle style){
	MainForm -> Canvas -> Brush -> Style = style;
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(20, 170, 20));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(20, 170, 20));
	TPoint points [3] = {{x, y}, {x + size / 2, y + size}, {x - size / 2, y + size}};
	MainForm -> Canvas -> Polygon(points, 2);
	MainForm -> Canvas -> Brush -> Style = bsSolid;
}

//---------------------------------------------------------------------------
// ======================= Рисование картинки =======================
//---------------------------------------------------------------------------

// Рисование облака
void Cloud(int x, int y, int scale){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(240, 240, 255));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(240, 240, 255));
	int _size = 10 * scale;
	int d1 = _size * 3;
	int d2 = _size * 2;
	MainForm -> Canvas -> Chord(x, y, x + d1, y + d2, x + d1, y + d2 / 2, x, y + d2 / 2);
	int dx = _size;
	MainForm -> Canvas -> Chord(x, y + d2 / 4,	   		x + dx, y + 3 * d2 / 4, 	x, y + d2 / 2, x + d1, y + d2 / 2);
	MainForm -> Canvas -> Chord(x + dx, y + d2 / 4, 	x + 2 * dx,	y + 3 * d2 / 4, x, y + d2 / 2, x + d1, y + d2 / 2);
	MainForm -> Canvas -> Chord(x + 2 * dx, y + d2 / 4,	x + 3 * dx,	y + 3 * d2 / 4, x, y + d2 / 2, x + d1, y + d2 / 2);
}

// Рисование неба
void Sky(){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(80, 80, 240));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(80, 80, 240));
	int sky_width = MainForm -> Width - 20;
	int sky_height = MainForm -> Height * 0.6;
	MainForm -> Canvas -> Rectangle(5, 5, sky_width, sky_height);
	Cloud(sky_width * 0.2, sky_height * 0.1, 3);
	Cloud(sky_width * 0.4, sky_height * 0.2, 4);
	Cloud(sky_width * 0.6, sky_height * 0.1, 3);
}

// Рисование земли
void Ground(){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(50, 50, 50));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(50, 50, 50));
	int ground_width = MainForm -> Width - 20;
	int ground_height_top = MainForm -> Height * 0.6;
	int ground_height_bottom = MainForm -> Height - 100;
	MainForm -> Canvas -> Rectangle(5, ground_height_top, ground_width, ground_height_bottom);
}

// === ### Рисание снеговика ### ===
// Рисование глаз
void Eyes(int x, int y, int _size){
    MainForm -> Canvas -> Brush -> Color = TColor(RGB(20, 20, 20));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(20, 20, 20));
	int eye_size = _size / 10;
	Circle(x - _size / 2, y - _size / 2, eye_size);
	Circle(x + _size / 2, y - _size / 2, eye_size);
}

// Рисование носа
void Nose(int x, int y, int _size){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(200, 170, 20));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(200, 170, 20));
	TPoint points [3] = {{x, y - _size / 5}, {x + _size / 2, y - _size / 10}, {x, y}};
	MainForm -> Canvas -> Polygon(points, 2);
}

// Рисование рта
void Mouth(int x, int y, int _size){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(20, 20, 20));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(20, 20, 20));
	int offset = _size / 4;
	MainForm -> Canvas -> Chord(x - offset, y + offset, x + offset, y + offset + _size / 5, x - offset, y + offset + _size / 10, x + offset, y + offset + _size / 10);

}

// Рисование головы
void DrawHead(int x, int y, int _size){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(200, 200, 200));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(200, 200, 200));
	SimpleEllipse(x, y, _size, _size);
	Eyes(x, y, _size);
	Nose(x, y, _size);
	Mouth(x, y, _size);
}

// Рисование рук
void DrawArms(int x, int y, int _size, int y_body_center){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(0, 0, 0));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(0, 0, 0));
	MainForm -> Canvas -> Pen -> Width = 5;
	MainForm -> Canvas -> MoveTo(x - _size, y + _size);
	MainForm -> Canvas -> LineTo(x - _size * 2, y_body_center);
	MainForm -> Canvas -> MoveTo(x + _size, y + _size);
	MainForm -> Canvas -> LineTo(x + _size * 2, y_body_center);
}

// Рисование тела (средней части)
void DrawBody(int x, int y, int _size){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(200, 200, 200));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(200, 200, 200));
	int r1 = _size * 1.25;
	int y_body_center = y + _size * 0.6 + r1;
	SimpleEllipse(x, y_body_center, r1 * 1.1, r1);
	DrawArms(x, y, _size, y_body_center);
}

// Рисование тела (нижней части)
void DrawBottom(int x, int y, int _size){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(200, 200, 200));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(200, 200, 200));
	int r1 = _size * 1.7;
	int y_bottom_center = y + _size * 4;
	SimpleEllipse(x, y_bottom_center, r1 * 1.1, r1);
}

// Весь снеговик
void SnowMan(){
	int size = MainForm -> Height / 17;
	int x_start = MainForm -> Width / 5;
	int y_start = MainForm -> Height / 2;
	DrawHead(x_start, y_start, size);
	DrawBody(x_start, y_start, size);
	DrawBottom(x_start, y_start, size);
}


// Рисование елочки
void FirTree(int x, int y, int size, TBrushStyle style){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(100, 60, 30));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(100, 60, 30));
	MainForm -> Canvas -> Rectangle(x - size / 4, y + size * 3, x + size / 4, y + size * 4.5);
	Triangle(x, y, size, style);
	Triangle(x, y + size * 0.7, size * 1.5, style);
	Triangle(x, y + size * 1.7, size * 2, style);
}

// Вся картинка
void DrawPicture(){
	Sky();
	Ground();
	SnowMan();
	int size = MainForm -> Height / 17;
	int x_start = MainForm -> Width * 0.7;
	int y_start = MainForm -> Height * 0.35;
	FirTree(x_start, y_start, size, bsSolid);
	size = MainForm -> Height / 12;
	x_start = MainForm -> Width * 0.5;
	y_start = MainForm -> Height * 0.37;
	FirTree(x_start, y_start, size, bsDiagCross);
}
//---------------------------------------------------------------------------
// ================== Рисование графика функции ==================
//---------------------------------------------------------------------------
void DrawPlot(){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(0, 0, 0));
	MainForm -> Canvas -> Pen -> Color = TColor(RGB(0, 0, 0));
	MainForm -> Canvas -> Pen -> Width = 5;
	int yoff = MainForm -> Height / 2;
	float amp = MainForm -> Height / 5;
	float freq = 0.02;
	int h = 3;
	for(int i = 0 ; i < MainForm -> Width; i+=h){
		int xFrom = i;
		int xTo = i + h;
		MainForm -> Canvas -> MoveTo(xFrom, - amp * sin(freq * xFrom) + yoff);
		MainForm -> Canvas -> LineTo(xTo, 	- amp * sin(freq * xTo) + yoff);
	}
	MainForm -> Canvas -> Pen -> Width = 1;
}


//---------------------------------------------------------------------------
// ====== Закрашивание всей области, рисование прямоугольника и круга =======
//---------------------------------------------------------------------------
void RandomBackground() {
	MainForm -> Canvas -> Brush -> Style = bsSolid;
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(random(255), random(255), random(255)));
	TRect rect(0, 0, MainForm -> Width, MainForm -> Height);
	MainForm -> Canvas -> FillRect(rect);
}
//---------------------------------------------------------------------------
void RandomColorRect(){
	MainForm -> Canvas -> Brush -> Color = TColor(RGB(random(255), random(255), random(255)));
	MainForm -> Canvas -> Brush -> Style = bsSolid;
	MainForm -> Canvas -> Rectangle(randomColorRect);
}
//---------------------------------------------------------------------------
void DrawCircle() {
	MainForm -> Canvas -> Brush -> Color = clLime;
	MainForm -> Canvas -> Ellipse(circleRect);
}


//---------------------------------------------------------------------------
// ========================== Обработчики событий ==========================
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnPictureClick(TObject *Sender)
{
	btnPictureClicked = true;
	btnCircleClicked = btnPlotClicked = false;
	btnRandomBackgroundClicked = btnRandomRectClicked = false;
	MainForm -> Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormPaint(TObject *Sender)
{
	if (btnPictureClicked){
		DrawPicture();
	}
	else if (btnPlotClicked){
		DrawPlot();
	}
	else if(btnRandomBackgroundClicked){
		RandomBackground();
	}
	else if(btnRandomRectClicked){
		RandomColorRect();
	}
	else if(btnCircleClicked){
		DrawCircle();
	}
	DrawPlotButton(clBtnFace);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{
	MainForm -> Refresh();
	DrawPlotButton(clBtnFace);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if((X > btnRect.Left && X < btnRect.Right) && (Y > btnRect.Top && Y < btnRect.Bottom) && Button == mbLeft){
		DrawPlotButton(clBtnShadow);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if((X > btnRect.Left && X < btnRect.Right) && (Y > btnRect.Top && Y < btnRect.Bottom) && Button == mbLeft){
		btnPlotClicked = true;
		btnPictureClicked = btnCircleClicked = false;
		btnRandomBackgroundClicked = btnRandomRectClicked = false;
		MainForm -> Refresh();
	}

	int r = (circleRect.Right - circleRect.Left) / 2;
	int xrel = X - (circleRect.Right + circleRect.Left) / 2;
	int yrel = Y - (circleRect.Bottom + circleRect.Top) / 2;

	if ( (xrel * xrel + yrel * yrel) < r * r) {
		btnCircleClicked = false;
		::InvalidateRect(MainForm->Handle, &circleRect, true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnRandomBackgroundClick(TObject *Sender)
{
	btnPictureClicked = btnPlotClicked = btnRandomRectClicked = btnCircleClicked = false;
	btnRandomBackgroundClicked = true;
	::InvalidateRect(MainForm->Handle, 0, false);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnRandomRectClick(TObject *Sender)
{
	btnPictureClicked = btnPlotClicked = btnRandomBackgroundClicked = btnCircleClicked = false;
	btnRandomRectClicked = true;
	::InvalidateRect(MainForm->Handle, &randomColorRect, false);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnCircleClick(TObject *Sender)
{
	btnPictureClicked = btnPlotClicked = false;
	btnRandomBackgroundClicked = btnRandomRectClicked = false;
	btnCircleClicked = true;
	::InvalidateRect(MainForm->Handle, &circleRect, false);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if (Shift.Contains(ssLeft) && btnCircleClicked) {
		::InvalidateRect(MainForm->Handle, &circleRectBB, true);
		int r = (circleRect.Right - circleRect.Left) / 2;
		circleRect = TRect(X-r, Y-r, X+r, Y+r);
		r = (circleRectBB.Right - circleRectBB.Left) / 2;
		circleRectBB = TRect(X-r, Y-r, X+r, Y+r);
	}
}
//---------------------------------------------------------------------------

