#include "Matrix4x4.hpp"

const Vector4 EMPTY_VECTOR4(0.0f,0.0f,0.0f,0.0f);
Matrix4x4::Matrix4x4()
{
	m_iBasis = EMPTY_VECTOR4;
	m_jBasis = EMPTY_VECTOR4;
	m_kBasis = EMPTY_VECTOR4;
	m_translation = EMPTY_VECTOR4;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4::Matrix4x4( const Matrix4x4& copy )
{
	*this = copy;
}

///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4::Matrix4x4(const Vector2& iBasis, const Vector2& jBasis)
{
	m_iBasis = EMPTY_VECTOR4;
	m_jBasis = EMPTY_VECTOR4;
	m_kBasis = EMPTY_VECTOR4;
	m_translation = EMPTY_VECTOR4;
	m_iBasis.SetVector2InVector4(iBasis);
	m_jBasis.SetVector2InVector4(jBasis);
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4::Matrix4x4(const Vector2& iBasis, const Vector2& jBasis, const Vector2& translation)
{
	m_iBasis = EMPTY_VECTOR4;
	m_jBasis = EMPTY_VECTOR4;
	m_kBasis = EMPTY_VECTOR4;
	m_translation = EMPTY_VECTOR4;
	m_iBasis.SetVector2InVector4(iBasis);
	m_jBasis.SetVector2InVector4(jBasis);
	m_translation.SetVector2InVector4(translation);
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4::Matrix4x4(const Vector3& iBasis, const Vector3& jBasis, const Vector3& kBasis)
{
	m_iBasis = EMPTY_VECTOR4;
	m_jBasis = EMPTY_VECTOR4;
	m_kBasis = EMPTY_VECTOR4;
	m_translation = EMPTY_VECTOR4;
	m_iBasis.SetVector3InVector4(iBasis);
	m_jBasis.SetVector3InVector4(jBasis);
	m_kBasis.SetVector3InVector4(kBasis);
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4::Matrix4x4(const Vector3& iBasis, const Vector3& jBasis, const Vector3& kBasis, const Vector3& translation)
{
	m_iBasis = EMPTY_VECTOR4;
	m_jBasis = EMPTY_VECTOR4;
	m_kBasis = EMPTY_VECTOR4;
	m_translation = EMPTY_VECTOR4;
	m_iBasis.SetVector3InVector4(iBasis);
	m_jBasis.SetVector3InVector4(jBasis);
	m_kBasis.SetVector3InVector4(kBasis);
	m_translation.SetVector3InVector4(translation);
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4::Matrix4x4(const Vector4& iBasis, const Vector4& jBasis, const Vector4& kBasis, const Vector4& translation)
{
	m_iBasis = iBasis;
	m_jBasis = jBasis;
	m_kBasis = kBasis;
	m_translation =translation;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4::~Matrix4x4()
{

}
///------------------------------------------------------
///
///------------------------------------------------------

const float* Matrix4x4::GetAsFloatArray() const
{
	return &m_iBasis.x;
}
///------------------------------------------------------
///
///------------------------------------------------------

float* Matrix4x4::GetAsFloatArray()
{
	return &m_iBasis.x;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::MakeIdentity()
{
	m_iBasis = EMPTY_VECTOR4;
	m_jBasis = EMPTY_VECTOR4;
	m_kBasis = EMPTY_VECTOR4;
	m_translation = EMPTY_VECTOR4;
	m_iBasis.x = 1.0f;
	m_jBasis.y = 1.0f;
	m_kBasis.z = 1.0f;
	m_translation.w = 1.0f;
}
///------------------------------------------------------
///
///------------------------------------------------------

void* Matrix4x4::operator = (const Matrix4x4 &copy)
{
	m_iBasis = copy.m_iBasis;
	m_jBasis = copy.m_jBasis;
	m_kBasis = copy.m_kBasis;
	m_translation = copy.m_translation;
	return this;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::Transform(Matrix4x4& transformMatrix)
{
	Matrix4x4 afterTransformedMatrix;
	afterTransformedMatrix.m_iBasis = Vector4(transformMatrix.m_iBasis.x,transformMatrix.m_jBasis.x,transformMatrix.m_kBasis.x,transformMatrix.m_translation.x);
	afterTransformedMatrix.m_jBasis = Vector4(transformMatrix.m_iBasis.y, transformMatrix.m_jBasis.y, transformMatrix.m_kBasis.y, transformMatrix.m_translation.y);
	afterTransformedMatrix.m_kBasis = Vector4(transformMatrix.m_iBasis.z, transformMatrix.m_jBasis.z, transformMatrix.m_kBasis.z, transformMatrix.m_translation.z);
	afterTransformedMatrix.m_translation = Vector4(transformMatrix.m_iBasis.w, transformMatrix.m_jBasis.w, transformMatrix.m_kBasis.w, transformMatrix.m_translation.w);
	m_iBasis = afterTransformedMatrix.m_iBasis;
	m_jBasis = afterTransformedMatrix.m_jBasis;
	m_kBasis = afterTransformedMatrix.m_kBasis;
	m_translation = afterTransformedMatrix.m_translation;
}
///------------------------------------------------------
///
///------------------------------------------------------

const Matrix4x4 Matrix4x4::GetTransformed(Matrix4x4& transformMatrix)
{
	Matrix4x4 afterTransformedMatrix(m_iBasis,m_jBasis,m_kBasis,m_translation);
	afterTransformedMatrix.Transform(transformMatrix);
	return afterTransformedMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector2 Matrix4x4::TransformPosition( const Vector2& position2D ) const // Hardcoded to assume z=0, w=1
{
	Vector2 vector2AfterTransformed;
	vector2AfterTransformed.x = m_iBasis.x * position2D.x + m_iBasis.y * position2D.y + m_translation.x;
	vector2AfterTransformed.y = m_jBasis.x * position2D.x + m_jBasis.y * position2D.y + m_translation.y;
	return vector2AfterTransformed;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector3 Matrix4x4::TransformPosition( const Vector3& position3D ) const // Hardcoded to assume w=1
{
	Vector3 vector3AfterTransformed;
	vector3AfterTransformed.x = m_iBasis.x * position3D.x + m_iBasis.y * position3D.y + m_iBasis.z * position3D.z + m_translation.x;
	vector3AfterTransformed.y = m_jBasis.x * position3D.x + m_jBasis.y * position3D.y + m_jBasis.z * position3D.z + m_translation.y;
	vector3AfterTransformed.z = m_kBasis.x * position3D.x + m_kBasis.y * position3D.y + m_kBasis.z * position3D.z + m_translation.z;
	return vector3AfterTransformed;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector2 Matrix4x4::TransformDirection( const Vector2& direction2D ) const // Hardcoded to assume z=0, w=0
{
	Vector2 vector2AfterTransformed;
	vector2AfterTransformed.x = m_iBasis.x * direction2D.x + m_iBasis.y * direction2D.y;
	vector2AfterTransformed.y = m_jBasis.x * direction2D.x + m_jBasis.y * direction2D.y;
	return vector2AfterTransformed;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector3 Matrix4x4::TransformDirection( const Vector3& direction3D ) const // Hardcoded to assume w=0
{
	Vector3 vector3AfterTransformed;
	vector3AfterTransformed.x = m_iBasis.x * direction3D.x + m_iBasis.y * direction3D.y + m_iBasis.z * direction3D.z;
	vector3AfterTransformed.y = m_jBasis.x * direction3D.x + m_jBasis.y * direction3D.y + m_jBasis.z * direction3D.z;	
	vector3AfterTransformed.z = m_kBasis.x * direction3D.x + m_kBasis.y * direction3D.z + m_kBasis.z * direction3D.z;
	return vector3AfterTransformed;
}
///------------------------------------------------------
///
///------------------------------------------------------

Vector4 Matrix4x4::TransformVector( const Vector4& homogeneousVector ) const // w is provided
{
	Vector4 vector4AfterTransformed;
	vector4AfterTransformed.x = m_iBasis.x * homogeneousVector.x + m_jBasis.x * homogeneousVector.y 
							+ m_kBasis.x * homogeneousVector.z + m_translation.x *homogeneousVector.w;
	vector4AfterTransformed.y = m_iBasis.y * homogeneousVector.x + m_jBasis.y * homogeneousVector.y 
							+ m_kBasis.y * homogeneousVector.z + m_translation.y *homogeneousVector.w;
	vector4AfterTransformed.z = m_iBasis.z * homogeneousVector.x + m_jBasis.z * homogeneousVector.y 
							+ m_kBasis.z * homogeneousVector.z + m_translation.z *homogeneousVector.w;
	vector4AfterTransformed.w = m_iBasis.w * homogeneousVector.x + m_jBasis.w * homogeneousVector.y 
							+ m_kBasis.w * homogeneousVector.z + m_translation.w *homogeneousVector.w;
	return vector4AfterTransformed;
}
///-----------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::Translate( const Vector2& translation2D ) // z translation assumed to be 0
{
	this->MakeIdentity();
	m_translation.x = translation2D.x;
	m_translation.y = translation2D.y;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::Translate( const Vector3& translation3D )
{
	this->MakeIdentity();
	m_translation.x = translation3D.x;
	m_translation.y = translation3D.y;
	m_translation.z = translation3D.z;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::Scale( float uniformScale )
{
	this->MakeIdentity();
	m_iBasis.x = uniformScale;
	m_jBasis.y = uniformScale;
	m_kBasis.z = uniformScale;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::Scale( const Vector2& nonUniformScale2D ) // z scale assumed to be 1
{
	this->MakeIdentity();
	m_iBasis.x = nonUniformScale2D.x;
	m_jBasis.y = nonUniformScale2D.y;
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::Scale( const Vector3& nonUniformScale3D )
{
	this->MakeIdentity();
	m_iBasis.x = nonUniformScale3D.x;
	m_jBasis.y = nonUniformScale3D.y;
	m_kBasis.z = nonUniformScale3D.z;
}
void Matrix4x4::RotateDegreesAboutX( float degrees )
{
	float radians = degrees * DEG2RAD;
	this->MakeIdentity();
	m_jBasis.y = (float)cos(radians);
	m_jBasis.z = (float)sin(radians);
	m_kBasis.y = -(float)sin(radians);
	m_kBasis.z = (float)cos(radians);
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::RotateDegreesAboutY( float degrees )
{
	float radians = degrees * DEG2RAD;
	this->MakeIdentity();
	m_iBasis.x = (float)cos(radians);
	m_iBasis.z = -(float)sin(radians);
	m_kBasis.x = (float)sin(radians);
	m_kBasis.z = (float)cos(radians);
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::RotateDegreesAboutZ( float degrees )// Possibly also offered as RotateDegrees2D
{
	float radians = degrees * DEG2RAD;
	this->MakeIdentity();
	m_iBasis.x = (float)cos(radians);
	m_iBasis.y = (float)sin(radians);
	m_jBasis.x = -(float)sin(radians);
	m_jBasis.y = (float)cos(radians);
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::RotateRadiansAboutX( float radians )
{
	this->MakeIdentity();
	m_jBasis.y = (float)cos(radians);
	m_jBasis.z = (float)sin(radians);
	m_kBasis.y = -(float)sin(radians);
	m_kBasis.z = (float)cos(radians);
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::RotateRadiansAboutY( float radians )
{
	this->MakeIdentity();
	m_iBasis.x = (float)cos(radians);
	m_iBasis.z = -(float)sin(radians);
	m_kBasis.x = (float)sin(radians);
	m_kBasis.z = (float)cos(radians);
}
///------------------------------------------------------
///
///------------------------------------------------------

void Matrix4x4::RotateRadiansAboutZ( float radians )// Possibly also offered as RotateRadians2D
{
	this->MakeIdentity();
	m_iBasis.x = (float)cos(radians);
	m_iBasis.y = (float)sin(radians);
	m_jBasis.x = -(float)sin(radians);
	m_jBasis.y = (float)cos(radians);
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4:: CreateTranslation( const Vector2& translation2D )
{
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_translation.x = translation2D.x;
	newMatrix.m_translation.y = translation2D.y;
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateTranslation( const Vector3& translation3D )
{
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_translation.x = translation3D.x;
	newMatrix.m_translation.y = translation3D.y;
	newMatrix.m_translation.z = translation3D.z;
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateScale( float uniformScale )
{
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_iBasis.x = uniformScale;
	newMatrix.m_jBasis.y = uniformScale;
	newMatrix.m_kBasis.z = uniformScale;
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateScale( const Vector2& nonUniformScale2D )
{
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_iBasis.x = nonUniformScale2D.x;
	newMatrix.m_jBasis.y = nonUniformScale2D.y;
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateScale( const Vector3& nonUniformScale3D )
{
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_iBasis.x = nonUniformScale3D.x;
	newMatrix.m_jBasis.y = nonUniformScale3D.y;
	newMatrix.m_kBasis.z = nonUniformScale3D.z;
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateRotationDegreesAboutX( float degrees )
{
	float radians = degrees * DEG2RAD;
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_jBasis.y = (float)cos(radians);
	newMatrix.m_jBasis.z = (float)sin(radians);
	newMatrix.m_kBasis.y = -(float)sin(radians);
	newMatrix.m_kBasis.z = (float)cos(radians);
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateRotationDegreesAboutY( float degrees )
{
	float radians = degrees * DEG2RAD;
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_iBasis.x = (float)cos(radians);
	newMatrix.m_iBasis.z = -(float)sin(radians);
	newMatrix.m_kBasis.x = (float)sin(radians);
	newMatrix.m_kBasis.z = (float)cos(radians);
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateRotationDegreesAboutZ( float degrees )
{
	float radians = degrees * DEG2RAD;
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_iBasis.x = (float)cos(radians);
	newMatrix.m_iBasis.y = (float)sin(radians);
	newMatrix.m_jBasis.x = -(float)sin(radians);
	newMatrix.m_jBasis.y = (float)cos(radians);
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateRotationRadiansAboutX( float radians )
{
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_jBasis.y = (float)cos(radians);
	newMatrix.m_jBasis.z = (float)sin(radians);
	newMatrix.m_kBasis.y = -(float)sin(radians);
	newMatrix.m_kBasis.z = (float)cos(radians);
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateRotationRadiansAboutY( float radians )
{
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_iBasis.x = (float)cos(radians);
	newMatrix.m_iBasis.z = -(float)sin(radians);
	newMatrix.m_kBasis.x = (float)sin(radians);
	newMatrix.m_kBasis.z = (float)cos(radians);
	return newMatrix;
}
///------------------------------------------------------
///
///------------------------------------------------------

Matrix4x4 Matrix4x4::CreateRotationRadiansAboutZ( float radians )
{
	Matrix4x4 newMatrix;
	newMatrix.MakeIdentity();
	newMatrix.m_iBasis.x = (float)cos(radians);
	newMatrix.m_iBasis.y = (float)sin(radians);
	newMatrix.m_jBasis.x = -(float)sin(radians);
	newMatrix.m_jBasis.y = (float)cos(radians);
	return newMatrix;
}

void Matrix4x4::Mult(const Matrix4x4& l, const Matrix4x4& r, Matrix4x4& res)
{
	Matrix4x4 leftHand;
	Matrix4x4 rightHand;

	//	matrix()
	//	{
	//	i	_m[0] = 1.0; _m[1] = 0.0; _m[2] = 0.0; _m[3] = 0.0;
	//	j	_m[4] = 0.0; _m[5] = 1.0; _m[6] = 0.0; _m[7] = 0.0;
	//	k	_m[8] = 0.0; _m[9] = 0.0; _m[10] =1.0; _m[11] =0.0;
	//	t	_m[12] = 0.0; _m[13] = 0.0; _m[14] = 0.0; _m[15] = 1.0;
	//		i				j			k				
	//	}

	assert(&l != &res && &r != &res);//prevent in-place overwrites
	//assume that the arguments are valid float[16] buffers
	res.m_iBasis.x = l.m_iBasis.x * r.m_iBasis.x + l.m_iBasis.y * r.m_jBasis.x + l.m_iBasis.z * r.m_kBasis.x + l.m_iBasis.w* r.m_translation.x;
	res.m_iBasis.y = l.m_iBasis.x * r.m_iBasis.y + l.m_iBasis.y * r.m_jBasis.y + l.m_iBasis.z * r.m_kBasis.y + l.m_iBasis.w* r.m_translation.y;
	res.m_iBasis.z = l.m_iBasis.x * r.m_iBasis.z + l.m_iBasis.y * r.m_jBasis.z + l.m_iBasis.z * r.m_kBasis.z + l.m_iBasis.w *r.m_translation.z;
	res.m_iBasis.w = l.m_iBasis.x * r.m_iBasis.w + l.m_iBasis.y * r.m_jBasis.w + l.m_iBasis.z * r.m_kBasis.w + l.m_iBasis.w *r.m_translation.w;

	res.m_jBasis.x = l.m_jBasis.x *  r.m_iBasis.x + l.m_jBasis.y * r.m_jBasis.x + l.m_jBasis.z * r.m_kBasis.x + l.m_jBasis.w * r.m_translation.x;
	res.m_jBasis.y = l.m_jBasis.x *  r.m_iBasis.y + l.m_jBasis.y * r.m_jBasis.y + l.m_jBasis.z * r.m_kBasis.y + l.m_jBasis.w * r.m_translation.y;
	res.m_jBasis.z = l.m_jBasis.x *  r.m_iBasis.z + l.m_jBasis.y * r.m_jBasis.z + l.m_jBasis.z * r.m_kBasis.z + l.m_jBasis.w * r.m_translation.z;
	res.m_jBasis.w = l.m_jBasis.x *  r.m_iBasis.w + l.m_jBasis.y * r.m_jBasis.w + l.m_jBasis.z * r.m_kBasis.w + l.m_jBasis.w * r.m_translation.w;

	res.m_kBasis.x = l.m_kBasis.x *  r.m_iBasis.x + l.m_kBasis.y * r.m_jBasis.x + l.m_kBasis.z * r.m_kBasis.x + l.m_kBasis.w * r.m_translation.x;
	res.m_kBasis.y = l.m_kBasis.x *  r.m_iBasis.y + l.m_kBasis.y * r.m_jBasis.y + l.m_kBasis.z * r.m_kBasis.y + l.m_kBasis.w * r.m_translation.y;
	res.m_kBasis.z = l.m_kBasis.x *  r.m_iBasis.z + l.m_kBasis.y * r.m_jBasis.z + l.m_kBasis.z * r.m_kBasis.z + l.m_kBasis.w * r.m_translation.z;
	res.m_kBasis.w = l.m_kBasis.x *  r.m_iBasis.w + l.m_kBasis.y * r.m_jBasis.w + l.m_kBasis.z * r.m_kBasis.w + l.m_kBasis.w * r.m_translation.w;

	res.m_translation.x = l.m_translation.x *  r.m_iBasis.x + l.m_translation.y * r.m_jBasis.x + l.m_translation.z * r.m_kBasis.x + l.m_translation.w* r.m_translation.x;
	res.m_translation.y = l.m_translation.x *  r.m_iBasis.y + l.m_translation.y * r.m_jBasis.y + l.m_translation.z * r.m_kBasis.y + l.m_translation.w* r.m_translation.y;
	res.m_translation.z = l.m_translation.x *  r.m_iBasis.z + l.m_translation.y * r.m_jBasis.z + l.m_translation.z * r.m_kBasis.z + l.m_translation.w * r.m_translation.z;
	res.m_translation.w = l.m_translation.x *  r.m_iBasis.w + l.m_translation.y * r.m_jBasis.w + l.m_translation.z * r.m_kBasis.w + l.m_translation.w * r.m_translation.w;
}
//////////////////////////////////////////////////////////////////////////
void Matrix4x4::Transpose()
{
	Matrix4x4 afterTransformedMatrix;
	afterTransformedMatrix.m_iBasis = Vector4(m_iBasis.x,m_jBasis.x, m_kBasis.x, m_translation.x);
	afterTransformedMatrix.m_jBasis = Vector4(m_iBasis.y,m_jBasis.y, m_kBasis.y, m_translation.y);
	afterTransformedMatrix.m_kBasis = Vector4(m_iBasis.z,m_jBasis.z, m_kBasis.z, m_translation.z);
	afterTransformedMatrix.m_translation = Vector4(m_iBasis.w,m_jBasis.w, m_kBasis.w, m_translation.w);
	m_iBasis = afterTransformedMatrix.m_iBasis;
	m_jBasis = afterTransformedMatrix.m_jBasis;
	m_kBasis = afterTransformedMatrix.m_kBasis;
	m_translation = afterTransformedMatrix.m_translation;
}

const Matrix4x4 Matrix4x4::I(Vector4(1.0f,0.0f,0.0f,0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f));
