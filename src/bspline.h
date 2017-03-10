#ifndef BSPLINE_H
#define BSPLINE_H

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

using namespace glm;
using namespace std;

struct arc_segment
{
	arc_segment(double in_d, double in_offs, double in_t0, double in_t1)
	{
		dist = in_d;
		dist_offset = in_offs;
		t0 = in_t0;
		t1 = in_t1;
	}

	float dist;
	float dist_offset;
	float t0;	// start point 
	float t1;	// end point
};

class BSpline
{
public:
	BSpline();
	BSpline(vector<vec3> *pts, int num_segments);
	void setOrder(int in_k);					// setter
	void setKnots(float *U);					// setter
	void setControlPoints(vector<vec3> *p);		// setter	
	double calc_arclength_table(int n, vector<arc_segment> &table);
	vec3 arc_pos(float s);

	void arc_getLinePoints(vector<vec3> *list, float step_u);
	void getLinePoints(vector<vec3> *list, vector<float> *u_list, float step_u);	// evaluate a list of points on the curve

	int getIndexOfFocus(float u);				// find the index of focus
	vec3 pos(int d, float u);				// efficient algorithm to evaluate a point on the curve

	static float *standardKnotSeq(int m, int k);								// generates the standard knot sequence for given m and k
	static double bSplineBasis(int i, int m, int k, double u, float *knots);	// evaluate a specified bspline basis func 

    vector<arc_segment> segments;   // computed list of curve segments
    double length;                  // total length of all curve segments

private:
	vec3 arc_pos(float s, int start, int end);

protected:
	int k;						// curve order
	float *knots;				// knot array
	vector<vec3> ctrlPts;	// a pointer to the control point list in program
};

#endif
