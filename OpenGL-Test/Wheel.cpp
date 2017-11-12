#include "Wheel.h"

Wheel::Wheel() { }
Wheel::Wheel(Model* wheelModel, const GLuint* shaderProgram) : Object(wheelModel, nullptr, shaderProgram, false) { }
Wheel::~Wheel() { }