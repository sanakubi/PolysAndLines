#include "object.h"


obj_point get_obj_point(int x_, int y_){

	obj_point rtn{x_, y_};
	return rtn;
}

obj_line_vec get_obj_line(obj_point start_, obj_point end_){

	obj_line_vec rtn;
	rtn.start = start_;
	rtn.end = end_;
	return rtn;
}

bool pnt_in_line(double n, double p1, double p2) {

	return ((p1 <= n) && (n <= p2)) ? 1 : 0;
}

/// 
/// Object methods
/// 

object::object()
{

}

object::object(int count) : poly_count(count)
{
}

object::~object(){

	lines.erase(lines.begin(), lines.end());
}


void object::add_line(obj_line_vec line){

	lines.push_back(line);
}

void object::add_line(obj_point start_pt, obj_point end_pt){

	lines.push_back( get_obj_line(start_pt, end_pt) );
}

void object::add_point(obj_point pnt){	

	points.push_back(pnt);
}

void object::calcalte_object(){

	if (points.size() < 2) return;

	obj_point last = points[0];
	obj_line_vec buffer;

	for (int i = 1; i < points.size(); i++) {
		buffer.start = last;
		buffer.end = points[i];
		last = points[i];
		add_line(buffer);
	}

	buffer.start = points[points.size() - 1];
	buffer.end = points[0];
	add_line(buffer);
}

int object::get_size(){

	return lines.size();
}

double object::inline_check(obj_point& intr, cls_act& act, double a_start, double a_end, double b_start, double b_end) {

	if (pnt_in_line(a_start, b_start, b_end)) 
	{       // !!!
		act.type = OVRL;
		return a_start;
	} else if (pnt_in_line(a_end, b_start, b_end)) 
	{       // !!!
		act.type = OVRL;
		return a_end;
	} else {
		act.type = NOT;
		return 0;
	}
}

void swap_costyl(obj_line_vec& a, obj_line_vec& b) {

	if (a.start.x > b.start.x || a.start.y > b.start.y) {
		obj_line_vec tmp = a;
		a = b;
		b = a;
	}
}

void swap_costyl(obj_line_vec& a) {	

	if ( a.start.x > a.end.x ) {
		obj_point tmp = a.start;
		a.start = a.end;
		a.end = tmp;
	}
}

cls_act object::line_intersection(obj_line_vec& a, obj_line_vec& b) {     
	//obj_line_vec a, b;

	obj_point intr{ 0,0 };
	cls_act action;
	action.type = NOT;

	//a = a_; 
	//b = b_;
	
	if ((a.start.x == b.start.x) && (a.end.x == b.end.x) && (a.start.y == b.start.y) && (a.end.y == b.end.y)) { action.type = OVRL_FULL; return action; }
	//swap_costyl(a);
	//swap_costyl(b);

	short costyl = 0;

	double a1 = a.end.y - a.start.y;
	double b1 = a.start.x - a.end.x;
	double c1 = -a.start.x * a.end.y + a.start.y * a.end.x;

	double a2 = b.end.y - b.start.y;
	double b2 = b.start.x - b.end.x;
	double c2 = -b.start.x * b.end.y + b.start.y * b.end.x;

	if ( (a1 * b2 == a2 * b1)) // Ïðîâåðêà íà ïàðàëëåëüíîñòü  è íàëîæåíèå
	{
		if (a1 * b2 == b1 * a2 && a1 * c2 == a2 * c1 && b1 * c2 == c1 * b2) 
		{
			if (!(a1 - a2) && (a.start.y == b.start.y) )
			{
				if (abs(c1) > abs(c2)) 
				{
					intr.x = inline_check(intr, action, b.start.x, b.end.x, a.start.x, a.end.x);
				} else if (abs(c1) <= abs(c2)) 
				{
					intr.x = inline_check(intr, action, a.start.x, a.end.x, b.start.x, b.end.x);
				}
				intr.y = a.start.y;
				
				if ((std::min(a.start.x, a.end.x) <= b.start.x) && (b.start.x <= std::max(a.start.x, a.end.x))) costyl++;
				if ((std::min(a.start.x, a.end.x) <= b.end.x) && (b.end.x <= std::max(a.start.x, a.end.x))) costyl++;

			} 
			else if (!(b1 - b2) && (a.start.x == b.start.x))
			{
				if (abs(c1) > abs(c2)) 
				{
					intr.y = inline_check(intr, action, b.start.y, b.end.y, a.start.y, a.end.y);
				} else if (abs(c1) <= abs(c2)) 
				{
					intr.y = inline_check(intr, action, a.start.y, a.end.y, b.start.y, b.end.y);
				}
				intr.x = a.start.x;
				
				if ((std::min(a.start.y, a.end.y) <= b.start.y) && (b.start.y <= std::max(a.start.y, a.end.y))) costyl++;
				if ((std::min(a.start.y, a.end.y) <= b.end.y) && (b.end.y <= std::max(a.start.y, a.end.y))) costyl++;


			} else {
				if (a1 < a2) 
				{
					intr.x = inline_check(intr, action, a.start.x, a.end.x, b.start.x, b.end.x);
				} else {
					intr.x = inline_check(intr, action, b.start.x, b.end.x, a.start.x, a.end.x);
				}

				if ((std::min(a.start.x, a.end.x) <= b.start.x) && (b.start.x <= std::max(a.start.x, a.end.x))) costyl++;
				if ((std::min(a.start.x, a.end.x) <= b.end.x) && (b.end.x <= std::max(a.start.x, a.end.x))) costyl++;
			}

		}

	} else {

		intr.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
		intr.y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);

		if ((intr.x >= std::min(a.start.x, a.end.x)) && (intr.x <= std::max(a.start.x, a.end.x) ) && (intr.y >= std::min(a.start.y, a.end.y) ) && (intr.y <= std::max(a.start.y, a.end.y)))
		{
			if ((intr.x >= std::min(b.start.x, b.end.x)) && (intr.x <= std::max(b.start.x, b.end.x)) && (intr.y >= std::min(b.start.y, b.end.y)) && (intr.y <= std::max(b.start.y, b.end.y)))
			{
				action.type = ITRS;
			}

		}

	}

	if (action.type != ITRS && action.type != NOT) {
		switch (costyl) {
		case 0: { action.type = OVRL_FULL; break; }
		case 1: { action.type = OVRL_OS; break; }
		case 2: { action.type = OVRL; break; }
		default: break;
		}
	}

	action.point = intr;
	return action;
}

report_act object::collision(obj_line_vec& line) {

	report_act rpt{0, NOT};
	bool check;
	cls_act out;
	std::vector<obj_point> points;

	for (int i = 0; i < lines.size(); i++) 
	{
		out = line_intersection(line, lines[i]);
		if (out.type == OVRL || out.type == OVRL_FULL || out.type == OVRL_OS)
		{
			std::cout << "Overlay on line " << lines[i].start << " - " << lines[i].end << std::endl;
			rpt.type = out.type;//OVRL;

				switch (rpt.type)
				{
				case OVRL: {
					rpt.intersections = 2;
				}break;
				case OVRL_FULL: {
					rpt.intersections = 0;
				}break;
				case OVRL_OS: {
					rpt.intersections = 1;
				}break;
				default:
					break;
				}
			
				return rpt;
		}

		check = 1;

		for (int n = 0; n < points.size(); n++)
			if (points[n] == out.point)
				check = 0;
		
		if (check) 
		{
			points.push_back(out.point);
			if (out.type != NOT) rpt.intersections++;
		}
	}

	return rpt;
}

int object::report(obj_line_vec& line) {
	report_act tmp = collision(line);
	int cls = tmp.intersections;

	if (cls == 0) {

		if (tmp.type == OVRL_FULL) {
			std::cout << "Inside an object." << std::endl;
			return 0;
		}

		obj_line_vec temp; 
		temp.start = line.start;

		for (int i = 0; i < lines.size(); i++) 
		{
			temp.end = lines[i].start;
			cls += collision(temp).intersections;
		}

		temp.start = line.end;

		for (int i = 0; i < lines.size(); i++) 
		{
			temp.end = lines[i].start;
			cls += collision(temp).intersections;
		}

		if (cls == lines.size()*2) 
		{
			std::cout << "Inside an object." << std::endl;
			return 0;
		} else {
			std::cout << "Outside the object." << std::endl;
			return 3;
		}

	} else if ( !(cls % 2)) {
		std::cout << "Intersects the entire object. Number of match points: " << cls << std::endl;
		return 1;
	} else {
		std::cout << "Crosses an object on one side. Number of match points: " << cls << std::endl;
		return 2;
	}

}
