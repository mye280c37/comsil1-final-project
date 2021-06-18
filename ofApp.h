#pragma once

#include "ofMain.h"
#include "object.h"
#include <cstdlib>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		int WIDTH = 750;
		int HEIGHT = 900;
		int obj_range;
		int l_flag;
		int d_flag;
		int s_flag;
		int q_flag;
		int line_r; 
		int line_num;
		RotatableLine *lines;
		Dot water_point;
		int cur_line;
		Water water;
		WaterPail water_pail;

		int initializeObject();
		int pickSetId(int datum);
};
