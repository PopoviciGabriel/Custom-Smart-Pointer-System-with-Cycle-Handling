#pragma once
#include <cstddef>
#include <utility>

template<typename T>
struct ControlBlock
{
    T* ptr;
    int strongCount;
    int weakCount;
    explicit ControlBlock(T* p) : ptr(p), strongCount(1), weakCount(0) {}
};
template<typename T>
class SharedPtr
{
public:
    T* get() const {
        return ctrl ? ctrl->ptr : nullptr;
    }
    explicit operator bool() const {
        return ctrl && ctrl->ptr;
    }
template<typename U> friend class WeakPtr;
private:
    ControlBlock<T>* ctrl;
    void release() {
        if (!ctrl) return;

        --ctrl->strongCount;
        if (ctrl->strongCount == 0) {
            delete ctrl->ptr;  // distruge obiectul
            ctrl->ptr = nullptr;

            if (ctrl->weakCount == 0) {
                delete ctrl;
            }
        }
        ctrl = nullptr;
    }

public:
    SharedPtr() : ctrl(nullptr) {}
    explicit SharedPtr(T* p) {ctrl = new ControlBlock<T>(p);}

    ~SharedPtr() {release();}

    // Copy Constructor
    SharedPtr(const SharedPtr& other) {
        ctrl = other.ctrl;
        if (ctrl) ++ctrl->strongCount;
    }
    // Copy Assignment Operator
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            if (ctrl) ++ctrl->strongCount;
        }
        return *this;
    }

    // Move Constructor
    SharedPtr(SharedPtr&& other) noexcept {
        this->ctrl = other.ctrl;
        other.ctrl = nullptr;
    }

    // Move Assignment Operator
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if(this != &other) {
            release();
            this->ctrl = other.ctrl;
            other.ctrl = nullptr;
        }
        return *this;
    }

    T& operator*() const {return *ctrl->ptr;}
    T* operator->() const {return ctrl->ptr;}
    int use_count() const {
        return ctrl ? ctrl->strongCount : 0;
    }
};

template<typename T>
class WeakPtr {
template<typename U> friend class SharedPtr;
private:
    ControlBlock<T>* ctrl;

public:
    WeakPtr() : ctrl(nullptr) {}

    // construit din SharedPtr
    WeakPtr(const SharedPtr<T>& sp) {
        ctrl = sp.ctrl;
        if (ctrl) ++ctrl->weakCount;
    }

    // Copy Constructor
    WeakPtr(const WeakPtr& other) {
        ctrl = other.ctrl;
        if (ctrl) ++ctrl->weakCount;
    }

    // Copy Assignment
    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            if (ctrl) ++ctrl->weakCount;
        }
        return *this;
    }

    // Move Constructor
    WeakPtr(WeakPtr&& other) noexcept {
        this->ctrl = other.ctrl;
        other.ctrl = nullptr;
    }

    // Move Assignment Operator
    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if(this != &other) {
            release();
            this->ctrl = other.ctrl;
            other.ctrl = nullptr;
        }
        return *this;
    }

    ~WeakPtr() {
        release();
    }

    void release() {
        if (!ctrl) return;

        --ctrl->weakCount;

        if (ctrl->strongCount == 0 && ctrl->weakCount == 0) {
            delete ctrl;
        }

        ctrl = nullptr;
    }

    bool expired() const {
        return !ctrl || ctrl->strongCount == 0;
    }

    SharedPtr<T> lock() const {
        if (expired()) {
            return SharedPtr<T>();
        }
        SharedPtr<T> sp;
        sp.setControlBlock(ctrl);
        ++ctrl->strongCount;
        return sp;
    }
};