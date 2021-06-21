#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cout << "setup method is called" << "\n" << "\n";

	ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

	//old OF default is 96 - but this results in fonts looking larger than in other programs.
	// setting for Write String on window
	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 30, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(220, 220, 220);

	// initialize flags
	d_flag = 0;
	s_flag = 0;
	l_flag = 0;
	end_flag = 0;

	// initialize setting for lines
	line_num = 6;
	obj_unit = (int)WIDTH / (line_num+1);
	line_r = (int)3 * obj_unit / 4;
	cout << "obj_unit is " << obj_unit << "\n";
	cout << "line_r is " << line_r << "\n" << "\n";

	lines = (RotatableLine*)malloc(sizeof(RotatableLine)*line_num);

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
	ofDrawRectangle(0, 0, WIDTH, 50); // Top left corner at (50, 50), 100 wide x 100 high
	ofDrawRectangle(0, HEIGHT-25, WIDTH, 25); // Top left corner at (50, 50), 100 wide x 100 high

	ofSetLineWidth(5);
	if (d_flag) {
		// draw water_point
		ofSetColor(0, 0, 0);
		ofDrawCircle(water_point.x, water_point.y, 12);
		ofSetColor(255, 255, 255);
		ofDrawCircle(water_point.x, water_point.y, 7);
		// draw lines
		ofSetColor(0, 102, 56);
		for (int i = 0; i < line_num; i++) {
			ofDrawCircle(lines[i].center.x, lines[i].center.y, 5);
			ofDrawLine(lines[i].diameter.start.x, lines[i].diameter.start.y, lines[i].diameter.end.x, lines[i].diameter.end.y);
		}
		// draw current_ line
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
		ofSetColor(0, 80, 255);
		ofDrawCircle(water.cur_loc.x, water.cur_loc.y, 7);
		if (l_flag) {
			if (water.cur_loc.y < HEIGHT - 25 - 7) {
				water.calculatePath(lines, line_num, HEIGHT);
			}
			else {
				if (water_pail.bottom.start.x <= water.cur_loc.x && water.cur_loc.x <= water_pail.bottom.end.x) {
					cout << "success!!" << endl;
					result_msg = "SUCCESS!!";
				}
				else {
					cout << "fail!" << endl;
					result_msg = "      FAIL!  ";
				}
				end_flag = 1;
				l_flag = 0;
				d_flag = 0;
				s_flag = 0;
				l_flag = initializeObject();
			}
		}
	}
	if (end_flag) {
		// display result message
		ofSetColor(0, 0, 0);
		verdana14.drawString(result_msg, WIDTH / 3 + 30, HEIGHT / 2);
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
		free(lines);

		cout << "Dynamically allocated memory has been freed." << endl;

		_Exit(0);
	}
	if (key == 'd') {
		end_flag = 0;
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
	int start_p, end_p;
	int path_limit, path_num;
	int *y_list;
	int min_y = 768, max_y = 0;
	int forward = rand()%2;

	RotatableLine tmp_line;
	tmp_line.r = line_r;
	// create radom line
	// create path
	path_limit = (int)((line_num+1)/2);
	path_num = rand() % (path_limit-1) + 2;
	cout <<"path limit : " << path_limit << " / " << "path num : " << path_num << endl;
	y_list = (int*)malloc(sizeof(int)*line_num);
	if (forward) {
		start_p = highest = rand() % (line_num - (path_num - 1));
		end_p = lowest = highest + path_num - 1;
	}
	else {
		start_p = lowest = rand() % (line_num - (path_num - 1));
		end_p = highest = lowest + path_num - 1;
	}
	y_list[highest] = rand() % (line_num - (path_num - 1) * 2);
	y_list[lowest] = line_num - rand() % (line_num - (y_list[highest] + (path_num - 1) * 2)) - 1;
	cout << "highest_line(" << highest << ")'s y set: " << y_list[highest] << ", lowest_line(" << lowest << ")'s y set: " << y_list[lowest] << endl;

	// set y_list
	for (int i = start_p - 1; i >= 0; i--) {
		y_list[i] = pickSetId(y_list[i + 1]);
	}
	int rest_path = path_num - 2;
	cout << y_list[start_p] << "->";
	for (int i = start_p + 1; i < end_p; i++) {
		rest_path--;
		if (forward) {
			y_list[i] = rand() % (y_list[end_p] - 2 * rest_path - (y_list[i - 1] + 2)) + (y_list[i - 1] + 2);
		}
		else {
			y_list[i] = rand() % ((y_list[i - 1] - 2) - (y_list[end_p] + 2 * rest_path)) + (y_list[end_p] + 2 * rest_path) + 1;
		}
		cout << y_list[i] << "->";
	}
	cout << y_list[end_p] << "\n\n";
	for (int i = end_p + 1; i < line_num; i++) {
		y_list[i] = pickSetId(y_list[i - 1]);
	}

	// set rotatable line object
	for (int i = 0; i < line_num; i++) {
		tmp_line.center.x = (float)(rand() % (obj_unit - line_r)) + (line_r + i * obj_unit);
		tmp_line.center.y = (float)(rand() % (obj_unit - line_r)) + (100 + obj_unit * y_list[i] + line_r);
		// set gradient
		tmp_line.gradient = rand() % 180;
		// get diameter
		tmp_line.setDiameter();

		cout << "lines[" << i << "] : "<< tmp_line.center.x << ", " << tmp_line.center.y << endl;
		lines[i] = tmp_line;
	}
	cout << "\n";

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
	// set water_pail's bottom
	water_pail.bottom.start.x = lines[lowest].center.x - line_r + rand() % (2*line_r);
	water_pail.bottom.start.y = HEIGHT - 25;
	water_pail.bottom.end.x = water_pail.bottom.start.x + line_r;
	water_pail.bottom.end.y = HEIGHT - 25;
	if (water_pail.bottom.end.x > WIDTH) {
		water_pail.bottom.end.x = WIDTH;
		water_pail.bottom.start.x = water_pail.bottom.end.x - line_r;
	}
	if (water_pail.bottom.start.x < 0) {
		water_pail.bottom.start.x = 0;
		water_pail.bottom.end.x = line_r;
	}
	// set water_pail's left
	water_pail.left.end = water_pail.bottom.start;
	water_pail.left.start.x = water_pail.left.end.x;
	water_pail.left.start.y = water_pail.left.end.y - 25;
	// set water_pail's right
	water_pail.right.start = water_pail.bottom.end;
	water_pail.right.end.x = water_pail.right.start.x;
	water_pail.right.end.y = water_pail.right.start.y - 25;

	// initialize water
	water.on_line = 0;
	water.past_dest = -1;
	water.dest = -1;
	water.cur_loc = { water_point.x, water_point.y + 1 };

	return 1;
}

int ofApp::pickSetId(int datum) {
	int set_id;
	if (datum < 2) {
		// only add
		set_id = datum + 2 + rand() % (line_num - datum - 2) ;
	}
	else if (datum > line_num - 3) {
		// only sub
		set_id = rand() % (datum - 1);
	}
	else {
		// choose add or sub
		int do_sub = rand() % 2;
		if (do_sub) {
			set_id = rand() % (datum - 1);
		}
		else {
			set_id = datum + 2 + rand() % (line_num - datum - 2);
		}
	}

	return set_id;
}