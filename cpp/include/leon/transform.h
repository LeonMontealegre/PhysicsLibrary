#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "vector.h"
#include "matrix.h"
#include "matrices.h"

class Transform {
public:
    Transform(const Matrix4f& m);
    Transform(const Vec3f& pos   = Vecf(0,0,0), const Vec3f& rot = Vecf(0,0,0),
              const Vec3f& scale = Vecf(1,1,1));

    Transform& translate(float dx, float dy, float dz);
    Transform& translate(const Vec3f& dv) { return translate(dv[0], dv[1], dv[2]); }

    Transform& rotate(float rx, float ry, float rz);
    Transform& rotate(const Vec3f& rv) { return rotate(rv[0], rv[1], rv[2]); }

    Transform& scale(float sx, float sy, float sz);
    Transform& scale(const Vec3f& sv)  { return scale(sv[0], sv[1], sv[2]); }
    Transform& scale(float s)          { return scale(s, s, s); }

    Transform& set_pos(float x, float y, float z);
    Transform& set_pos(const Vec3f& v) { return set_pos(v[0], v[1], v[2]); }

    Matrix4f operator * () const;

    const Vec3f& get_pos() const { return translation; }

private:
    Matrix4f mat;
    Vec3f translation;
};

Transform::Transform(const Matrix4f& m) {
    mat = m;
}

Transform::Transform(const Vec3f& pos, const Vec3f& rot, const Vec3f& scale): mat(1) {
    this->translate(pos);
    this->rotate(rot);
    this->scale(scale);
}

Transform& Transform::translate(float dx, float dy, float dz) {
    mat = mat * translate_mat(dx, dy, dz);
    translation += Vecf(dx, dy, dz);
    return *this;
}

Transform& Transform::rotate(float rx, float ry, float rz) {
    if (rx != 0) mat = mat * rotate_x_mat(rx);
    if (ry != 0) mat = mat * rotate_y_mat(ry);
    if (rz != 0) mat = mat * rotate_z_mat(rz);
    return *this;
}

Transform& Transform::scale(float sx, float sy, float sz) {
    mat = mat * scale_mat(sx, sy, sz);
    return *this;
}

Transform& Transform::set_pos(float x, float y, float z) {
    mat[3][0] = x;
    mat[3][1] = y;
    mat[3][2] = z;
    translation = Vecf(x, y, z);
    return *this;
}

Matrix4f Transform::operator * () const {
    return mat;
}


#endif