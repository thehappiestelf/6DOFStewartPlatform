#ifndef VECTOR3_H
#define VECTOR3_H
//------------------------------------------------------------------------------
// Vector3 class
// dan@marginallycelver.com 2013-03-16
//------------------------------------------------------------------------------
// Copyright at end of file.
// please see http://www.github.com/MarginallyClever/RotaryStewartPlatform for more information.


#include "Arduino.h"


//------------------------------------------------------------------------------
class Vector3 {
public:
  // these usions allow the Vector3 to be used as a color component
  float x;
  float y;
  float z;

public:
  inline Vector3() {}

  
  inline Vector3( float xx, float yy, float zz ) {
    x = xx;
    y = yy;
    z = zz;
  }


  inline Vector3( float v[ 3 ] ) {
    x = v[ 0 ];
    y = v[ 1 ];
    z = v[ 2 ];
  }

  
  ~Vector3() {};


  inline Vector3 &MakeZero() {
    x=0;
    y=0;
    z=0;

    return *this;
  }

  
  inline Vector3 &Set( float xx, float yy, float zz ) {
    x = xx;
    y = yy;
    z = zz;

    return *this;
  }


  inline Vector3 operator + () const {  // Unary negation
    return Vector3(*this);
  }


  inline Vector3 operator - () const {  // Unary negation
    return Vector3( -x, -y, -z );
  }


  inline Vector3 operator *= ( float v ) {  // assigned multiply by a float
    x *= v;
    y *= v;
    z *= v;

    return *this;
  }


  inline Vector3 operator /= ( float t ) {  // assigned division by a float
    float v;

    if( t == 0.0f )
      v = 0;
    else
      v = 1.0f / t;

    x *= v;
    y *= v;
    z *= v;

    return *this;
  }


  inline Vector3 operator -= ( const Vector3 &v ) {  // assigned subtraction
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
  }


  inline Vector3 operator += ( const Vector3 &v ) {  // assigned addition
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
  }


  inline Vector3 operator *= ( const Vector3 &v ) {  // assigned mult.
    x *= v.x;
    y *= v.y;
    z *= v.z;

    return *this;
  }


  inline Vector3 operator ^= ( const Vector3 &v ) {  // assigned cross product
    float nx, ny, nz;
    
    nx = ( y * v.z - z * v.y );
    ny =-( x * v.z - z * v.x );
    nz = ( x * v.y - y * v.x );
    x = nx;
    y = ny;
    z = nz;

    return *this;
  }


  inline bool operator == ( const Vector3 &v ) const {
    return ( fabs( x - v.x ) < 0.01f &&
             fabs( y - v.y ) < 0.01f &&
             fabs( z - v.z ) < 0.01f );
  }


  inline bool operator != ( const Vector3 &v ) const {
    return ( fabs( x - v.x ) > 0.01f ||
             fabs( y - v.y ) > 0.01f ||
             fabs( z - v.z ) > 0.01f );
  }


// METHODS
  inline float Length() const {
    return (float)sqrt( *this | *this );
  }


  inline float LengthSquared() const {
    return *this | *this;
  }


  inline void Normalize() {
    float len, iLen;

    len = Length();
    if( !len ) iLen = 0;
    else iLen = 1.0f / len;

    x *= iLen;
    y *= iLen;
    z *= iLen;
  }


  inline float NormalizeLength() {
    float len, iLen;

    len = Length();
    if( !len ) iLen = 0;
    else iLen = 1.0f / len;

    x *= iLen;
    y *= iLen;
    z *= iLen;

    return len;
  }


  inline void ClampMin( float min ) {  // Clamp to minimum
    if( x < min ) x = min;
    if( y < min ) y = min;
    if( z < min ) z = min;
  }


  inline void ClampMax( float max ) {  // Clamp to maximum
    if( x > max ) x = max;
    if( y > max ) y = max;
    if( z > max ) z = max;
  }


  inline void Clamp( float min, float max ) {  // Clamp to range ]min,max[
    ClampMin( min );
    ClampMax( max );
  }


  // Interpolate between *this and v
  inline void Interpolate( const Vector3 &v, float a ) {
    float b( 1.0f - a );

    x = b * x + a * v.x;
    y = b * y + a * v.y;
    z = b * z + a * v.z;
  }


  inline float operator | ( const Vector3 &v ) const {  // Dot product
    return x * v.x + y * v.y + z * v.z;
  }


  inline Vector3 operator / ( float t ) const {  // vector / float
    if( t == 0.0f )
      return Vector3( 0, 0, 0 );

    float s( 1.0f / t );

    return Vector3( x * s, y * s, z * s );
  }


  inline Vector3 operator + ( const Vector3 &b ) const {  // vector + vector
    return Vector3( x + b.x, y + b.y, z + b.z );
  }


  inline Vector3 operator - ( const Vector3 &b ) const {  // vector - vector
    return Vector3( x - b.x, y - b.y, z - b.z );
  }


  inline Vector3 operator * ( const Vector3 &b ) const {  // vector * vector
    return Vector3( x * b.x, y * b.y, z * b.z );
  }


  inline Vector3 operator ^ ( const Vector3 &b ) const {  // cross(a,b)
    float nx, ny, nz;

    nx =  y * b.z - z * b.y;
    ny =  z * b.x - x * b.z;
    nz =  x * b.y - y * b.x;

    return Vector3( nx, ny, nz );
  }


  inline Vector3 operator * ( float s ) const {
    return Vector3( x * s, y * s, z * s );
  }


  inline void Rotate( Vector3 &axis, float angle ) {
	  float   sa = (float)sin( angle );
    float   ca = (float)cos( angle );
	  Vector3 axis2( axis );
	  float   m[9];

	  axis2.Normalize();

	  m[ 0 ] = ca + (1 - ca) * axis2.x * axis2.x;
	  m[ 1 ] = (1 - ca) * axis2.x * axis2.y - sa * axis2.z;
	  m[ 2 ] = (1 - ca) * axis2.z * axis2.x + sa * axis2.y;
	  m[ 3 ] = (1 - ca) * axis2.x * axis2.y + sa * axis2.z;
	  m[ 4 ] = ca + (1 - ca) * axis2.y * axis2.y;
	  m[ 5 ] = (1 - ca) * axis2.y * axis2.z - sa * axis2.x;
	  m[ 6 ] = (1 - ca) * axis2.z * axis2.x - sa * axis2.y;
	  m[ 7 ] = (1 - ca) * axis2.y * axis2.z + sa * axis2.x;
	  m[ 8 ] = ca + (1 - ca) * axis2.z * axis2.z;

          Vector3 src( *this );

	  x = m[0] * src.x + m[1] * src.y + m[2] * src.z;
	  y = m[3] * src.x + m[4] * src.y + m[5] * src.z;
	  z = m[6] * src.x + m[7] * src.y + m[8] * src.z;
  }

  inline operator float *() {
    return &this->x;
  }
};

//------------------------------------------------------------------------------
// Copyright (C) 2013 Dan Royer (dan@marginallyclever.com)
// Permission is hereby granted, free of charge, to any person obtaining a 
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//------------------------------------------------------------------------------
#endif  // VECTOR3_H