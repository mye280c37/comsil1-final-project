#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(255, 255, 255);
	ofSetLineWidth(4);

	line_num = 6;
	l_flag = 0;
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
	ofSetColor(127, 23, 31);  // Set the drawing color to brown

	// Draw shapes for ceiling and floor
	ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high


	ofSetLineWidth(5);
	if (d_flag) {
		// draw water_point
		// draw lines
		// draw water_pail
	}
	if (s_flag) {
		//
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
		if(l_flag) d_flag = 1;
		else initializeObject();
	}
	if (key == 's') {
		if (l_flag && d_flag) {
			//
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
		lines[cur_line].increaseGrad();
	}
	if (key == OF_KEY_DOWN) {
		lines[cur_line].decreaseGrad();
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

void ofApp::quickSort(int left, int right) {
	/*
		https://reakwon.tistory.com/61?category=308657
	*/
	int pivot = lines[left].center.y;
	int less = left;
	int more = right + 1;

	while (left < right) {
		do {
			do
				less++;
			while (less <= right && lines[less].center.y < pivot);

			do
				more--;
			while (left <= more && pivot < lines[more].center.y);

		} while (less < more);

		// swap left and more
		RotatableLine tmp_line = lines[left];
		lines[left] = lines[more];
		lines[more] = tmp_line;

		quickSort(left, more - 1);
		quickSort(more + 1, right);
	}
}

int ofApp::initializeObject() {
	// create radom line
	RotatableLine tmp_line;
	for (int i = 0; i < line_num; i++) {
		// set center
		tmp_line.center.x = (float)rand() * 1024;
		tmp_line.center.y = (float)rand()* 768;
		// set gradient
		tmp_line.gradient = rand() % 180;
		// get diameter
		tmp_line.setDiameter();

		lines.push_back(tmp_line);
	}

	// sorting lines according to ceter.y : quick sort
	quickSort(0, line_num - 1);

	// set water_point and initialize cur_line index
	cur_line = rand() % 3;
	tmp_line = lines[cur_line];		// target line
	float delta_x = tmp_line.diameter.end.x - tmp_line.diameter.start.x;
	water_point.x = tmp_line.diameter.start.x + (float)rand()*delta_x;
	water_point.y = 20;

	// set water_pail
	tmp_line = lines[line_num - rand() % 3 - 1]; // traget line
	int tmp_grad = rand() % 180;
	float x1, x2;
	if (tmp_grad <= 90) {
		x1 = tmp_line.center.x + tmp_line.getR() * cos(180 + tmp_grad);
		x2 = tmp_line.center.x + tmp_line.getR() * cos(tmp_grad);
	}
	else {
		x1 = tmp_line.center.x + tmp_line.getR() * cos(tmp_grad);
		x2 = tmp_line.center.x + tmp_line.getR() * cos(180 + tmp_grad);
	}
	delta_x = x2 - x1;
	float center_of_bottom;
	center_of_bottom = x1 + (float)rand()*delta_x;
	water_pail.bottom.start.x = center_of_bottom - 2;
	water_pail.bottom.start.y = 768 - 20;
	water_pail.bottom.end.x = center_of_bottom + 2;
	water_pail.bottom.end.y = 768 - 20;
	// set water_pail's left
	water_pail.left.end = water_pail.bottom.start;
	water_pail.left.start.x = water_pail.left.end.x - 1;
	water_pail.left.start.y = water_pail.left.end.y - 1;
	// set water_pail's right
	water_pail.right.start = water_pail.bottom.end;
	water_pail.right.end.x = water_pail.right.start.x + 1;
	water_pail.right.end.y = water_pail.right.start.y - 1;

	return 1;
}
