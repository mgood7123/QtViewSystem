#ifndef ANIMATIONGROUPHELPER_H
#define ANIMATIONGROUPHELPER_H

#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

template <typename T>
class AnimationLambda {
public:
    T * object = nullptr;
    QAbstractAnimation * animation = nullptr;
    AnimationLambda(T * object, QAbstractAnimation * animation) {
        this->object = object;
        this->animation = animation;
    };
    AnimationLambda(T * object, std::function<QAbstractAnimation *(T * obj)> func) {
        this->object = object;
        animation = func(object);
    };
};

#define ANIMATION_GROUP_HELPER_PUBLIC_BASE(T) \
protected: \
QParallelAnimationGroup animationGroup; \
public: \
 \
    QSequentialAnimationGroup * getSequentialAnimationGroup() { \
        return new QSequentialAnimationGroup(); \
    } \
 \
    QParallelAnimationGroup * getParallelAnimationGroup() { \
        return new QParallelAnimationGroup(); \
    } \
 \
    virtual T* addAnimation(QAbstractAnimation * animation) { \
        animationGroup.addAnimation(animation); \
        return static_cast<T*>(this); \
    } \
 \
    AnimationLambda<T> addAnimation(std::function<QAbstractAnimation *(T * obj)> func) { \
        AnimationLambda<T> animation = AnimationLambda<T>(this, func); \
        addAnimation(animation.animation); \
        return animation; \
    } \
 \
    virtual T* removeAnimation(QAbstractAnimation * animation) { \
        animationGroup.removeAnimation(animation); \
        return static_cast<T*>(this); \
    } \
 \
    AnimationLambda<T> removeAnimation(AnimationLambda<T> animation) { \
        removeAnimation(animation.animation); \
        return animation; \
    } \
 \
    virtual T* startAnimation(QAbstractAnimation::DeletionPolicy policy = QAbstractAnimation::DeletionPolicy::KeepWhenStopped) { \
        animationGroup.start(policy); \
        return static_cast<T*>(this); \
    } \
 \
    virtual T* pauseAnimation() { \
        animationGroup.pause(); \
        return static_cast<T*>(this); \
    } \
 \
    virtual T* stopAnimation() { \
        animationGroup.stop(); \
        return static_cast<T*>(this); \
    } \

#define ANIMATION_GROUP_HELPER_PUBLIC_BASE_OVERRIDE(T) \
    virtual T* addAnimation(QAbstractAnimation * animation) override { \
        animationGroup.addAnimation(animation); \
        return static_cast<T*>(this); \
    } \
 \
    AnimationLambda<T> addAnimation(std::function<QAbstractAnimation *(T * obj)> func) { \
        AnimationLambda<T> animation = AnimationLambda<T>(this, func); \
        addAnimation(animation.animation); \
        return animation; \
    } \
 \
    virtual T* removeAnimation(QAbstractAnimation * animation) override { \
        animationGroup.removeAnimation(animation); \
        return static_cast<T*>(this); \
    } \
 \
    AnimationLambda<T> removeAnimation(AnimationLambda<T> animation) { \
        removeAnimation(animation.animation); \
        return animation; \
    } \
 \
    virtual T* startAnimation(QAbstractAnimation::DeletionPolicy policy = QAbstractAnimation::DeletionPolicy::KeepWhenStopped) override { \
        animationGroup.start(policy); \
        return static_cast<T*>(this); \
    } \
 \
    virtual T* pauseAnimation() override { \
        animationGroup.pause(); \
        return static_cast<T*>(this); \
    } \
 \
    virtual T* stopAnimation() override { \
        animationGroup.stop(); \
        return static_cast<T*>(this); \
    } \

#endif // ANIMATIONGROUPHELPER_H
