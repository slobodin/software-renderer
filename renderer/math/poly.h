/*
 * poly.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef POLY_H
#define POLY_H

#include "comm_pch.h"

#include "vertex.h"
#include "material.h"
#include "m44.h"

namespace math
{

class Triangle
{
    vertex m_verts[3];
    vec3 m_normal;

    sptr(rend::Material) m_material;
    rend::Material::SideType m_sideType;

public:
    Triangle(rend::Material::SideType st = rend::Material::ONE_SIDE);
    Triangle(const vertex *arr, rend::Material::SideType st = rend::Material::ONE_SIDE);

    const vertex &v(size_t ind) const { return m_verts[ind]; }
    vertex &v(size_t ind) { return m_verts[ind]; }

    //! Sets 3 vertices from an array.
    void setVertices(const vertex *arr)
    {
        m_verts[0] = arr[0];
        m_verts[1] = arr[1];
        m_verts[2] = arr[2];
    }

    void applyTransformation(const math::M44 &transform)
    {
        // translate point
        m_verts[0].p = m_verts[0].p * transform;
        m_verts[1].p = m_verts[1].p * transform;
        m_verts[2].p = m_verts[2].p * transform;

        // FIXME: !!
        // translate normal
        /*m_verts[0].n = m_verts[0].n * transform;
        m_verts[1].n = m_verts[1].n * transform;
        m_verts[2].n = m_verts[2].n * transform;

        // noo??
        m_verts[0].n.normalize();
        m_verts[1].n.normalize();
        m_verts[2].n.normalize();*/
    }

    //! Returns copy of the triangle points.
    vector<vec3> points() const;
    //! Returns copy of the triangle normals.
    vector<vec3> normals() const;
    //! Returns copy of the triangle texture coordinates.
    vector<vec2> uvs() const;

    sptr(rend::Material) getMaterial() const { return m_material; }
    void setMaterial(sptr(rend::Material) material) { m_material = material; m_sideType = material->sideType; }

    void setSideType(rend::Material::SideType st) { m_sideType = st; }
    rend::Material::SideType getSideType() const { return m_sideType; }

    void computeNormal();
    vec3 normal() const { return m_normal; }

    float square() const;

    friend bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2);
    friend bool ZCompareMin(const math::Triangle &t1, const math::Triangle &t2);
    friend bool ZCompareMax(const math::Triangle &t1, const math::Triangle &t2);
};

bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2);
bool ZCompareMin(const math::Triangle &t1, const math::Triangle &t2);
bool ZCompareMax(const math::Triangle &t1, const math::Triangle &t2);

//! Arbitrary poly.
/*!
  * Only for polygons triangulation support.
  */
class Polygon
{
    vector<vertex> m_vertices;

public:
    Polygon();
    Polygon(const vector<vertex> &vertices);

    //! Set poly with new data.
    void set(const vector<vertex> &vertices);

    const vector<vertex> &vertices() const { return m_vertices; }

    //! Splits this poly into two polys.
    void split(Polygon &poly1, Polygon &poly2) const;

    //! Performs triangulation of poly into resultList.
    friend void Triangulate(const Polygon &poly, vector<Triangle> &resultList);
};

//! Performs triangulation of poly into resultList.
void Triangulate(const Polygon &poly, vector<Triangle> &resultList);
//! Performs triangulation of poly defined by index and vertex list.
void Triangulate(const vector<math::vertex> &vertices, const vector<int> &indices, vector<int> &resultIndexList);

}

#endif // POLY_H
