//
// OpenFlightŪ loader for OpenSceneGraph
//
//  Copyright (C) 2005-2006  Brede Johansen
//

#include <cassert>
#include <osg/Geode>
#include <osg/Billboard>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/CullFace>
#include <osg/PolygonOffset>
#include <osg/Depth>
#include <osg/ShadeModel>
#include <osg/BlendFunc>
#include <osgUtil/Tesselator>
#include <osgUtil/SmoothingVisitor>
#include "Registry.h"
#include "Document.h"
#include "RecordInputStream.h"

namespace flt {

class Face : public PrimaryRecord
{
    // flags
    static const unsigned int TERRAIN_BIT      = 0x80000000u >> 0;
    static const unsigned int NO_COLOR_BIT     = 0x80000000u >> 1;
    static const unsigned int NO_ALT_COLOR_BIT = 0x80000000u >> 2;
    static const unsigned int PACKED_COLOR_BIT = 0x80000000u >> 3;
    static const unsigned int FOOTPRINT_BIT    = 0x80000000u >> 4;    // Terrain culture cutout
    static const unsigned int HIDDEN_BIT       = 0x80000000u >> 5;
    static const unsigned int ROOFLINE_BIT     = 0x80000000u >> 6;

    osg::Vec4   _primaryColor;

    int32       _IRColor;
    int16       _relativePriority;
    uint8       _drawFlag;
    uint8       _texturedWhite;
    int16       _primaryNameIndex;
    int16       _secondaryNameIndex;
    uint8       _template;
    int         _detailTexture;
    int         _textureIndex;
    int         _materialIndex;
    int16       _surface;
    int16       _feature;
    int32       _IRMaterial;
    uint16      _transparency;
    uint8       _influenceLOD;
    uint8       _linestyle;
    uint32      _flags;
    uint8       _lightMode;
    osg::Vec4   _primaryPackedColor;
    osg::Vec4   _secondaryPackedColor;
    int         _textureMappingIndex;
    int         _primaryColorIndex;
    int         _alternateColorIndex;
    int         _shaderIndex;

    osg::ref_ptr<osg::Geode> _geode;
    osg::ref_ptr<osg::Geometry> _geometry;

public:

    Face() :
        _primaryColor(1,1,1,1)
    {
    }

    META_Record(Face)

    META_setID(_geode)
    META_setComment(_geode)
    META_setMatrix(_geode)
    META_setMultitexture(_geode)

    // draw mode
    enum DrawMode
    {
        SOLID_BACKFACED = 0,
        SOLID_NO_BACKFACE = 1,
        WIREFRAME_CLOSED = 2,
        WIREFRAME_NOT_CLOSED = 3,
        SURROUND_ALTERNATE_COLOR = 4,
        OMNIDIRECTIONAL_LIGHT = 8,
        UNIDIRECTIONAL_LIGHT = 9,
        BIDIRECTIONAL_LIGHT = 10
    };

    inline DrawMode getDrawMode() const { return (DrawMode)_drawFlag; }

    // lighting
    enum LightMode
    {
        FACE_COLOR = 0,
        VERTEX_COLOR = 1,
        FACE_COLOR_LIGHTING = 2,
        VERTEX_COLOR_LIGHTING = 3
    };

    inline LightMode getLightMode() const { return (LightMode)_lightMode; }
    inline bool isLit() const { return (_lightMode==FACE_COLOR_LIGHTING) || (_lightMode==VERTEX_COLOR_LIGHTING); }
    inline bool isGouraud() const { return (_lightMode==VERTEX_COLOR) || (_lightMode==VERTEX_COLOR_LIGHTING); }

    // flags
    inline bool noColor()         const { return (_flags & NO_COLOR_BIT)!=0; }
    inline bool isHidden()        const { return (_flags & HIDDEN_BIT)!=0; }
    inline bool isTerrain()       const { return (_flags & TERRAIN_BIT)!=0; }
    inline bool isFootprint()     const { return (_flags & FOOTPRINT_BIT)!=0; }
    inline bool isRoofline()      const { return (_flags & ROOFLINE_BIT)!=0; }
    inline bool packedColorMode() const { return (_flags & PACKED_COLOR_BIT)!=0; }

    // billboard
    enum TemplateMode
    {
        FIXED_NO_ALPHA_BLENDING = 0,
        FIXED_ALPHA_BLENDING = 1,
        AXIAL_ROTATE_WITH_ALPHA_BLENDING = 2,
        POINT_ROTATE_WITH_ALPHA_BLENDING = 4
    };

    inline TemplateMode getTemplateMode() const { return (TemplateMode)_template; }

    // transparency & alpha
    inline bool isAlphaBlend() const
    {
        return (_template==FIXED_ALPHA_BLENDING) ||
                (_template==AXIAL_ROTATE_WITH_ALPHA_BLENDING) ||
                (_template==POINT_ROTATE_WITH_ALPHA_BLENDING);
    }

    virtual osg::Vec4 getPrimaryColor() const { return _primaryColor; }
    inline int getMaterialIndex() const { return _materialIndex; }
	inline int getTextureIndex() const { return _textureIndex; }
	inline int getTextureMappingIndex() const { return _textureMappingIndex; }
	inline float getTransparency() const { return (float)_transparency / 65535.0f; }
    inline bool isTransparent() const { return _transparency > 0; }

    virtual void addChild(osg::Node& child)
    {
        // Add subface to parent.
        if (_parent.valid())
            _parent->addChild(child);
    }

    virtual void addVertex(Vertex& vertex)
    {
        osg::Vec3Array* vertices = getOrCreateVertexArray(*_geometry);
        vertices->push_back(vertex._coord);

        if (isGouraud())
        {
            osg::Vec4Array* colors = getOrCreateColorArray(*_geometry);
            if (vertex.validColor())
            {
                colors->push_back(vertex._color);
            }
            else
            {
                // Use face color if vertex color is -1 in a gouraud polygon.
                // http://www.multigen-paradigm.com/ubb/Forum1/HTML/000967.html
                colors->push_back(_primaryColor);
            }
        }

        if (vertex.validNormal())
        {
            osg::Vec3Array* normals = getOrCreateNormalArray(*_geometry);
            normals->push_back(vertex._normal);
        }

        if (vertex.validUV())
        {
            osg::Vec2Array* UVs = getOrCreateTextureArray(*_geometry,0);
            UVs->push_back(vertex._uv);
        }
    }

    virtual void addVertexUV(int unit, const osg::Vec2& uv)
    {
        osg::Vec2Array* UVs = getOrCreateTextureArray(*_geometry,unit);
        UVs->push_back(uv);
    }

    virtual void addMorphVertex(Vertex& vertex0, Vertex& vertex100)
    {
        osg::Vec3Array* vertices = getOrCreateVertexArray(*_geometry);
        vertices->push_back(vertex0._coord);

        if (isGouraud())
        {
            osg::Vec4Array* colors = getOrCreateColorArray(*_geometry);
            if (vertex0.validColor())
            {
                colors->push_back(vertex0._color);
            }
            else
            {
                // Use face color if vertex color is -1 in a gouraud polygon.
                // http://www.multigen-paradigm.com/ubb/Forum1/HTML/000967.html
                colors->push_back(_primaryColor);
            }
        }

        if (vertex0.validNormal())
        {
            osg::Vec3Array* normals = getOrCreateNormalArray(*_geometry);
            normals->push_back(vertex0._normal);
        }

        if (vertex0.validUV())
        {
            osg::Vec2Array* UVs = getOrCreateTextureArray(*_geometry,0);
            UVs->push_back(vertex0._uv);
        }
    }

protected:

    virtual void readRecord(RecordInputStream& in, Document& document)
    {
        std::string id = in.readString(8);
        _IRColor = in.readInt32();
        _relativePriority = in.readInt16();
        _drawFlag = in.readUInt8();
        _texturedWhite = in.readUInt8();
        _primaryNameIndex = in.readInt16(-1);
        _secondaryNameIndex = in.readInt16(-1);
        in.forward(1);
        _template = in.readUInt8(FIXED_NO_ALPHA_BLENDING);
        _detailTexture = in.readInt16(-1);
        _textureIndex = in.readInt16(-1);
        _materialIndex = in.readInt16(-1);
        _surface = in.readInt16();
        _feature = in.readInt16();
        _IRMaterial = in.readInt32(-1);
        _transparency = in.readUInt16(0);
        // version > 13
        _influenceLOD = in.readUInt8();
        _linestyle = in.readUInt8();
        _flags = in.readUInt32(0);
        _lightMode = in.readUInt8(FACE_COLOR);
        in.forward(7);
        _primaryPackedColor = in.readColor32();
        _secondaryPackedColor = in.readColor32();
        // version >= VERSION_15_1
        _textureMappingIndex = in.readInt16(-1);
        in.forward(2);
        _primaryColorIndex = in.readInt32(-1);
        _alternateColorIndex = in.readInt32(-1);
        // version >= 16
        in.forward(2);
        _shaderIndex = in.readInt16(-1);

        // Create Geode or Billboard.
        switch (_template)
        {
        case AXIAL_ROTATE_WITH_ALPHA_BLENDING:
            {
                osg::Billboard* billboard = new osg::Billboard;
                billboard->setMode(osg::Billboard::AXIAL_ROT);
                _geode = billboard;
            }
            break;
        case POINT_ROTATE_WITH_ALPHA_BLENDING:
            {
                osg::Billboard* billboard = new osg::Billboard;
                billboard->setMode(osg::Billboard::POINT_ROT_WORLD);
                _geode = billboard;
            }
            break;
        default:
            _geode = new osg::Geode;
        }

        _geode->setDataVariance(osg::Object::STATIC);
        _geode->setName(id);

        _geometry = new osg::Geometry;
        _geometry->setDataVariance(osg::Object::STATIC);
        _geode->addDrawable(_geometry.get());

        // StateSet
        osg::StateSet* stateset = _geode->getOrCreateStateSet();

        // Hidden
        if (isHidden())
            _geode->setNodeMask(0);

        // Face color
        if (_texturedWhite!=0 && _textureIndex>=0)
        {
            _primaryColor = osg::Vec4(1,1,1,1);
        }
        else
        {
            if (packedColorMode())
            {
                _primaryColor = _primaryPackedColor;
            }
            else
            {
                if (document.version() < VERSION_15_1)
                    _primaryColor = document.getColorPool()->getColor(_primaryNameIndex);

                else // >= VERSION_15_1
                    _primaryColor = document.getColorPool()->getColor(_primaryColorIndex);
            }
        }

        // Lighting
        stateset->setMode(GL_LIGHTING, isLit() ? osg::StateAttribute::ON : osg::StateAttribute::OFF);

        // Material
        bool isTransparentMaterial = false;
        if (isLit())
        {
            osg::Vec4 col = _primaryColor;
            col.a() = 1.0f - getTransparency();
            osg::Material* material = document.getOrCreateMaterialPool()->getOrCreateMaterial(_materialIndex,col);
            stateset->setAttribute(material);
            isTransparentMaterial = material->getDiffuse(osg::Material::FRONT).a() < 0.99f;
        }

        // Shaders
        if (_shaderIndex >= 0)
        {
            ShaderPool* sp = document.getOrCreateShaderPool();
            osg::Program* program = sp->get(_shaderIndex);
            if (program)
                stateset->setAttributeAndModes(program, osg::StateAttribute::ON);
        }

         // Texture
        TexturePool* tp = document.getOrCreateTexturePool();
        osg::StateSet* textureStateSet = tp->get(_textureIndex);
        if (textureStateSet)
        {
            // Merge face stateset with texture stateset
            stateset->merge(*textureStateSet);
        }

        // Translucent image?
        bool isImageTranslucent = false;
        if (textureStateSet)
        {
            if (document.getUseTextureAlphaForTransparancyBinning())
            {
                osg::Texture2D* texture = dynamic_cast<osg::Texture2D*>(textureStateSet->getTextureAttribute(0,osg::StateAttribute::TEXTURE));
                if (texture)
                {
                    osg::Image* image = texture->getImage();
                    if (image && image->isImageTranslucent())
                        isImageTranslucent = true;
                }
            }
        }

        // Enable alpha blend?
        if (isAlphaBlend() || isTransparent() || isTransparentMaterial || isImageTranslucent)
        {
            stateset->setAttributeAndModes(new osg::BlendFunc(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA), osg::StateAttribute::ON);
            stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
        }

        // Cull face
        switch(_drawFlag)
        {
        case SOLID_BACKFACED:     // Enable backface culling
            stateset->setAttributeAndModes(new osg::CullFace(osg::CullFace::BACK), osg::StateAttribute::ON);
            break;
        case SOLID_NO_BACKFACE:   // Disable backface culling
            stateset->setMode(GL_CULL_FACE,osg::StateAttribute::OFF);
            break;
        }

        // Subface
        if (document.subfaceLevel() > 0)
        {
            osg::PolygonOffset* polyoffset = new osg::PolygonOffset;
            polyoffset->setFactor(-10.0f);
            polyoffset->setUnits(-40.0f);
            stateset->setAttributeAndModes(polyoffset, osg::StateAttribute::ON);

            osg::Depth* depth = new osg::Depth;
            depth->setWriteMask(false);
            stateset->setAttribute(depth);

            stateset->setRenderBinDetails(document.subfaceLevel(),"RenderBin");
        }

        // Add to parent.
        if (_parent.valid())
            _parent->addChild(*_geode);
    }

    osg::PrimitiveSet::Mode getPrimitiveSetMode(int numVertices)
    {
        switch(getDrawMode())
        {
            case WIREFRAME_NOT_CLOSED:
                return osg::PrimitiveSet::LINE_STRIP;
            case WIREFRAME_CLOSED:
                return osg::PrimitiveSet::LINE_LOOP;
            case OMNIDIRECTIONAL_LIGHT:
            case UNIDIRECTIONAL_LIGHT:
            case BIDIRECTIONAL_LIGHT:
                return osg::PrimitiveSet::POINTS;
            default: break;
        }

        switch (numVertices)
        {
            case 1: return osg::PrimitiveSet::POINTS;
            case 2: return osg::PrimitiveSet::LINES;
            case 3: return osg::PrimitiveSet::TRIANGLES;
            case 4: return osg::PrimitiveSet::QUADS;
            default: break;
        }

        return osg::PrimitiveSet::POLYGON;
    }

    virtual ~Face()
    {
        if (_geode.valid())
        {
            for (unsigned int i=0; i<_geode->getNumDrawables(); ++i)
            {
                osg::Geometry* geometry = dynamic_cast<osg::Geometry*>(_geode->getDrawable(i));
                if (geometry)
                {
                    osg::Array* vertices = geometry->getVertexArray();
                    if (vertices)
                    {
                        GLint first = 0;
                        GLsizei count = vertices->getNumElements();
                        osg::PrimitiveSet::Mode mode = getPrimitiveSetMode(count);
                        geometry->addPrimitiveSet(new osg::DrawArrays(mode,first,count));
                    }

                    // Color binding
                    if (isGouraud())
                    {
                        // Color per vertex
                        geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
                    }
                    else
                    {
                        // Color per face
                        osg::Vec4 col = getPrimaryColor();
                        col[3] = 1.0f - getTransparency();

                        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
                        osg::Vec4Array* colors = new osg::Vec4Array(1);
                        (*colors)[0] = col;
                        geometry->setColorArray(colors);
                    }

                    // Normal binding
                    if (isLit())
                    {
                        geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX );
                    }
                    else
                    {
                        geometry->setNormalBinding(osg::Geometry::BIND_OFF);
                        geometry->setNormalArray(NULL);
                    }
                }
            }
        }
    }
};

RegisterRecordProxy<Face> g_Face(FACE_OP);
RegisterRecordProxy<Face> g_Mesh(MESH_OP);


/** VertexList -
  * The VertexList is a leaf record.
  * Possible parents: Face, Mesh & LightPoint
  */
class VertexList : public PrimaryRecord
{
public:

    VertexList() {}

    META_Record(VertexList)

    virtual void addVertex(Vertex& vertex)
    {
        // forward vertex to parent.
        if (_parent.valid())
            _parent->addVertex(vertex);
    }

    virtual void addVertexUV(int layer,const osg::Vec2& uv)
    {
        // forward uv to parent.
        if (_parent.valid())
            _parent->addVertexUV(layer,uv);
    }

protected:

    virtual ~VertexList() {}

    virtual void readRecord(RecordInputStream& in, Document& document)
    {
        VertexPool* vp = document.getVertexPool();
        if (vp)
        {
            int vertices = (in.getRecordSize()-4) / 4;

            // Use the Vertex pool as a record stream.
            RecordInputStream inVP(vp);
            for (int n=0; n<vertices; n++)
            {
                // Get position of vertex.
                uint32 pos = in.readUInt32();

                // Get vertex from vertex pool.
                inVP().seekg((std::istream::pos_type)pos);
                inVP.readRecord(document);
            }
        }
    }
};


RegisterRecordProxy<VertexList> g_VertexList(VERTEX_LIST_OP);


/** MorphVertexList -
  * The MorphVertexList is a leaf record.
  */
class MorphVertexList : public PrimaryRecord
{
    enum Mode
    {
        UNDEFINED,
        MORPH_0,
        MORPH_100
    };

    Mode _mode;
    Vertex _vertex0;
    Vertex _vertex100;

public:

    MorphVertexList():
        _mode(UNDEFINED)
    {
    }

    META_Record(MorphVertexList)

    virtual void addVertex(Vertex& vertex)
    {
        switch (_mode)
        {
        case MORPH_0:
            _vertex0 = vertex;
            break;
        case MORPH_100:
            _vertex100 = vertex;

            // forward vertex to parent.
            if (_parent.valid())
                _parent->addMorphVertex(_vertex0, _vertex100);
            break;
        }
    }

    //virtual void addVertexUV(int layer,const osg::Vec2& uv)
    //{
    //    // forward uv to parent.
    //    if (_parent.valid())
    //        _parent->addVertexUV(layer,uv);
    //}

protected:

    virtual ~MorphVertexList() {}

    virtual void readRecord(RecordInputStream& in, Document& document)
    {
        VertexPool* vp = document.getVertexPool();
        if (vp)
        {
            int vertices = (in.getRecordSize()-4) / 8;

            // Use the Vertex pool as a record stream.
            RecordInputStream inVP(vp);
            for (int n=0; n<vertices; n++)
            {
                // Get position of vertex.
                uint32 offset0 = in.readUInt32();
                uint32 offset100 = in.readUInt32();

                // Get vertex from vertex pool.

                // 0%
                _mode = MORPH_0;
                inVP().seekg((std::istream::pos_type)offset0);
                inVP.readRecord(document);

                // 100%
                _mode = MORPH_100;
                inVP().seekg((std::istream::pos_type)offset100);
                inVP.readRecord(document);
            }
        }
    }
};

RegisterRecordProxy<MorphVertexList> g_MorphVertexList(MORPH_VERTEX_LIST_OP);

} // end namespace
