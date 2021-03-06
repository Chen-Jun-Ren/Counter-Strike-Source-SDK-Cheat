#pragma once
class Vector
{
public:
	// Members
	float x, y, z;

	// Construction/destruction:
	Vector(void);
	Vector(float X, float Y, float Z);
	explicit Vector(float XYZ); ///< broadcast initialize

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	// TODO (Ilya): Should there be an init that takes a single float for consistency?

   // Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// Cast to Vector2D...
	/*Vector2D& AsVector2D();
	const Vector2D& AsVector2D() const;*/

	// Initialization methods
	void Random(float minVal, float maxVal);
	inline void Zero(); ///< zero out a vector

	// equality
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	// arithmetic operations
	/*FORCEINLINE Vector& operator+=(const Vector& v);
	FORCEINLINE Vector& operator-=(const Vector& v);
	FORCEINLINE Vector& operator*=(const Vector& v);
	FORCEINLINE Vector& operator*=(float s);
	FORCEINLINE Vector& operator/=(const Vector& v);
	FORCEINLINE Vector& operator/=(float s);
	FORCEINLINE Vector& operator+=(float fl); ///< broadcast add
	FORCEINLINE Vector& operator-=(float fl); ///< broadcast sub*/			

// negate the vector components
	void	Negate();

	// Get the vector's magnitude.
	inline float	Length() const;

	// Get the vector's magnitude squared.
	/*FORCEINLINE float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x * x + y * y + z * z);
	}*/

	// return true if this vector is (0,0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	float	NormalizeInPlace();
	Vector	Normalized() const;
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// check if a vector is within the box defined by two other vectors
	/*FORCEINLINE bool WithinAABox(Vector const& boxmin, Vector const& boxmax);*/

	// Get the distance from this vector to the other one.
	float	DistTo(const Vector& vOther) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' inline.  
	// may be able to tidy this up after switching to VC7
	/*FORCEINLINE float DistToSqr(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}*/

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void	MulAdd(const Vector& a, const Vector& b, float scalar);

	// Dot product.
	float	Dot(const Vector& vOther) const;

	// assignment
	Vector& operator=(const Vector& vOther);

	// 2d
	float	Length2D(void) const;
	float	Length2DSqr(void) const;

	/*operator VectorByValue& () { return *((VectorByValue*)(this)); }*/
	/*operator const VectorByValue& () const { return *((const VectorByValue*)(this)); }*/

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
//	Vector(const Vector &vOther);

	// arithmetic operations
	Vector	operator-(void) const;

	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;

	// Cross product between two vectors.
	Vector	Cross(const Vector& vOther) const;

	// Returns a vector with the min or max in X, Y, and Z.
	Vector	Min(const Vector& vOther) const;
	Vector	Max(const Vector& vOther) const;

#else

private:
	// No copy constructors allowed if we're in optimal mode
	Vector(const Vector& vOther);
#endif
};

class QAngle
{
public:
	float x, y, z;
};