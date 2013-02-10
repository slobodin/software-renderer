/*
 * decoderobj.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODEROBJ_H
#define DECODEROBJ_H

#include "resourcedecoder.h"
#include "math/vertex.h"

namespace base
{

class DecoderOBJ : public ResourceDecoder
{
    void appendVertex(std::string &line);
    void appendFace(std::string &line);
    void appendNormal(std::string &line);
    void triangulateModel();

    std::vector<math::vertex> vertexList;
    std::vector<math::vec3> normalsList;

    struct FaceInfo
    {
        std::vector<int> indices;
        std::vector<int> normalIndices;
    };

    std::vector<FaceInfo> faces;
    std::vector<int> resultTrianglesIndices;

    void clear();

public:
    DecoderOBJ() { }
    ~DecoderOBJ() { }

    sptr(Resource)  decode(const std::string &path);
    std::string     extension() const;
};

}

#endif // DECODEROBJ_H
