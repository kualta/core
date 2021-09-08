#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include "Essential.h"
#include "FileSystem.h"
#include "Mesh.h"

#include <string>
#include <fstream>

#include <Magnum/Shaders/VertexColorGL.h>

using namespace Magnum;
namespace core {

class Shader {
public:
    Shader();

    void Draw(Mesh* mesh);

protected:

    Shaders::VertexColorGL2D shader;

};

}

#endif //CORE_SHADER_H
