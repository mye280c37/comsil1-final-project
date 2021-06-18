#include "object.h"

// RotatableLine
void RotatableLine::setDiameter()
{
	diameter.start.x = center.x + (float)(r * cos(gradient*PI/180));
	diameter.start.y = center.y - (float) (r * sin(gradient*PI/180));
	diameter.end.x = center.x + (float)(r *cos((180 + gradient)*PI/180));
	diameter.end.y = center.y - (float)(r * sin((180 + gradient)*PI / 180));
}

int RotatableLine::increaseGrad() {
	gradient += w;
	if (gradient >= 180) {
		gradient = 0;
	}

	// renew diameter
	setDiameter();

	return 1;
}

int RotatableLine::decreaseGrad() {
	gradient -= w;
	if (gradient < 0) {
		gradient = 180;
	}

	// renew diameter
	setDiameter();

	return 1;
}

void RotatableLine::setW(int new_w) {
	w = new_w;
}

// Water
void Water::calculatePath(vector<RotatableLine> lines, int line_num) {
	int path_length = pre_path.size();
	Line new_line;
	Dot next_loc;
	RotatableLine dest_line;
	float delta_x, delta_y, tmp_y;

	if (on_line) {
		dest_line = lines[dest];
		if (dest_line.gradient == 0) {
			next_loc = cur_loc;
		}
		else {
			next_loc.x = cur_loc.x + (float) 2* cos((dest_line.gradient + 180)*PI / 180);
			next_loc.y = cur_loc.y - (float)2* sin((dest_line.gradient + 180)*PI / 180);
			if (next_loc.y > dest_line.diameter.end.y) {
				next_loc = dest_line.diameter.end;
				past_dest = dest;
				dest = -1;
				on_line = 0;
			}
		}
	}
	else {
		next_loc.x = cur_loc.x;
		next_loc.y = cur_loc.y + 4;
		dest = -1;
		dest_loc.x = cur_loc.x;
		dest_loc.y = 768;
		for (int i = 0; i < line_num; i++) {
			if (i == past_dest) continue;
			Line tmp_line = lines[i].diameter;
			if (cur_loc.y > tmp_line.end.y) continue;
			if (lines[i].gradient <= 90) {
				if (cur_loc.x < tmp_line.end.x || tmp_line.start.x < cur_loc.x) continue;
			}
			else {
				if (cur_loc.x < tmp_line.start.x  || tmp_line.end.x < cur_loc.x) continue;
			}

			if (lines[i].gradient != 90) {
				delta_x = cur_loc.x - lines[i].center.x;
				delta_y = -tan((lines[i].gradient)*PI / 180)*delta_x;
				tmp_y = lines[i].center.y + delta_y;
				if (dest_loc.y > tmp_y) {
					dest_loc.y = tmp_y;
					dest = i;
				}
			}
			else {
				dest_loc.y = lines[i].diameter.start.y;
			}
		}
		// compare next_loc.y with dest_loc.y
		if (next_loc.y > dest_loc.y) {
			next_loc = dest_loc;
			on_line = 1;
		}
	}

	new_line.start = cur_loc;
	new_line.end = next_loc;
	pre_path.push_back(new_line);
	cur_loc = next_loc;
	cout << '(' << on_line << ')'  << cur_loc.x << ", " << cur_loc.y << endl;
}

int Water::checkCurLoc(vector<RotatableLine> lines) {
	RotatableLine dest_line;
	float delta_x, delta_y;

	if (on_line) {
		dest_line = lines[dest];
		delta_x = cur_loc.x - dest_line.center.x;
		delta_y = -tan((dest_line.gradient)*PI / 180)*delta_x;
		cur_loc.y = dest_line.center.y + delta_y;
	}
	
	return 1;
}