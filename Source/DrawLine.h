#pragma once

/* 
 *  File:   DrawLine.h
 *  Author: lidia
 *
 *  Created on 20 de enero de 2021, 12:06
 */

#include "Geometry/Line.h"
#include "Model3D.h"

namespace PAG
{
    class DrawLine : public Model3D 
    {
    protected:
        Line _line;

    public:
        DrawLine(Line& t);
        DrawLine(const DrawLine& drawLine) = delete;
        virtual ~DrawLine() {};
    };
}

