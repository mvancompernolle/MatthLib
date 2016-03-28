#include "renderutils.h"

void drawMatrix( const matth::mat3& mat, unsigned TINT ) {
	float size = 50.0f;
	matth::vec2 pos = mat[2].xy;
	matth::vec2 up = pos + mat[1].xy.normal() * size;
	matth::vec2 right = pos + mat[0].xy.normal() * size;

	sfw::drawLine( pos.x, pos.y, right.x, right.y, RED );
	sfw::drawLine( pos.x, pos.y, up.x, up.y, GREEN );
}

void drawVector( const matth::mat3& mat, const matth::vec2& v, unsigned TINT ) {
	matth::vec2 a = ( mat * matth::vec3{ v.x, v.y, 1.0f } ).xy;
	sfw::drawLine( mat[2].x, mat[2].y, a.x, a.y, TINT );
}

void drawPlane( const matth::Plane& p ) {
	const matth::vec2 right = p.normal.perp();
	const matth::vec2 p1 = p.pos + right * 800.0f;
	const matth::vec2 p2 = p.pos - right * 800.0f;
	sfw::drawLine( p1.x, p1.y, p2.x, p2.y );
	matth::Ray r;
	r.dir = p.normal;
	r.len = 50.0f;
	r.pos = p.pos;
	drawRay( r );
}

void drawAABB( const matth::AABB& box ) {
	sfw::drawLine( box.min().x, box.min().y, box.max().x, box.min().y );
	sfw::drawLine( box.min().x, box.min().y, box.min().x, box.max().y );
	sfw::drawLine( box.min().x, box.max().y, box.max().x, box.max().y );
	sfw::drawLine( box.max().x, box.max().y, box.max().x, box.min().y );
}

void drawHull( const matth::ConvexHull& hull ) {
	for ( int i = 0; i < hull.verts.size(); ++i ) {
		sfw::drawLine( hull.verts[i].x, hull.verts[i].y, hull.verts[( i + 1 ) % hull.verts.size()].x, hull.verts[( i + 1 ) % hull.verts.size()].y );
	}
}

void drawCircle( const matth::Circle& c ) {
	sfw::drawCircle( c.pos.x, c.pos.y, c.radius );
}

void drawRay( const matth::Ray& r ) {
	const matth::vec2 endPoint = r.pos + r.dir * r.len;
	const matth::vec2 endLine = ( r.pos + r.dir * r.len * 0.8f );
	sfw::drawLine( r.pos.x, r.pos.y, endLine.x, endLine.y );
	const matth::vec2 perpen = ( endPoint - r.pos ).normal().perp();
	const matth::vec2 anchorPoint = r.pos + r.dir * r.len * 0.8f;
	std::vector<matth::vec2> points;
	points.push_back( anchorPoint + perpen * r.len * 0.25f );
	points.push_back( anchorPoint - perpen * r.len * 0.25f );
	points.push_back( endPoint );
	matth::ConvexHull dirHull = { points };
	drawHull( dirHull );
}

void drawTransform( const Transform& transform ) {
	drawMatrix( transform.getGlobalTransform() * matth::mat3::scale(30.0f, 30.0f), 0 );
}

void drawRigidBody( const Transform& transform, const RigidBody& rbody ) {
	matth::vec2 pos = transform.getPos();
	matth::vec2 acc = pos + rbody.acc;
	matth::vec2 vel = pos + rbody.vel;

	sfw::drawLine(pos.x, pos.y, acc.x, acc.y, CYAN );
	sfw::drawLine( pos.x, pos.y, vel.x, vel.y, YELLOW );
}

void drawCollider( const Transform& transform, const Collider& collider ) {
	switch ( collider.shape ) {
	case Collider::e_CIRCLE:
		drawCircle( transform.getGlobalTransform() * collider.circle );
		break;
	case Collider::e_RAY:
		drawRay( transform.getGlobalTransform() * collider.ray );
		break;
	case Collider::e_AABB:
		drawAABB( transform.getGlobalTransform() * collider.aabb );
		break;
	case Collider::e_PLANE:
		drawPlane( transform.getGlobalTransform() * collider.plane );
		break;
	case Collider::e_CHULL:
		drawHull( transform.getGlobalTransform() * collider.cHull );
	default:
		break;
	}
}