#pragma once

#include "History/HistoryEvent/HistoryEvent.hpp"
#include "History/HistoryFigure.hpp"

class BirthEvent : public HistoryEvent {

    public:
        BirthEvent(const HistoryEvent *event) : HistoryEvent(event) { }
        const char *getTextEvent();
    
}
