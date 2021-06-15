#include "object.h"

// RotatableLine
void RotatableLine::increaseGrad() {
	gradient += w;

	// renew diameter
	diameter.start.x = center.x + r * cos(gradient);
	diameter.start.y = center.y - r * sin(gradient);
	diameter.end.x = center.x + r * cos(180 + gradient);
	diameter.end.y = center.y - r * sin(180 + gradient);
}

void RotatableLine::decreaseGrad() {
	gradient -= w;

	// renew diameter
	diameter.start.x = center.x + r * cos(gradient);
	diameter.start.y = center.y - r * sin(gradient);
	diameter.end.x = center.x + r * cos(180 + gradient);
	diameter.end.y = center.y - r * sin(180 + gradient);
}

void RotatableLine::setW(int new_w) {
	w = new_w;
}

void RotatableLine::setR(int new_r) {
	r = new_r;
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
		//
	}
	else {
		cur_loc.y += 2;
		// get dest and dest_loc
		for (int i = 0; i < line_num; i++) {
			Line tmp_line = lines[i].diameter;
			if (tmp_line.start.x > last_loc.x || last_loc.x > tmp_line.end.x) continue;

		}
	}
}