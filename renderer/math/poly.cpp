/*
 * poly.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "poly.h"

namespace math
{

Triangle::Triangle(rend::Material::SideType st)
    : m_sideType(st)
{
}

Triangle::Triangle(const vertex *arr, rend::Material::SideType st)
    : m_sideType(st)
{
    if (!arr)
    {
        syslog << "Trying to initialize triangle with an empty array" << logdebug;
        return;
    }

    m_verts[0] = arr[0];
    m_verts[1] = arr[1];
    m_verts[2] = arr[2];

    computeNormal();
}

/*const vertex &Triangle::v(const size_t ind) const
{
    if (ind > 2)
    {
        throw std::out_of_range("Bad index passed to triangle->v()");
    }

    return m_verts[ind];
}

vertex &Triangle::v(const size_t ind)
{
    if (ind > 2)
    {
        throw std::out_of_range("Bad index passed to triangle->v()");
    }

    return m_verts[ind];
}*/

vector<vec3> Triangle::points() const
{
    vector<vec3> res(3);
    res[0] = m_verts[0].p;
    res[1] = m_verts[1].p;
    res[2] = m_verts[2].p;

    return res;
}

vector<vec3> Triangle::normals() const
{
    vector<vec3> res(3);
    res[0] = m_verts[0].n;
    res[1] = m_verts[1].n;
    res[2] = m_verts[2].n;

    return res;
}

vector<vec2> Triangle::uvs() const
{
    vector<vec2> res(3);
    res[0] = m_verts[0].t;
    res[1] = m_verts[1].t;
    res[2] = m_verts[2].t;

    return res;
}

void Triangle::computeNormal()
{
    static vec3 p1, p2;

    p1.set((m_verts[1].p - m_verts[0].p).normalize());
    p2.set((m_verts[2].p - m_verts[0].p).normalize());

    m_normal = p1.crossProduct(p2);
    m_normal.normalize();
}

float Triangle::square() const
{
    static vec3 p1, p2;

    p1.set((m_verts[1].p - m_verts[0].p).normalize());
    p2.set((m_verts[2].p - m_verts[0].p).normalize());

    vec3 n = p1.crossProduct(p2);

    return 0.5 * n.length();
}

bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2)
{
    float avgz = 0.33333 * (t1.m_verts[0].p.z + t1.m_verts[1].p.z + t1.m_verts[2].p.z);
    float avgotherz = 0.33333 * (t2.m_verts[0].p.z + t2.m_verts[1].p.z + t2.m_verts[2].p.z);

    if (avgz < avgotherz)
        return true;

    return false;
}

bool ZCompareMin(const Triangle &t1, const Triangle &t2)
{
    vector<vec3> points = t1.points();
    float minz1 = (*std::min_element(points.begin(), points.end(), comparez)).z;

    points = t2.points();
    float minz2 = (*std::min_element(points.begin(), points.end(), comparez)).z;

    if (minz1 < minz2)
        return true;

    return false;
}

bool ZCompareMax(const Triangle &t1, const Triangle &t2)
{
    vector<vec3> points = t1.points();
    float minz1 = (*std::max_element(points.begin(), points.end(), comparez)).z;

    points = t2.points();
    float minz2 = (*std::max_element(points.begin(), points.end(), comparez)).z;

    if (minz1 < minz2)
        return true;

    return false;
}

Polygon::Polygon()
{
}

Polygon::Polygon(const vector<vertex> &vertices)
{
    if (vertices.size() < 3)
        throw std::runtime_error("Invalid poly.");

    copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));
}

void Polygon::set(const vector<vertex> &vertices)
{
    m_vertices.clear();
    copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));
}

void Polygon::split(Polygon &poly1, Polygon &poly2) const
{
    poly1.set(vector<vertex>(m_vertices.begin(), m_vertices.begin() + 3));
    poly2.set(vector<vertex>(m_vertices.begin() + 2, m_vertices.end()));
    poly2.m_vertices.push_back(m_vertices[0]);
}

void Triangulate(const Polygon &poly, vector<Triangle> &resultList)
{
    if (poly.m_vertices.size() == 3)
    {
        resultList.push_back(Triangle(&poly.m_vertices[0]));
        return;
    }
    else
    {
        Polygon p1, p2;

        poly.split(p1, p2);
        Triangulate(p1, resultList);
        Triangulate(p2, resultList);
    }
}

}
