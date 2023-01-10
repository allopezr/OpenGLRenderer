#pragma once

/* 
 * File:   DrawPointCloud.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 13:29
 */

#include "Geometry/PointCloud.h"
#include "Model3D.h"

namespace PAG
{
    class DrawPointCloud : public Model3D 
    {
    protected:
        PointCloud _pointCloud;

    public:
        DrawPointCloud(PointCloud& t);
        DrawPointCloud(const DrawPointCloud& drawPointCloud) = delete;
        virtual ~DrawPointCloud() {};
    };
}

