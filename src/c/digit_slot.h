#ifndef DIGIT_SLOT_H
#define DIGIT_SLOT_H

typedef struct {
    Layer*            layer;
    bool              mirror;
    uint8_t           prevDigit;
    uint8_t           curDigit;
    uint8_t           divider;
    AnimationProgress normTime;
    uint8_t           slotIndex;
} digitSlot;

#endif /* end of include guard: DIGIT_SLOT_H */
