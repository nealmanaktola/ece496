#ifndef __GESTURE_EXECUTOR__  
#define __GESTURE_EXECUTOR__  


class GestureExecutor {
private:
	static void swipeLeftRight(int dir);
	static void swipeUpDown(int dir);
public:
	static void execute(int gid, int dir);

};

#endif
