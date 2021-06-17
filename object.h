#include <iostream>
#include <vector>
#include <cmath>

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
		int w = 1;
		int r = 4;

	public:
		Line diameter;
		int gradient;
		Dot center;

		void increaseGrad();
		void decreaseGrad();
		void setDiameter();
		void setW(int new_w);
		void setR(int new_r);
		int getR();
	
};

class Water {

	public:
		vector<Line> pre_path;
		Dot cur_loc;
		int on_line;
		int dest;
		Dot dest_loc;

		void calculatePath(vector<RotatableLine> lines, int line_num);
};

typedef struct _WaterPail {
	Line left;
	Line bottom;
	Line right;
};