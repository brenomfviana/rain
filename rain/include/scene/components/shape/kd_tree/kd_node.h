#ifndef _KDNODE_H_
#define _KDNODE_H_

#include <vector>
#include "ray.h"
#include "vec3.h"
#include "scene/components/hit_record.h"
#include "scene/components/shape/triangle.h"
#include "scene/components/shape/box.h"

using namespace utils;

/*!
 * This class represents a KD node.
 */
class KDNode {

    public:
        // Nodes
        KDNode* left;
        KDNode* right;
        // Bounding box
        Box* bbox;
        // Triangles of this node
        std::vector<Triangle*> ts;

        /*!
         * KD node constructor.
         */
        KDNode();

        /*!
         * KD node builder.
         */
        KDNode* build(std::vector<Triangle*>& ts, int depth) const;

        /*!
         * Check if the ray has hit some triangle. Returns true if the ray has hit
         * and false otherwise.
         *
         * @param node KDNode
         * @param r Ray
         * @param t_min
         * @param t_max
         * @param hr Hit record
         *
         * @return True if the ray has hit the shape and false otherwise
         */
        bool hit(KDNode* node, Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) const;
};

#endif /* _KDNODE_H_ */
