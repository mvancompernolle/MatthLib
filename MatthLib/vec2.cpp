#include "vec2.h"


namespace matth {

	vec2 vec2::fromAngle( float angle ) {
		return{ cos( ( angle * PI ) / 180.0f ), sin( ( angle*PI ) / 180.0f ) };
	}

	const float& vec2::operator[]( int pos ) const {
		return v[pos];
	}

	float& vec2::operator[]( int pos ) {
		return v[pos];
	}

	vec2 vec2::operator-() const {
		return{ -x, y };
	}

	vec2 vec2::reflect( const vec2& n ) const {
		return {*this - 2 * (dot(*this, n.normal()) * n.normal())};
	}

	float vec2::length() const {
		return sqrt( x*x + y*y );
	}

	vec2 vec2::normal() const {
		float len = length();
		return{ x / len, y / len };
	}

	vec2 vec2::perp() const {
		return{ -y, x };
	}

	float vec2::angle() const {
		return atan2( y, x ) * 180.0f / PI;
	}

	// friend functions ////////////////////////////////////

	float dot( const vec2& lhs, const vec2& rhs ) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	vec2 interp( const vec2& lhs, const vec2& rhs, float val ) {
		val = std::fmax( 0.0f, std::fmin( val, 1.0f ) );
		return{ lhs * val + ( rhs * ( 1.0f - val ) ) };
	}

	bool operator==( const vec2& lhs, const vec2& rhs ) {
		return abs( lhs.x - rhs.x ) < FLT_EPSILON && abs( lhs.y - rhs.y ) < FLT_EPSILON;
	}

	bool operator!=( const vec2& lhs, const vec2& rhs ) {
		return !( lhs == rhs );
	}

	bool operator<( const vec2& lhs, const vec2& rhs ) {
		return lhs.x < rhs.x && lhs.y < rhs.y;
	}

	bool operator<=( const vec2& lhs, const vec2& rhs ) {
		return ( lhs.x < rhs.x || abs( lhs.x - rhs.x ) < FLT_EPSILON ) && ( lhs.y < rhs.y || abs( lhs.y - rhs.y ) < FLT_EPSILON );
	}

	bool operator>( const vec2& lhs, const vec2& rhs ) {
		return lhs.x > rhs.x && lhs.y > rhs.y;
	}

	bool operator>=( const vec2& lhs, const vec2& rhs ) {
		return ( lhs.x > rhs.x || abs( lhs.x - rhs.x ) < FLT_EPSILON ) && ( lhs.y > rhs.y || abs( lhs.y - rhs.y ) < FLT_EPSILON );
	}

	vec2 operator+( const vec2& lhs, const vec2& rhs ) {
		return {lhs.x + rhs.x, lhs.y + rhs.y};
	}

	vec2 operator-( const vec2& lhs, const vec2& rhs ) {
		return{ lhs.x - rhs.x, lhs.y - rhs.y };
	}

	vec2 operator+=( vec2& lhs, const vec2& rhs ) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	vec2 operator-=( vec2& lhs, const vec2& rhs ) {
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	vec2 operator*( const vec2& lhs, float val ) {
		return {lhs.x * val, lhs.y * val};
	}

	vec2 operator*( float val, const vec2& lhs ) {
		return lhs * val;
	}

	vec2 operator/( const vec2& lhs, float val ) {
		return{ lhs.x / val, lhs.y / val };
	}

	vec2 operator*=( vec2& lhs, float val ) {
		lhs.x *= val;
		lhs.y *= val;
		return lhs;
	}

	vec2 operator/=( vec2& lhs, float val ) {
		lhs.x /= val;
		lhs.y /= val;
		return lhs;
	}

};
