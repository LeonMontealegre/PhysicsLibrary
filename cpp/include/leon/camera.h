#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <leon/linalg.h>
#include <leon/print_utils.h>
#include "matrix.h"
#include "matrices.h"
#include "transform.h"

class Camera {
public:
    Camera(const Matrix4f& proj_mat_, const Transform& transform_ = Transform(), const Vec3f& origin_ = Vec3f());

    void set_origin(const Vec3f& origin_);

    // Vec3f forward() const;
    // Vec3f right() const;
    // Vec3f up() const;

    Transform& get_transform();

    const Matrix4f& get_proj_mat() const;
    const Vec3f& get_origin() const;

private:
    Matrix4f proj_mat;
    Transform transform;
    Vec3f origin;
};

Camera::Camera(const Matrix4f& proj_mat_, const Transform& transform_, const Vec3f& origin_):
               proj_mat(proj_mat_), transform(transform_), origin(origin_) {}

void Camera::set_origin(const Vec3f& origin_) {
    origin = origin_;
}

// Vec3f Camera::forward() const {
//     Matrix4f m0 = *transform;
//     Matrix4f m = invert(m0);
//     Vec3f p = transform.get_pos();
//     Vec4f v = Vecf(p[0], p[1], p[2], 0);
//     std::cout << (m0 * m) << std::endl;
//     Vec4f v2 = m * v;
//     return Vecf(v2[0], v2[1], v2[2]).norm();
// }

// Vec3f Camera::right() const {
//     return cross(Vecf(0, 1, 0), forward());
// }

// Vec3f Camera::up() const {
//     return cross(forward(), right());
// }

Transform& Camera::get_transform() {
    return transform;
}

const Matrix4f& Camera::get_proj_mat() const {
    return proj_mat;
}

#endif