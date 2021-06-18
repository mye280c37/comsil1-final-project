#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cout << "setup method is called" << endl;

	ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(255, 255, 255);
	ofSetLineWidth(4);

	line_num = 6;
	x_range = (int)1024 / (line_num+1);
	line_r = (int)3 * x_range / 4;
	cout << "x_range is " << x_range << endl;
	cout << "line_r is " << line_r << endl;

	d_flag = 0;
	s_flag = 0;
	q_flag = 0;

	l_flag = initializeObject();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	//cout << "draw method is called" << endl;
	ofSetColor(127, 66, 70);
	// Draw shapes for ceiling and floor
	ofDrawRectangle(0, 0, 1024, 50); // Top left corner at (50, 50), 100 wide x 100 high
	ofDrawRectangle(0, 768-25, 1024, 25); // Top left corner at (50, 50), 100 wide x 100 high

	ofSetLineWidth(5);
	if (d_flag) {
		// draw water_point
		ofSetColor(0, 0, 0);
		ofDrawCircle(water_point.x, water_point.y, 12);
		ofSetColor(255, 255, 255);
		ofDrawCircle(water_point.x, water_point.y, 7);
		// draw lines
		ofSetColor(40, 150, 65);
		for (int i = 0; i < line_num; i++) {
			ofDrawCircle(lines[i].center.x, lines[i].center.y, 5);
			ofDrawLine(lines[i].diameter.start.x, lines[i].diameter.start.y, lines[i].diameter.end.x, lines[i].diameter.end.y);
		}
		ofSetColor(198, 0, 0);
		ofDrawCircle(lines[cur_line].center.x, lines[cur_line].center.y, 5);
		ofDrawLine(lines[cur_line].diameter.start.x, lines[cur_line].diameter.start.y, lines[cur_line].diameter.end.x, lines[cur_line].diameter.end.y);
		// draw water_pail
		ofSetColor(6, 0, 22);
		ofDrawLine(water_pail.left.start.x, water_pail.left.start.y, water_pail.left.end.x, water_pail.left.end.y);
		ofDrawLine(water_pail.bottom.start.x, water_pail.bottom.start.y, water_pail.bottom.end.x, water_pail.bottom.end.y);
		ofDrawLine(water_pail.right.start.x, water_pail.right.start.y, water_pail.right.end.x, water_pail.right.end.y);
	}
	if (s_flag) {
		ofSetColor(0, 170, 204);
		ofSetLineWidth(3);
		//for (int i = 0; i < water.pre_path.size(); i++) {
		//	ofDrawLine(water.pre_path[i].start.x, water.pre_path[i].start.y, water.pre_path[i].end.x, water.pre_path[i].end.y);
		//}
		ofSetColor(0, 0, 205);
		ofDrawCircle(water.cur_loc.x, water.cur_loc.y, 7);
		if (l_flag && water.cur_loc.y < 768-25-7) {
			water.calculatePath(lines, line_num);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'v') {
		// HACK: only needed on windows, when using ofSetAutoBackground(false)
		glReadBuffer(GL_FRONT);
		ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
	}
	if (key == 'q') {
		// Reset flags
		l_flag = 0;
		d_flag = 0;
		s_flag = 0;

		// Free the dynamically allocated memory exits.
		lines.clear();

		cout << "Dynamically allocated memory has been freed." << endl;

		_Exit(0);
	}
	if (key == 'd') {
		d_flag = 1;
	}
	if (key == 's') {
		if (d_flag) {
			s_flag = 1;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == OF_KEY_RIGHT) {
		cur_line++;
		if (cur_line >= line_num) {
			cur_line = 0;
		}
	}
	if (key == OF_KEY_LEFT) {
		cur_line--;
		if (cur_line < 0) {
			cur_line = line_num - 1;
		}
	}
	if (key == OF_KEY_UP) {
		if (d_flag && s_flag) {
			l_flag = 0;
			lines[cur_line].increaseGrad();
			l_flag = water.checkCurLoc(lines);
		}
			
	}
	if (key == OF_KEY_DOWN) {
		if (d_flag && s_flag) {
			l_flag = 0;
			lines[cur_line].decreaseGrad();
			l_flag = water.checkCurLoc(lines);
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

int ofApp::initializeObject() {
	cout << "initializeObject method is called" << endl;

	int highest, lowest;
	int min_y = 768, max_y = 0;
	int above = rand()%2;

	RotatableLine tmp_line;
	tmp_line.r = line_r;

	// create radom line
	for (int i = 0; i < line_num; i++) {
		// set center
		tmp_line.center.x = (float)(rand() % (x_range-line_r)) + (line_r + i * x_range);
		tmp_line.center.y = (float)(rand() % (768 - 2 * (50 + line_r) - line_r/2)) + (50 + line_r ) + (line_r/2);
		
		// set gradient
		tmp_line.gradient = rand() % 180;
		// get diameter
		tmp_line.setDiameter();
		if (min_y > tmp_line.diameter.start.y) {
			min_y = tmp_line.diameter.start.y;
			highest = i;
		}
		if (max_y < tmp_line.diameter.end.y) {
			max_y = tmp_line.diameter.end.y;
			lowest = i;
		}
		cout << tmp_line.center.x << ", " << tmp_line.center.y << endl;
		cout << tmp_line.gradient << endl;
		cout << '(' << tmp_line.diameter.start.x << ", " << tmp_line.diameter.start.y << "), (" << tmp_line.diameter.end.x << ", " << tmp_line.diameter.end.y << ')' << endl;
		lines.push_back(tmp_line);
	}

	// set water_point and initialize cur_line index
	cur_line = highest;
	tmp_line = lines[cur_line];		// target line
	if (tmp_line.diameter.start.x < tmp_line.diameter.end.x) {
		float delta_x = tmp_line.diameter.end.x - tmp_line.diameter.start.x;
		water_point.x = tmp_line.diameter.start.x + rand() % ((int)delta_x-5);
	}
	else {
		float delta_x = tmp_line.diameter.start.x - tmp_line.diameter.end.x;
		water_point.x = tmp_line.diameter.end.x + rand() % (int)delta_x;
	}
	water_point.y = 25;

	cout << "water point: " << water_point.x << ", " << water_point.y << endl;

	// set water_pail
	tmp_line = lines[lowest]; // traget line
	water_pail.bottom.start.x = lines[lowest].center.x - line_r + rand() % (2*line_r);
	water_pail.bottom.start.y = 768 - 25;
	water_pail.bottom.end.x = water_pail.bottom.start.x + line_r;
	water_pail.bottom.end.y = 768 - 25;
	cout << '(' << water_pail.bottom.start.x << ", " << water_pail.bottom.start.y << "), (" << water_pail.bottom.end.x << ", " << water_pail.bottom.end.y << ')' << endl;
	// set water_pail's left
	water_pail.left.end = water_pail.bottom.start;
	water_pail.left.start.x = water_pail.left.end.x - 25;
	water_pail.left.start.y = water_pail.left.end.y - 25;
	// set water_pail's right
	water_pail.right.start = water_pail.bottom.end;
	water_pail.right.end.x = water_pail.right.start.x + 25;
	water_pail.right.end.y = water_pail.right.start.y - 25;

	// check there is valid path
	int start, end;
	if (highest < lowest) {
		start = highest;
		end = lowest;
	}
	else {
		start = lowest;
		end = highest;
	}
	for (int i = start; i < end; i++) {
		if (lines[i].center.y > lines[i + 1].center.y) {
			float tmp_y = lines[i].center.y;
			lines[i].center.y = lines[i + 1].center.y;
			lines[i + 1].center.y = tmp_y;
			lines[i].setDiameter();
			lines[i + 1].setDiameter();
		}
	}

	// initialize water
	water.on_line = 0;
	water.past_dest = -1;
	water.dest = -1;
	Line first_path = { {water_point.x, water_point.y}, {water_point.x, water_point.y + 1} };
	water.cur_loc = { water_point.x, water_point.y + 1 };
	water.pre_path.push_back(first_path);

	return 1;
}
