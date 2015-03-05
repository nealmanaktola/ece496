#ifndef __GESTURE_EXECUTOR__  
#define __GESTURE_EXECUTOR__  


class GestureExecutor {
private:
	 void swipeLeftRight();
	 void zoom();
	 void swipeUpDown(int dir);
public:
	 void execute(int gid);

};

#endif
