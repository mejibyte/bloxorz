#pragma once

class AbstractController {
public:    
    // Runs the game and synchronizes calls between the model and the view as necessary.    
    virtual void run() = 0;
};