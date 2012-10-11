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

    vector<vec3> points() const;
    vector<vec3> normals() const;
    vector<vec2> uvs() const;

    sptr(rend::Material) getMaterial() const { return m_material; }
    void setMaterial(sptr(rend::Material) material) { m_material = material; m_sideType = material->sideType; }

    void setSideType(rend::Material::SideType st) { m_sideType = st; }
    rend::Material::SideType getSideType() const { return m_sideType; }

    void computeNormal();
    vec3 normal() const { return m_normal; }

    double square() const;

    friend bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2);
    friend bool ZCompareMin(const math::Triangle &t1, const math::Triangle &t2);
    friend bool ZCompareMax(const math::Triangle &t1, const math::Triangle &t2);
};

bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2);
bool ZCompareMin(const math::Triangle &t1, const math::Triangle &t2);
bool ZCompareMax(const math::Triangle &t1, const math::Triangle &t2);

// TODO: class Poly, for arbitrary polys support
// They will be triangulated

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

void Triangulate(const Polygon &poly, vector<Triangle> &resultList);

}

#endif // POLY_H
