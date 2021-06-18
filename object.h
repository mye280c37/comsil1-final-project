#include <iostream>
#include <vector>
#include <cmath>
#define PI 3.1415926

using namespace std;

typedef struct _Dot {
	float x;
	float y;
}Dot;

typedef struct _Line {
	Dot start;
	Dot end;
}Line;

typedef struct _WaterPail {
	Line left;
	Line bottom;
	Line right;
} WaterPail;

class RotatableLine {

	private:
		int w = 10;

	public:
		Line diameter;
		int gradient;
		Dot center;
		int r;
		int increaseGrad();
		int decreaseGrad();
		void setDiameter();
		void setW(int new_w);
	
};

class Water {

	public:
		vector<Line> pre_path;
		Dot cur_loc;
		int on_line;
		int past_dest;
		int dest;
		Dot dest_loc;

		void calculatePath(RotatableLine* lines, int line_num, int height);
		int checkCurLoc(RotatableLine* lines);
};