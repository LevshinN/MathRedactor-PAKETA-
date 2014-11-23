﻿/*
author: Timur Khusaenov
class: CWinMain
description:
	Класс реализует интерфейс, применяемый в приложении WinPlotter.
	Для корректной работы должен содержвать делегата CWinPlotter, который реализует отрисовку графика
*/

#pragma once

#include "Windows.h"
#include "CFormula.h"
#include <vector>
#include <map>

#include "CWinPlotter.h"
#include "MainWindow.h"


class CWinMain
{
public:
	CWinMain() : epsilon( 1. ) { maxParam[0] = maxParam[1] = 10.; minParam[0] = minParam[1] = -10.; }
	static bool registerClass( HINSTANCE hInstance );	// зарегистрировать класс окна
	HWND create( HINSTANCE hInctance );					// создать экземпляр окна
	void show( int cmdShow );							// показать окно
	HWND createButton( LPCWSTR title, int X, int Y, HWND parent, HMENU id );	// создать кнопку и  проинициализировать defButtonPorc
	void setButtonPos( HWND hWnd, int X, int Y );		// изменить позицию кнопки
	double MouseWheelSens = 0.04;						// чувствительность колесика 
	//int getButtonSize() { return buttonSize; }		// возможно добавиться функция смены размера кнопок

protected:
	void OnDestroy();									// разрушение окна
	void OnCreate( HWND hWnd );							// действия при создании окна
	void OnDialogCreate( HWND hWnd );					// действия при создании окна
	LRESULT OnCommand( WPARAM wParam, LPARAM lParam );	// обработка WM_COMMAND
	LRESULT OnFormCommand( WPARAM wParam, LPARAM lParam );	// обработка комманд в окне диалога
	void OnFormOk();									// обработчик изменения параметров принажатии Ок
	void ShowFormulaForm();								// отобразить диалог ввода формулы
	void ShowParamForm();								// отобразить диалог редактирование параметров
	void ResizeChildrens();								// смена положения и размеров дочерних окон
	void Move();										// перемещение по графику (вызов соответсвующих функций у WinPlotter)
	void IdentifyCommand( HWND hWnd );					// идентификация какая кнопка была нажата и последующие действия в зависимости от этого
	void TakeFormula();									// принять формулу
	LRESULT OnKeyDown( WPARAM wParam, LPARAM lParam );	// обработка нажатия клавиш (стрелки для перемещения по графику)
	LRESULT OnKeyUp( WPARAM wParam, LPARAM lParam );	// обработка отжатия клавиш

private:
	enum TDirection { D_None, D_Top, D_Bot, D_Right, D_Left };
	enum TZoom { Z_None, Z_Minus, Z_Plus };

	POINT curPos, oldCurPos;							// положение курсора
	bool curMove = false;								// индикатор движения
	TDirection moveDirection = D_None;					// направление движения
	TDirection rotateDirection = D_None;				// направление поворота
	TZoom zoom = Z_None;								// зум
	static WNDPROC defButtonProc;						// дефолтный обработчик кнопок-контролов
	static WNDPROC defMouseProc;						// дефолтный обработчик откна отрисовки
	HWND handle;										// хэндл окна
	HWND hPlotter;										// хэндл плоттера
	HWND hRedactor;										// хэндл редактора
	HWND hFormulaForm;									// хэндл диалога
	UINT_PTR timer;										// таймер
	int buttonSize = 25;								// рзмер кнопки

	CMainWindow winRedactor;							// дочернее окно - редактор
	CWinPlotter winPlotter;								// дочернее окно, отвечающее за прорисовку

	// хэндлы кнопок
	HWND hButtonMoveTop, hButtonMoveBot, hButtonMoveLeft, hButtonMoveRight;
	HWND hButtonRotateUp, hButtonRotateDown, hButtonRotateLeft, hButtonRotateRight;
	HWND hButtonZoomPlus, hButtonZoomMinus;

	// оброботчики сообщений
	static LRESULT __stdcall windowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static LRESULT __stdcall buttonProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static LRESULT __stdcall mouseProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static BOOL __stdcall formulaDialogProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );

	// temporary params for plotter
	double maxParam[2], minParam[2];
	double epsilon;

	CFormula formula;
	void buildPlot();
	std::map< char, std::pair< double, double > > args;
	std::vector<char> vars;
};