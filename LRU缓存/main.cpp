#include <bits/stdc++.h>
#include <memory>
using namespace std;
struct FXListNode {
    int key;
    int val;
    std::weak_ptr<FXListNode> pre, next;
    FXListNode() {
    }
    FXListNode(int k, int v) {
        key = k;
        val = v;
    }
};
class LRUCache {
public:
    LRUCache(int capacity) {
        head_ = std::make_shared<FXListNode>();
        tail_ = std::make_shared<FXListNode>();
        head_->next = tail_;
        head_->pre = tail_;
        tail_->next = head_;
        tail_->pre = head_;
        capacity_ = capacity;
    }

    ~LRUCache() {
    }

    int get(int key) {
        if (mp_.count(key)) {
            erase(mp_[key]);
            insertAfterHead(mp_[key]);
            return mp_[key]->val;
        } else {
            return -1;
        }
    }

    void put(int key, int value) {
        std::shared_ptr<FXListNode> new_node = std::make_shared<FXListNode>(key, value);
        if (mp_.count(key)) {
            mp_[key]->val = value;
            erase(mp_[key]);
            insertAfterHead(mp_[key]);
            return;
        }
        if (mp_.size() >= capacity_) {
            auto tail_pre = tail_->pre.lock();
            if (tail_pre) {
                mp_.erase(tail_pre->key);
                erase(tail_pre);
            }
        }
        insertAfterHead(new_node);
        mp_[key] = new_node;
    }

private:
    void erase(std::shared_ptr<FXListNode> node) {
        auto pre = node->pre.lock();
        auto next = node->next.lock();
        if (pre && next) {
            pre->next = next;
            next->pre = pre;
        }
    }

    void insertAfterHead(std::shared_ptr<FXListNode> node) {
        auto next = head_->next.lock();
        if (next) {
            node->next = next;
            node->pre = head_;

            next->pre = node;
            head_->next = node;
        }
    }

    std::shared_ptr<FXListNode> head_, tail_;
    std::unordered_map<int, std::shared_ptr<FXListNode>> mp_;
    int capacity_;
};
// 测试shared_ptr循环引用
class B;
class A {
public:
    std::weak_ptr<B> a; // 若改为shared_ptr则会造成循环引用，导致内存泄漏，不会执行A的析构函数
    ~A() {
        std::cout << "A\n";
    }
};
class B {
public:
    std::weak_ptr<A> b; // 若改为shared_ptr则会造成循环引用，导致内存泄漏，不会执行B的析构函数
    ~B() {
        std::cout << "B\n";
    }
};
void solve() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->a = b;
    b->b = a;
}

int main() {
    solve();
    return 0;
}