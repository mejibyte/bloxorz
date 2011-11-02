//
//  Falling.cpp
//  Bloxorz
//
//  Created by Carlos Vivares on 2/11/11.
//  Copyright 2011 Familia. All rights reserved.
//

#include "Falling.h"


GLfloat GRAVITY = 0.098;

static GLfloat tiempoCaidaLibre = 1.0, tiempoMovimiento = 0.0;
static GLfloat tileVelY = 1.0 , tilePosY = 0.0;


void freeFalling(){
    double time = clock();
    //Necesito llamar a isLosingPosition() para poder comenzar la animación.
    {
    
    tileVelY += GRAVITY * tiempoCaidaLibre;
    tilePosY -= GRAVITY * (tiempoCaidaLibre*tiempoCaidaLibre)*(0.5) + tileVelY*tiempoCaidaLibre; 
    
    

        while ((clock() - time) < 0.01*CLOCKS_PER_SEC)
        {
        
        }
        glTranslatef(1., tilePosY, 1.);
    }
    
}

