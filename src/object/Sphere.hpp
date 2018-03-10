#ifndef MYRT_OBJECT_SPHERE_HPP
#define MYRT_OBJECT_SPHERE_HPP

#include "object/AbstractObject.hpp"
#include "hit_record/HitRecord.hpp"

namespace Myrt::Object {

using Myrt::HitRecord::HitRecord;

class Sphere: public AbstractObject {
public:
    Sphere(const vec4& center, float r)
        : mCenter(center), mRadius(r)
    {}

    virtual bool doHit(const ray4& ray, float& tmin, HitRecord& hr) const override {
        float t;
        vec4 tmp = ray.m_orig - mCenter;
        float a = Dot3(ray.m_dir, ray.m_dir);
        float b = Dot3(tmp, ray.m_dir);
        float c = Dot3(tmp, tmp) - mRadius * mRadius;
        float d = b * b - a * c;

        if (d < .0f)
            return false;
        float e = std::sqrt(d);
        float inva = 1.f / a;
        t = (-b - e) * inva;
        if (t > 10e-6f && t < tmin) {
            tmin = t;
            hr.mNormal = Normalize(tmp + t * ray.m_dir);
            hr.mHitPoint = ray.m_orig + t * ray.m_dir;
            hr.mColor = .5f * Color(hr.mNormal.x + 1.f, hr.mNormal.y + 1.f, hr.mNormal.z + 1.f);
            return true;
        }

        t = (-b + e) * inva;
        if (t > 10e-6f && t < tmin) {
            tmin = t;
            hr.mNormal = Normalize(tmp + t * ray.m_dir);
            hr.mHitPoint = ray.m_orig + t * ray.m_dir;
            hr.mColor = .5f * Color(hr.mNormal.x + 1.f, hr.mNormal.y + 1.f, hr.mNormal.z + 1.f);
            return true;
        }

        return false;
    }

private:
    vec4 mCenter;
    float mRadius;
};

} // namespace Myrt::Object

#endif

