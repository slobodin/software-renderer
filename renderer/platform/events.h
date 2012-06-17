#ifndef EVENTS_H
#define EVENTS_H

struct MouseEvent
{
    enum
    {
        LEFT_PRESSED    = 0x1,
        RIGHT_PRESSED   = 0x2,
        MIDDLE_PRESSED  = 0x4
    };

    int x, y;
    unsigned buttonsState;

    bool isLeftPressed() const { return buttonsState & LEFT_PRESSED; }
    bool isRightPressed() const { return buttonsState & RIGHT_PRESSED; }
    bool isMiddlePressed() const { return buttonsState & MIDDLE_PRESSED; }

    MouseEvent() : x(0), y(0), buttonsState(0) { }
};

struct KeyboardEvent
{
    unsigned keycode;

    KeyboardEvent() : keycode(0) { }
};

#endif // EVENTS_H
