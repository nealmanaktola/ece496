#include "stdafx.h"
#include "GestureExecutor.h"
#include <iostream>
#include "Common.h"
#include <Windows.h>

void GestureExecutor::zoom(int dir)
{
	POINTER_TOUCH_INFO contact[2];
	InitializeTouchInjection(2, TOUCH_FEEDBACK_DEFAULT);
	memset(&contact[0], 0, sizeof(POINTER_TOUCH_INFO));
	memset(&contact[1], 0, sizeof(POINTER_TOUCH_INFO));

	//Check Pointer Id is taken as 0 for contact 0
	contact[0].pointerInfo.pointerType = PT_TOUCH;
	contact[0].pointerInfo.pointerId = 0;          //Id 0 for contact 0
	
	POINT t1;
	GetCursorPos(&t1);

	contact[0].pointerInfo.ptPixelLocation.y = t1.y;
	contact[0].pointerInfo.ptPixelLocation.x = t1.x;


	//Defining Touch flag and touchmask for contact 0
	contact[0].touchFlags = TOUCH_FLAG_NONE;
	contact[0].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
	contact[0].orientation = 90;
	contact[0].pressure = 32000;
	contact[0].rcContact.top = contact[0].pointerInfo.ptPixelLocation.y - 2;
	contact[0].rcContact.bottom = contact[0].pointerInfo.ptPixelLocation.y + 2;
	contact[0].rcContact.left = contact[0].pointerInfo.ptPixelLocation.x - 2;
	contact[0].rcContact.right = contact[0].pointerInfo.ptPixelLocation.x + 2;

	//Check Pointer Id is taken as 1 for contact 1
	contact[1].pointerInfo.pointerType = PT_TOUCH;
	contact[1].pointerInfo.pointerId = 1;          //Id 0 for contact 1
	contact[1].pointerInfo.ptPixelLocation.y = t1.y;
	contact[1].pointerInfo.ptPixelLocation.x = t1.x - 120;
	//Defining Touch flag and touchmask for contact 1
	contact[1].touchFlags = TOUCH_FLAG_NONE;
	contact[1].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
	contact[1].orientation = 90;
	contact[1].pressure = 32000;
	contact[1].rcContact.top = contact[1].pointerInfo.ptPixelLocation.y - 2;
	contact[1].rcContact.bottom = contact[1].pointerInfo.ptPixelLocation.y + 2;
	contact[1].rcContact.left = contact[1].pointerInfo.ptPixelLocation.x - 2;
	contact[1].rcContact.right = contact[1].pointerInfo.ptPixelLocation.x + 2;


	//Implementing two touch down for both array of contact point in one go
	contact[0].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
	contact[1].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
	InjectTouchInput(2, contact);

	//Setting both the contact point for Drag
	contact[0].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
	contact[1].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
	for (int i = 0; i<100; i++)
	{
		int x = i * dir;
		contact[0].pointerInfo.ptPixelLocation.x = t1.x + x;//Zooming in by dragging apart both contact points w.r.t each other
		contact[1].pointerInfo.ptPixelLocation.x = (t1.x - 220) - x;
		InjectTouchInput(2, contact);
		Sleep(1);
		
	}

	contact[0].pointerInfo.pointerFlags = POINTER_FLAG_UP;
	contact[1].pointerInfo.pointerFlags = POINTER_FLAG_UP;
	InjectTouchInput(2, contact);
}
void GestureExecutor::swipeLeftRight(int dir)
{
	POINTER_TOUCH_INFO contact;

	InitializeTouchInjection(10, TOUCH_FEEDBACK_NONE);

	memset(&contact, 0, sizeof(POINTER_TOUCH_INFO));
	contact.pointerInfo.pointerType = PT_TOUCH; //we're sending touch input
	contact.pointerInfo.pointerId = 0;          //contact 0
	contact.touchFlags = TOUCH_FLAG_NONE;
	contact.touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
	contact.orientation = 90;
	contact.pressure = 32000;

	contact.pointerInfo.ptPixelLocation.x = 910;
	contact.pointerInfo.ptPixelLocation.y = 600;

	//
	// set the contact area depending on thickness
	//
	contact.rcContact.top = contact.pointerInfo.ptPixelLocation.y - 2;
	contact.rcContact.bottom = contact.pointerInfo.ptPixelLocation.y + 2;
	contact.rcContact.left = contact.pointerInfo.ptPixelLocation.x - 2;
	contact.rcContact.right = contact.pointerInfo.ptPixelLocation.x + 2;

	POINT t1;
	GetCursorPos(&t1);
	contact.pointerInfo.ptPixelLocation.x = t1.x;
	contact.pointerInfo.ptPixelLocation.y = t1.y;


	//SWIPE DOWN GESTURE
	contact.pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
	InjectTouchInput(1, &contact); // Injecting the touch down on screen

	contact.pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;

	for (int i = 0; i < 700; i++) {
		if (i % 20 == 0)
		{
			contact.pointerInfo.ptPixelLocation.x += dir; // updating the X Co-ordinate to x-100 pixels
			InjectTouchInput(1, &contact);
		}
	}
	// Lifts the touch input UP
	contact.pointerInfo.pointerFlags = POINTER_FLAG_UP;
	InjectTouchInput(1, &contact);
}

void GestureExecutor::swipeUpDown(int dir)
{
	POINTER_TOUCH_INFO contact;

	InitializeTouchInjection(10, TOUCH_FEEDBACK_NONE);

	memset(&contact, 0, sizeof(POINTER_TOUCH_INFO));
	contact.pointerInfo.pointerType = PT_TOUCH; //we're sending touch input
	contact.pointerInfo.pointerId = 0;          //contact 0
	contact.touchFlags = TOUCH_FLAG_NONE;
	contact.touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
	contact.orientation = 90;
	contact.pressure = 32000;

	contact.pointerInfo.ptPixelLocation.x = 910;
	contact.pointerInfo.ptPixelLocation.y = 600;

	//
	// set the contact area depending on thickness
	//
	contact.rcContact.top = contact.pointerInfo.ptPixelLocation.y - 2;
	contact.rcContact.bottom = contact.pointerInfo.ptPixelLocation.y + 2;
	contact.rcContact.left = contact.pointerInfo.ptPixelLocation.x - 2;
	contact.rcContact.right = contact.pointerInfo.ptPixelLocation.x + 2;

	POINT t1;
	GetCursorPos(&t1);
	contact.pointerInfo.ptPixelLocation.x = t1.x;
	contact.pointerInfo.ptPixelLocation.y = t1.y;


	//SWIPE DOWN GESTURE
	contact.pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
	InjectTouchInput(1, &contact); // Injecting the touch down on screen

	contact.pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;

	for (int i = 0; i < 700; i++) {
		if (i % 20 == 0)
		{
			contact.pointerInfo.ptPixelLocation.y += dir; // updating the X Co-ordinate to x-100 pixels
			InjectTouchInput(1, &contact);
		}
	}
	// Lifts the touch input UP
	contact.pointerInfo.pointerFlags = POINTER_FLAG_UP;
	InjectTouchInput(1, &contact);

}

void GestureExecutor::hideAllWindows() {
	INPUT keyboardInput;

	keyboardInput.type = INPUT_KEYBOARD;
	keyboardInput.ki.wScan = 0;
	keyboardInput.ki.time = 0;
	keyboardInput.ki.dwExtraInfo = 0;

	//Press Windows Key
	keyboardInput.ki.wVk = 0x5C;
	keyboardInput.ki.dwFlags = 0;
	SendInput(1, &keyboardInput, sizeof(keyboardInput));

	//Press M Key
	keyboardInput.ki.wVk = 0x4D;
	keyboardInput.ki.dwFlags = 0;
	SendInput(1, &keyboardInput, sizeof(keyboardInput));

	//Relase M key
	keyboardInput.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &keyboardInput, sizeof(keyboardInput));
	
	//Release Windows Key
	keyboardInput.ki.wVk = 0x5C;
	keyboardInput.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &keyboardInput, sizeof(keyboardInput));	
}

void GestureExecutor::execute(int gid)
{
	switch (gid) {
	case 0:
		swipeLeftRight(-1);
		break;
	case 1:
		swipeLeftRight(1);
		break;
	case 2:
		swipeUpDown(1);
		break; 
	case 3:
		swipeUpDown(-1);
		break;
	case 4:
		zoom(1);
		break;
	case 5:
		zoom(-1);
		break;
	case 6:
		hideAllWindows();
		break;
	default:
		std::cout << "Invalid gesture Id" << gid << std::endl;
		break;
	}
}
