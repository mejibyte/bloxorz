#pragma once

#include "Board.h"

class AbstractView {
public:
    static const int WIDTH = 700;
    static const int HEIGHT = 700;
    virtual void setBoard(Board board) = 0;
    virtual void refresh() = 0;
protected:
    Board board;
};