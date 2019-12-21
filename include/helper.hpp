#ifndef HELPER_H
#define HELPER_H

#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace Render{

    inline std::ostream& operator <<(std::ostream& os, const glm::mat4 &g){
        os << g[0][0] << ", " << g[1][0] << ", " << g[2][0] << ", " << g[3][0] << std::endl
        << g[0][1] << ", " << g[1][1] << ", " << g[2][1] << ", " << g[3][1] << std::endl
        << g[0][2] << ", " << g[1][2] << ", " << g[2][2] << ", " << g[3][2] << std::endl
        << g[0][3] << ", " << g[1][3] << ", " << g[2][3] << ", " << g[3][3] << std::endl;
        return os;
    }
    
};
#endif