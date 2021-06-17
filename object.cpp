#include "object.h"

// RotatableLine
void RotatableLine::setDiameter()
{
	// set diameter
	if (gradient <= 90) {
		diameter.start.x = center.x + r * cos(180 + gradient);
		diameter.start.y = center.y - r * sin(180 + gradient);
		diameter.end.x = center.x + r * cos(gradient);
		diameter.end.y = center.y - r * sin(gradient);
	}
	else {
		diameter.start.x = center.x + r * cos(gradient);
		diameter.start.y = center.y - r * sin(gradient);
		diameter.end.x = center.x + r * cos(180 + gradient);
		diameter.end.y = center.y - r * sin(180 + gradient);
	}
}

void RotatableLine::increaseGrad() {
	gradient += w;
	if (gradient >= 180) {
		gradient = 0;
	}

	// renew diameter
	setDiameter();
}

void RotatableLine::decreaseGrad() {
	gradient -= w;
	if (gradient < 0) {
		gradient = 180;
	}

	// renew diameter
	setDiameter();
}

void RotatableLine::setW(int new_w) {
	w = new_w;
}

void RotatableLine::setR(int new_r) {
	r = new_r;
}

int RotatableLine::getR() {
	return r;
}

// Water
void Water::calculatePath(vector<RotatableLine> lines, int line_num) {
	int path_length = pre_path.size();
	Dot last_loc = pre_path[path_length - 1].end;
	Line new_line;
	Dot next_loc;

	new_line.start = last_loc;
	new_line.end = cur_loc;
	pre_path.push_back(new_line);
	last_loc = cur_loc;

	if (on_line) {
		RotatableLine dest_line = lines[dest];
		cur_loc.x += 2 * cos(dest_line.gradient + 180);
		cur_loc.y -= 2 * sin(dest_line.gradient + 180);
		if (dest_line.gradient <= 90) {
			if (cur_loc.y > dest_line.diameter.start.y) cur_loc = dest_line.diameter.start;
		}
		else {
			if (cur_loc.y > dest_line.diameter.end.y) cur_loc = dest_line.diameter.end;
		}
	}
	else {
		cur_loc.y += 2;
		// get dest and dest_loc
		dest = -1;
		dest_loc.x = last_loc.x;
		dest_loc.y = 1028;
		for (int i = 0; i < line_num; i++) {
			Line tmp_line = lines[i].diameter;
			if (tmp_line.start.x > last_loc.x || last_loc.x > tmp_line.end.x) continue;
			float delta_x = last_loc.x - lines[i].center.x;
			float delta_y = -tan(lines[i].gradient)*delta_x;
			float tmp_y = lines[i].center.y - delta_y;
			if (dest_loc.y > tmp_y) {
				dest_loc.y = tmp_y;
				dest = i;
			}
		}
		// compare cur_loc.y with dest_loc.y
		if (cur_loc.y > dest_loc.y) {
			cur_loc = dest_loc;
			on_line = 0;
		}
	}
}