/*
 * decodercob.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef DECODERCOB_H
#define DECODERCOB_H

#include "comm_pch.h"

#include "resourcedecoder.h"
#include "vertex.h"

namespace base
{

class DecoderCOB : public ResourceDecoder
{
    string m_name;
    int currVertex;

    vector<math::vertex> vertexList;
    vector<int> indices;

    void parseHeader(string &line);
    void parseTransform(string &line);
    void parseVertices(string &line);
    void parseUV(string &line);
    void parseFaces(string &line);

    void clear();
public:
    DecoderCOB();
    ~DecoderCOB();

    sptr(Resource)  decode(const string &path);
    string          extension() const;
};

}

#endif // DECODERCOB_H
