#include "Freight.h"

Freight::Freight() { }
Freight::Freight(Model * freightModel, const GLuint * shaderProgram) : Object(freightModel, nullptr, shaderProgram, false) { }
Freight::~Freight() { }
