#include "scene/components/shape/kd_tree/kd_node.h"

bool sort_x(Triangle* t1, Triangle* t2){
    return t1->get_midpoint().x() < t2->get_midpoint().x();
}

bool sort_y(Triangle* t1, Triangle* t2){
    return t1->get_midpoint().y() < t2->get_midpoint().y();
}

bool sort_z(Triangle* t1, Triangle* t2){
    return t1->get_midpoint().z() < t2->get_midpoint().z();
}

KDNode::KDNode() {
    /* empty */
}

KDNode* KDNode::build(std::vector<Triangle*>& ts, int depth) const {
    //
    KDNode* node = new KDNode();
    node->ts = ts;
    node->left = NULL;
    node->right = NULL;
    node->bbox = NULL;
    // If this node does not have any triangle
    if (ts.size() == 0) {
        return node;
    }
    // If this node has a triangle
    if (ts.size() == 1) {
        node->bbox = ts[0]->get_bounding_box();
        node->left = new KDNode();
        node->right = new KDNode();
        node->left->ts = std::vector<Triangle*>();
        node->right->ts = std::vector<Triangle*>();
        return node;
    }
    //
    std::vector<Triangle*> left_ts = std::vector<Triangle*>();
    std::vector<Triangle*> right_ts = std::vector<Triangle*>();
    int axis = depth % 3;
    // Choose axis
    switch (axis) {
        case 0:
            std::sort(ts.begin(), ts.end(), sort_x);
            break;
        case 1:
            std::sort(ts.begin(), ts.end(), sort_y);
            break;
        case 2:
            std::sort(ts.begin(), ts.end(), sort_z);
            break;
    }

    // Build box
    Vec3::RealType inf = std::numeric_limits<Vec3::RealType>::infinity();
    Vec3::RealType xmin = inf, xmax = -inf;
    Vec3::RealType ymin = inf, ymax = -inf;
    Vec3::RealType zmin = inf, zmax = -inf;
    for (Triangle* t : ts) {
        Box* b = t->get_bounding_box();
        xmin = std::min(b->o.x(), xmin);
        ymin = std::min(b->o.y(), ymin);
        zmin = std::min(b->o.z(), zmin);
        xmax = std::max(b->end.x(), xmax);
        ymax = std::max(b->end.y(), ymax);
        zmax = std::max(b->end.z(), zmax);
    }
    Point3 bbox_origin = Point3(xmin, ymin, zmin);
    Vec3::RealType bbox_xsize = (bbox_origin - Vec3(xmax, ymin, zmin)).length();
    Vec3::RealType bbox_ysize = (bbox_origin - Vec3(xmin, ymax, zmin)).length();
    Vec3::RealType bbox_zsize = (bbox_origin - Vec3(xmin, ymin, zmax)).length();
    Vec3 bbox_size = Vec3(bbox_xsize, bbox_ysize, bbox_zsize);
    node->bbox = new Box(bbox_origin, bbox_size);

    int midlist = ts.size() / 2;

    for (int i = 0; i < midlist; i++) {
        left_ts.push_back(ts[i]);
    }

    for (int i = midlist; i < ts.size(); i++) {
        right_ts.push_back(ts[i]);
    }

    if (left_ts.size() > 0) {
        node->left = build(left_ts, depth + 1);
    }

    if (right_ts.size() > 0) {
        node->right = build(right_ts, depth + 1);
    }
    return node;
}

bool KDNode::hit(KDNode* node, Ray r, Vec3::RealType t_min, Vec3::RealType t_max,
        HitRecord& hr) const {
    if (node->bbox != NULL) {
        HitRecord shr;
        // Check if the ray intersects the bounding box of the given node
        if (node->bbox->hit(r, t_min, t_max, shr)) {
            // If either child still has triangles recurse down both sides and check for intersections
            if ((node->left->ts.size() > 0) || (node->right->ts.size() > 0)) {
                bool hit_left = hit(node->left, r, t_min, t_max, hr);
                bool hit_right = hit(node->right, r, t_min, t_max, hr);
                return (hit_left || hit_right);
            } else {
                // Ray reached a leaf
                for (Triangle* t : node->ts) {
                    // Check if hit a triangle
                    if (t->hit(r, t_min, t_max, hr)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
