/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#pragma once

#include "config.h"

#include <sofa/defaulttype/Vec.h>
#include <sofa/core/DataEngine.h>
#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/core/behavior/MechanicalState.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <sofa/defaulttype/VecTypes.h>

namespace sofa::component::engine
{
 /*
  * This engine computes barycentric coefficients from an input set of topology (and positions) and some other (mapped) positions
  */
template <class DataTypes>
class MeshBarycentricMapperEngine : public core::DataEngine
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(MeshBarycentricMapperEngine,DataTypes),core::DataEngine);
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::VecCoord VecCoord;
    typedef typename DataTypes::Real Real;
    typedef defaulttype::Vec<3,Real> Vec3;
    typedef typename sofa::helper::vector<unsigned int>  VecIndices;

protected:
    MeshBarycentricMapperEngine();

public:
    virtual ~MeshBarycentricMapperEngine() override {}

    void init() override;
    void reinit() override;
    void doUpdate() override;
    void draw(const core::visual::VisualParams* vparams) override;

    void addPointInLine(const int lineIndex, const SReal* baryCoords);
    void addPointInTriangle(const int triangleIndex, const SReal* baryCoords, const unsigned int pointIndex);
    void addPointInQuad(const int quadIndex, const SReal* baryCoords);
    void addPointInTetra(const int tetraIndex, const SReal* baryCoords, const unsigned int pointIndex);
    void addPointInCube(const int cubeIndex, const SReal* baryCoords);


    Data<VecCoord> d_inputPositions; ///< Initial positions of the master points
    Data<VecCoord> d_mappedPointPositions; ///< Initial positions of the mapped points
    Data<VecCoord> d_barycentricPositions; ///< Output : Barycentric positions of the mapped points
    Data< VecIndices> d_tableElements; ///< Output : Table that provides the element index to which each input point belongs
    Data<bool> d_bComputeLinearInterpolation; ///< if true, computes a linear interpolation (debug)

    Data< sofa::helper::vector<sofa::helper::vector< unsigned int > > > d_interpolationIndices; ///< Indices of a linear interpolation
    Data< sofa::helper::vector<sofa::helper::vector< Real > > > d_interpolationValues; ///< Values of a linear interpolation
    
    SingleLink<MeshBarycentricMapperEngine<DataTypes>, sofa::core::topology::BaseMeshTopology, BaseLink::FLAG_STOREPATH | BaseLink::FLAG_STRONGLINK> l_topology; ///< Name and path of Input mesh Topology

    //Temporary function to warn the user when old attribute names are used
    void parse( sofa::core::objectmodel::BaseObjectDescription* arg ) override
    {
        if (arg->getAttribute("InputMeshName"))
        {
            msg_warning() << "input data 'InputMeshName' changed for 'topology', please update your scene (see PR#1487)";
        }
        MeshBarycentricMapperEngine::parse(arg);
    }

private:
    sofa::helper::vector<sofa::helper::vector< unsigned int > >* linearInterpolIndices;
    sofa::helper::vector<sofa::helper::vector< Real > >* linearInterpolValues;
};



#if  !defined(SOFA_COMPONENT_ENGINE_MESHBARYCENTRICMAPPERENGINE_CPP)
extern template class SOFA_GENERAL_ENGINE_API MeshBarycentricMapperEngine<defaulttype::Vec3Types>;
 
#endif

} // namespace sofa::component::engine

