#include "scene/components/shape/kd_tree/kd_node.h"

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
    // Get bounding box surrounding all the triangle
    node->bbox = ts[0]->get_bounding_box();
    for (Triangle* t : ts) {
        node->bbox->expand(t->get_bounding_box());
    }
    // Get midpoint
    Point3 midpt;
    for (Triangle* t : ts) {
        midpt += (t->get_midpoint() * (1.f / ts.size()));
    }
    //
    std::vector<Triangle*> left_ts;
    std::vector<Triangle*> right_ts;
    int axis = node->bbox->longest_axis();
    for (Triangle* t : ts) {
        // Choose axis
        switch (axis) {
            case 0:
                if (midpt.x() >= t->get_midpoint().x()) {
                    right_ts.push_back(t);
                } else {
                    left_ts.push_back(t);
                }
                break;
            case 1:
                if (midpt.y() >= t->get_midpoint().y()) {
                    right_ts.push_back(t);
                } else {
                    left_ts.push_back(t);
                }
                break;
            case 2:
                if (midpt.z() >= t->get_midpoint().z()) {
                    right_ts.push_back(t);
                } else {
                    left_ts.push_back(t);
                }
                break;
        }
    }
    node->left = build(left_ts, depth + 1);
    node->right = build(right_ts, depth + 1);
    return node;
}

bool KDNode::hit(KDNode* node, Ray r, Vec3::RealType t_min, Vec3::RealType t_max,
        HitRecord& hr) const {
    // Check if the ray intersects the bounding box of the given node
    if (node->bbox->hit(r, t_min, t_max, hr)) {
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
    return false;
}
