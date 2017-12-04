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
    // If this node does not have any triangle
    if (ts.size() == 0) {
        return node;
    }
    // If this node has a triangle
    if (ts.size() == 1) {
        node->left = new KDNode();
        node->right = new KDNode();
        node->left->ts = std::vector<Triangle*>();
        node->right->ts = std::vector<Triangle*>();
        return node;
    }
    // Get midpoint
    Point3 midpt;
    for (int i = 1; i < ts.size(); i++) {
        midpt += (ts[i]->get_midpoint() * (1.f / ts.size()));
    }
    //
    std::vector<Triangle*> left_ts;
    std::vector<Triangle*> right_ts;
    //
    if ((left_ts.size() == 0) && (right_ts.size() > 0)) {
        left_ts = right_ts;
    }
    //
    if ((right_ts.size() == 0) && (left_ts.size() > 0)) {
        right_ts = left_ts;
    }
    // If 50% of triangles match, do not subdivide any more
    int matches = 0;
    for (int i = 0; i < left_ts.size(); i++) {
        for (int j = 0; j < right_ts.size(); j++) {
            if (left_ts[i] == right_ts[j]) {
                matches++;
            }
        }
    }
    //
    if (((((float) matches) / left_ts.size()) < 0.5) &&
        ((((float) matches) / right_ts.size()) < 0.5)) {
            node->left = build(left_ts, depth + 1);
            node->right = build(right_ts, depth + 1);
    } else {
        node->left = new KDNode();
        node->right = new KDNode();
        node->left->ts = std::vector<Triangle*>();
        node->right->ts = std::vector<Triangle*>();
    }
    return node;
}

bool KDNode::hit(KDNode* node, Ray r, Vec3::RealType t_min, Vec3::RealType t_max, HitRecord& hr) const {
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
    return false;
}
