#pragma once

class HistoryEvent {
    public:
        HistoryEvent(const HistoryEvent *last_event) : previousRelEvent(last_event) {}

        const HistoryEvent *previousRelEvent;
        virtual const char *getTextEvent() = 0;
}

// Event 1
// Event 2
// Event 1 b

// birth
// death
// 
