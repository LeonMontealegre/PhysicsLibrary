#ifndef __TEXTURE_COMPOSITOR_H__
#define __TEXTURE_COMPOSITOR_H__

#include <queue>

#include "../../types.h"
#include "../../log.h"

#include "texture_data.h"
#include "texture_atlas.h"

class TextureCompositor {
public:
    static void put(TextureData* tex) {
        data.push(tex);
    }

    static TextureAtlas* composite() {
        if (root)
            cleanup();
        root = new Node({false, 0, 0, data.top()->width, data.top()->height, NULL, NULL});

        std::vector<std::pair<TextureData*, Node*>> textures;

        while (data.size() > 0) {
            TextureData* tex = data.top();
            data.pop();

            Node* fit = NULL;
            Node* node = find_node(root, tex->width, tex->height);
            if (node)
                fit = split_node(node, tex->width, tex->height);
            else
                fit = grow(tex->width, tex->height);

            if (fit)
                textures.push_back(std::make_pair(tex, fit));
        }

        TextureAtlas* atlas = new TextureAtlas();
        TextureData* composite = new TextureData("", root->w, root->h, 4, new unsigned char[root->w * root->h * 4]);

        for (std::pair<TextureData*, Node*> tex : textures) {
            TextureData* dat = tex.first;
            Node* n = tex.second;

            composite->fill(n->x, n->y, *dat);
            atlas->put(dat->name, {{n->x, n->y}, {n->w, n->h}});
        }

        atlas->set_data(composite);

        return atlas;
    }

private:
    struct Node {
        bool used;
        const uint x, y, w, h;
        Node *down, *right;
    };
    class Compare {
    public:
        bool operator () (const TextureData* a, const TextureData* b) {
            if (std::max(b->width, b->height) == std::max(a->width, a->height)) {
                if (std::min(b->width, b->height) == std::min(a->width, a->height)) {
                    if (b->height == a->height)
                        return b->width > a->width;
                    return b->height > a->height;
                }
                return std::min(b->width, b->height) > std::min(a->width, a->height);
            }
            return std::max(b->width, b->height) > std::max(a->width, a->height);
        }
    };

    static Node* root;
    static std::priority_queue<TextureData*, std::vector<TextureData*>, Compare> data;
    static std::vector<Node*> all_nodes;


    static Node* split_node(Node* node, uint w, uint h) {
        node->used = true;
        node->down  = new Node({false, node->x, node->y + h, node->w, node->h - h, NULL, NULL});
        node->right = new Node({false, node->x + w, node->y, node->w - w, node->h, NULL, NULL});

        all_nodes.push_back(node->down);
        all_nodes.push_back(node->right);

        return node;
    }
    static Node* find_node(Node* root, uint w, uint h) {
        if (root->used) {
            Node* nr = find_node(root->right, w, h);
            if (nr)
                return nr;
            else
                return find_node(root->down, w, h);
        } else if ((w <= root->w) && (h <= root->h)) {
            return root;
        }
        return NULL;
    }


    static Node* grow(uint w, uint h) {
        bool can_grow_down  = (w <= root->w);
        bool can_grow_right = (h <= root->h);

        if (!can_grow_down && !can_grow_right) {
            log_e("Can't grow anywhere! (Hit texture larger then expected)\n");
            return NULL;
        }

        bool should_grow_down  = can_grow_down  && (root->w >= (root->h + h));
        bool should_grow_right = can_grow_right && (root->h >= (root->w + w));

        if (should_grow_right)
            return grow_right(w, h);
        if (should_grow_down)
            return grow_down(w, h);
        if (can_grow_right)
            return grow_right(w, h);
        if (can_grow_down)
            return grow_down(w, h);
        return NULL;
    }
    static Node* grow_right(uint w, uint h) {
        Node* right = new Node({false, root->w, 0, w, root->h, NULL, NULL});
        Node* new_root = new Node({true, 0, 0, root->w + w, root->h, root, right});
        root = new_root;

        all_nodes.push_back(right);
        all_nodes.push_back(new_root);

        Node* node = find_node(root, w, h);
        if (node)
            return split_node(node, w, h);
        else
            return NULL;
    }
    static Node* grow_down(uint w, uint h) {
        Node* down = new Node({false, 0, root->h, root->w, h, NULL, NULL});
        Node* new_root = new Node({true, 0, 0, root->w, root->h + h, down, root});
        root = new_root;

        all_nodes.push_back(down);
        all_nodes.push_back(new_root);

        Node* node = find_node(root, w, h);
        if (node)
            return split_node(node, w, h);
        else
            return NULL;
    }

    static void cleanup() {
        for (Node* n : all_nodes)
            delete n;
        all_nodes.clear();
    }
};


TextureCompositor::Node* TextureCompositor::root;
std::priority_queue<TextureData*, std::vector<TextureData*>, TextureCompositor::Compare> TextureCompositor::data;
std::vector<TextureCompositor::Node*> TextureCompositor::all_nodes;

#endif