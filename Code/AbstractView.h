#pragma once

#include "Board.h"

class AbstractView {
    virtual void setBoard(Board board) = 0;
    virtual void refresh() = 0;
};