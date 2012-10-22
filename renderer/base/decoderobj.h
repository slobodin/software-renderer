/*
 * decoderobj.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODEROBJ_H
#define DECODEROBJ_H

#include "comm_pch.h"

#include "resourcedecoder.h"
#include "vertex.h"

namespace base
{

class DecoderOBJ : public ResourceDecoder
{
    void appendVertex(string &line);
    void appendFace(string &line);
    void appendNormal(string &line);
    void triangulateModel();

    vector<math::vertex> vertexList;
    vector<math::vec3> normalsList;

    struct FaceInfo
    {
        vector<int> indices;
        vector<int> normalIndices;
    };

    vector<FaceInfo> faces;
    vector<int> resultTrianglesIndices;

    void clear();

public:
    DecoderOBJ() { }
    ~DecoderOBJ() { }

    sptr(Resource)  decode(const string &path);
    string          extension() const;
};

}

#endif // DECODEROBJ_H
