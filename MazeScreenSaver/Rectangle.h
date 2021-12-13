#pragma once
#include "Prop.h"
class Rectangle :
    public Prop
{
public:
    Rectangle(Shader shader);
    void draw();
};

