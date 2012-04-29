#include "Triangle.h"

Triangle::Triangle()
{
	mVertexes[0] = vector3();
	mVertexes[1] = vector3();
	mVertexes[2] = vector3();
}

Triangle::Triangle( vector3 iA, vector3 iB, vector3 iC )
{
	mVertexes[0] = iA;
	mVertexes[1] = iB;
	mVertexes[2] = iC;
}

// Real Time Collision Detection: Page 168 Chapter 5 Basic Primitive Tests
// Find point P on triangle ABC closest to sphere center
vector3 Triangle::closestPointToPoint( const vector3& p, const vector3& a, const vector3& b, const vector3& c )
{
	vector3 ab = b - a;
	vector3 ac = c - a;
	vector3 bc = c - b;

	// Compute parametric position s for projection P’ of P on AB,
	// P’ = A + s*AB, s = snom/(snom+sdenom)
	real snom = (p-a).dot(ab);
	real sdenom = (p-b).dot(a-b);

	// Compute parametric position t for projection P’ of P on AC,
	// P’ = A + t*AC, s = tnom/(tnom+tdenom)
	float tnom = (p-a).dot(ac);
	float tdenom = (p-c).dot(a-c);

	if (snom <= 0.0f && tnom <= 0.0f)
		return a; // Vertex region early out

	// Compute parametric position u for projection P’ of P on BC,
	// P’ = B + u*BC, u = unom/(unom+udenom)
	real unom = (p-b).dot(bc);
	real udenom = (p-c).dot(b-c);
	
	if (sdenom <= 0.0f && unom <= 0.0f)
		return b; // Vertex region early out
	
	if (tdenom <= 0.0f && udenom <= 0.0f)
		return c; // Vertex region early out

	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
	vector3 n = (b-a).cross(c-a);
	real vc = n.dot((a-p).cross(b-p));
	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab;

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
	real va = n.dot((b-p).cross(c-p));

	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc;

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
	real vb = n.dot((c-p).cross(a-p));

	// If P outside CA and within feature region of CA,
	// return projection of P onto CA
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac;

	// P must project inside face region. Compute Q using barycentric coordinates
	real u = va / (va + vb + vc);
	real v = vb / (va + vb + vc);
	real w = 1.0f - u - v; // = vc / (va + vb + vc)

	return u * a + v * b + w * c;
}

vector3 Triangle::normal( const vector3& a, const vector3& b ) {
	return (a.cross(b)).normalized();
}