#include "stdafx.h"
#include "GestureExecutor.h"
#include <iostream>

/*
void GestureExecutor::swipeLeftRight(int dir)
{

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
			contact.pointerInfo.ptPixelLocation.y--; // updating the X Co-ordinate to x-100 pixels
			InjectTouchInput(1, &contact);
		}
	}
	// Lifts the touch input UP
	contact.pointerInfo.pointerFlags = POINTER_FLAG_UP;
	InjectTouchInput(1, &contact);

}

void GestureExecutor::execute(int gid, int dir)
{
	switch (gid) {
	case 0:
		swipeLeftRight(dir);
		break;
	case 1:
		swipeUpDown(dir);
		break;
	default:
		std::cout << "Invalid gesture Id" << gid << std::endl;
		break;
}
*/