#include "bspline.h"

BSpline::BSpline()
{
	knots = 0;
}

BSpline::BSpline(vector<vec3> *pts, int num_segments) : BSpline()
{
	setOrder(7);
	setKnots(standardKnotSeq(pts->size() - 1, k));
	setControlPoints(pts);
	length = calc_arclength_table(num_segments, segments);
}

/* Determine the index of focus for a given u */
int BSpline::getIndexOfFocus(float u)
{
	int i = 0;
	int m = ctrlPts.size() - 1;

	if (u >= 1)		// for end of the curve, index of focus = m
		return m;

	for (i = 0; i < m + k; i++)		// go through knot list 
	{
		if (u >= knots[i] && u < knots[i + 1])	// if this interval contains u
			return i;
	}
	return -1;
}

void BSpline::setControlPoints(vector<vec3> *p)
{
	for (vector<vec3>::iterator it = p->begin(); it < p->end(); it++)
	{
		vec3 pt = *it;
		ctrlPts.push_back(pt);
	}
}

void BSpline::setOrder(int in_k)
{
	k = in_k;
	if (k < 1)	// minimum order = 1
		k = 1;
}

void BSpline::setKnots(float *U)
{
	if (knots)
		free(knots);	// free memory
	knots = U;
}

// compute a list of arc_segments
double BSpline::calc_arclength_table(int n, vector<arc_segment> &table)
{
	vector<vec3> list;
	vector<float> u_list;
	float step_u = 1.0f / n;
	double arclength = 0;

    // generate a list of n points along the curve
	getLinePoints(&list, &u_list, step_u);
    // compute stats on each curve segment
	for (int i = 0; i < list.size() - 1; i++)
	{
		vec3 curr_pt = list[i];
		vec3 next_pt = list[i + 1];

		double dist = glm::length(next_pt - curr_pt);
		table.push_back(arc_segment(dist, arclength, u_list[i], u_list[i + 1]));
		arclength += dist;
	}
	return arclength;
}

float wrap(float s)
{
	if (s > 1)
		return s - 1;
	if (s < 0)
		return s + 1;
	return s;
}

// returns the position of the curve at arclength s
vec3 BSpline::arc_pos(float s)
{
	while (s < 0)
		s += length;
	while (s > length)
		s -= length;

	return arc_pos(s, 0, segments.size() - 1);
}

// binary search through the arc_segment list to find the position of the curve
// at arclength s
vec3 BSpline::arc_pos(float s, int start, int end)
{
	int mid = (start + end) / 2;

	if (start == end)
	{
		float pct = (s - segments[start].dist_offset) / segments[start].dist;
		float u = ((1 - pct) * segments[start].t0 + pct * segments[start].t1);
		return pos(getIndexOfFocus(u), u);
	}
	
	if (s >= segments[mid].dist_offset && s < segments[mid].dist_offset + segments[mid].dist)
	{
		float pct = (s - segments[mid].dist_offset) / segments[mid].dist;
		float u = ((1 - pct) * segments[mid].t0 + pct * segments[mid].t1);
		return pos(getIndexOfFocus(u), u);
	}
	else if (s < segments[mid].dist_offset)
		return arc_pos(s, start, mid - 1);
	else
		return arc_pos(s, mid + 1, end);

}

/*
effsum: Efficient algorithm for BSplines
Given a index of focus, evaluate the point at u
*/
vec3 BSpline::pos(int d, float u)
{
	vec3 *c = new vec3[k];

	for (int i = 0; i <= k - 1; i++)
	{
		c[i] = ctrlPts[d - i];		//nonzero coefficients
	}
	int step = 0;
	for (int r = k; r >= 2; r--)		// the columns of the table
	{
		int i = d;
		for (int s = 0; s <= r - 2; s++)	// the elements of the column
		{
			float omega = (u - knots[i]) / (knots[i + r - 1] - knots[i]);
			c[s] = c[s] * omega + c[s + 1] * (1 - omega);
			i = i - 1;
		}
	}
	return vec3(c[0]);
}

void BSpline::getLinePoints(vector<vec3> *list, vector<float> *u_list, float step_u)
{
	list->clear();
	if (u_list) 
		u_list->clear();	// clear the target lists

	int m = ctrlPts.size() - 1;
	float u = 0;
	float prev_u = 0;

	if (m + 1 < k)		// need # of control points >= k for a line
		return;

	int d = 0;
	bool end = false;	// flag if we clamped u to the end of the curve (only clamp it once so the loop can end after)
	while (u <= 1)
	{
		while (u < 1 && u >= knots[d + 1] && d < m + k)
			d++;

		list->push_back(pos(d, u));	// evaluate the final curve point and store it
		if (u_list)
			u_list->push_back(u);					// store the u of the point

		u += step_u;

		if (prev_u < 1 && u > 1 && !end)	// if we overshot the end of the curve, clamp it 
		{
			end = true;		// only clamp it once
			u = 1;			// clamp u to the end of the curve
		}
		prev_u = u;
	}
}

void BSpline::arc_getLinePoints(vector<vec3> *list, float step_u)
{
	list->clear();

	int m = ctrlPts.size() - 1;
	float u = 0;
	float prev_u = 0;

	if (m + 1 < k)		// need # of control points >= k for a line
		return;

	int d = 0;
	bool end = false;	// flag if we clamped u to the end of the curve (only clamp it once so the loop can end after)
	int idx = 0;
	while (u < length)
	{
		list->push_back(arc_pos(u));	// evaluate the final curve point and store it

		u += step_u;

		if (prev_u < length && u > length && !end)	// if we overshot the end of the curve, clamp it 
		{
			end = true;		// only clamp it once
			u = length;			// clamp u to the end of the curve
		}
		prev_u = u;
	}
	list->push_back(pos(getIndexOfFocus(1), 1));
}

/* return the standard knot sequence for m & k */
float *BSpline::standardKnotSeq(int m, int k)
{
	float *knots = new float[m + k + 1];
	for (int i = 0; i < k; i++)			// first k knots = 0
		knots[i] = 0;

	float step = (float)1 / ((m + 1) - (k - 1));

	float v = step;
	for (int i = k; i < m + 1; i++)		// the middle knots interpolate between 0 to 1
	{
		knots[i] = v;
		v += step;
	}
	for (int i = m + 1; i <= m + k; i++)	// last k knots are = 1
	{
		knots[i] = 1;
	}
	return knots;
}

double BSpline::bSplineBasis(int i, int m, int k, double u, float *knots)
{
	if (k <= 0)										// weight of negative orders = 0
		return 0;
	if (k == 1)										// base case: order 1
	{
		if (knots[i] <= u && u < knots[i + 1])		// if u is inside the ith interval, return 1
			return 1;
		else
			return 0;
	}
	double denomA = knots[i + k - 1] - knots[i];	// calculate denomator of intervalA
	double denomB = knots[i + k] - knots[i + 1];	// calc denominator of intervalB
	double a = denomA == 0 ? 0 : (u - knots[i]) / denomA * bSplineBasis(i, m, k - 1, u, knots);		// if size of intervalA is 0, make the weight of intervalA = 0
	double b = denomB == 0 ? 0 : (knots[i + k] - u) / denomB * bSplineBasis(i + 1, m, k - 1, u, knots);		// same for B
	return (a + b);		// return weight sum
}
