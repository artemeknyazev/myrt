#ifndef MYRT_OBJECT_ABSTRACT_OBJECT
#define MYRT_OBJECT_ABSTRACT_OBJECT

#include "hit_record/HitRecord.hpp"

namespace Myrt::Object {

using Myrt::HitRecord::HitRecord;

class AbstractObject;
using ObjectPtr = std::shared_ptr<AbstractObject>;

class AbstractObject {
public:
    bool hit(const ray4& ray, float& tmin, HitRecord& hr) {
        return doHit(ray, tmin, hr);
    }

    virtual ~AbstractObject() = default;

protected:
    virtual bool doHit(const ray4& ray, float& tmin, HitRecord& hr) const = 0;
};

} // namespace Myrt::Object

#endif

