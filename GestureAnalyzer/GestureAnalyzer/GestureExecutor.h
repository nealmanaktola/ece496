#ifndef __GESTURE_EXECUTOR__  
#define __GESTURE_EXECUTOR__  


class GestureExecutor {
private:
	 void swipeLeftRight(int dir);
	 void zoom(int dir);
	 void swipeUpDown(int dir);
	 void hideAllWindows();
public:
	 void execute(int gid);

};

#endif
