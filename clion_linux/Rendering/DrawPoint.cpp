#include "stdafx.h"
#include "DrawPoint.h"

// Public methods

PAG::DrawPoint::DrawPoint (Point &point): Model3D(), _point(point)
{
    Component* component = new Component;
    component->_vertices.insert(component->_vertices.end(), {VAO::Vertex { vec3(_point.getX(), _point.getY(), .0f) } });
    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    this->buildVao(component);
}