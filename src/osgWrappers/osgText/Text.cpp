// ***************************************************************************
//
//   Generated automatically by genwrapper.
//   Please DO NOT EDIT this file!
//
// ***************************************************************************

#include <osgIntrospection/ReflectionMacros>
#include <osgIntrospection/TypedMethodInfo>
#include <osgIntrospection/Attributes>

#include <osg/CopyOp>
#include <osg/Drawable>
#include <osg/Object>
#include <osg/PrimitiveSet>
#include <osg/Quat>
#include <osg/State>
#include <osg/StateSet>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osgText/Font>
#include <osgText/String>
#include <osgText/Text>

TYPE_NAME_ALIAS(std::map< osg::ref_ptr< osg::StateSet > COMMA  osgText::Text::GlyphQuads >, osgText::Text::TextureGlyphQuadMap);

BEGIN_ENUM_REFLECTOR(osgText::Text::CharacterSizeMode)
	EnumLabel(osgText::Text::OBJECT_COORDS);
	EnumLabel(osgText::Text::SCREEN_COORDS);
	EnumLabel(osgText::Text::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
END_REFLECTOR

BEGIN_ENUM_REFLECTOR(osgText::Text::AlignmentType)
	EnumLabel(osgText::Text::LEFT_TOP);
	EnumLabel(osgText::Text::LEFT_CENTER);
	EnumLabel(osgText::Text::LEFT_BOTTOM);
	EnumLabel(osgText::Text::CENTER_TOP);
	EnumLabel(osgText::Text::CENTER_CENTER);
	EnumLabel(osgText::Text::CENTER_BOTTOM);
	EnumLabel(osgText::Text::RIGHT_TOP);
	EnumLabel(osgText::Text::RIGHT_CENTER);
	EnumLabel(osgText::Text::RIGHT_BOTTOM);
	EnumLabel(osgText::Text::LEFT_BASE_LINE);
	EnumLabel(osgText::Text::CENTER_BASE_LINE);
	EnumLabel(osgText::Text::RIGHT_BASE_LINE);
	EnumLabel(osgText::Text::BASE_LINE);
END_REFLECTOR

BEGIN_ENUM_REFLECTOR(osgText::Text::AxisAlignment)
	EnumLabel(osgText::Text::XY_PLANE);
	EnumLabel(osgText::Text::REVERSED_XY_PLANE);
	EnumLabel(osgText::Text::XZ_PLANE);
	EnumLabel(osgText::Text::REVERSED_XZ_PLANE);
	EnumLabel(osgText::Text::YZ_PLANE);
	EnumLabel(osgText::Text::REVERSED_YZ_PLANE);
	EnumLabel(osgText::Text::SCREEN);
END_REFLECTOR

BEGIN_ENUM_REFLECTOR(osgText::Text::Layout)
	EnumLabel(osgText::Text::LEFT_TO_RIGHT);
	EnumLabel(osgText::Text::RIGHT_TO_LEFT);
	EnumLabel(osgText::Text::VERTICAL);
END_REFLECTOR

BEGIN_ENUM_REFLECTOR(osgText::Text::DrawModeMask)
	EnumLabel(osgText::Text::TEXT);
	EnumLabel(osgText::Text::BOUNDINGBOX);
	EnumLabel(osgText::Text::ALIGNMENT);
END_REFLECTOR

BEGIN_OBJECT_REFLECTOR(osgText::Text)
	BaseType(osg::Drawable);
	Constructor0();
	ConstructorWithDefaults2(IN, const osgText::Text &, text, , IN, const osg::CopyOp &, copyop, osg::CopyOp::SHALLOW_COPY);
	Method0(osg::Object *, cloneType);
	Method1(osg::Object *, clone, IN, const osg::CopyOp &, copyop);
	Method1(bool, isSameKindAs, IN, const osg::Object *, obj);
	Method0(const char *, className);
	Method0(const char *, libraryName);
	MethodWithDefaults1(void, setFont, IN, osgText::Font *, font, 0);
	Method1(void, setFont, IN, const std::string &, fontfile);
	Method0(const osgText::Font *, getFont);
	Method2(void, setFontResolution, IN, unsigned int, width, IN, unsigned int, height);
	Method0(unsigned int, getFontWidth);
	Method0(unsigned int, getFontHeight);
	Method1(void, setText, IN, const osgText::String &, text);
	Method1(void, setText, IN, const std::string &, text);
	Method2(void, setText, IN, const std::string &, text, IN, osgText::String::Encoding, encoding);
	Method1(void, setText, IN, const wchar_t *, text);
	Method0(osgText::String &, getText);
	Method0(const osgText::String &, getText);
	Method0(void, update);
	MethodWithDefaults2(void, setCharacterSize, IN, float, height, , IN, float, aspectRatio, 1.0f);
	Method0(float, getCharacterHeight);
	Method0(float, getCharacterAspectRatio);
	Method1(void, setCharacterSizeMode, IN, osgText::Text::CharacterSizeMode, mode);
	Method0(osgText::Text::CharacterSizeMode, getCharacterSizeMode);
	Method1(void, setMaximumWidth, IN, float, maximumWidth);
	Method0(float, getMaximumWidth);
	Method1(void, setMaximumHeight, IN, float, maximumHeight);
	Method0(float, getMaximumHeight);
	Method1(void, setPosition, IN, const osg::Vec3 &, pos);
	Method0(const osg::Vec3 &, getPosition);
	Method1(void, setAlignment, IN, osgText::Text::AlignmentType, alignment);
	Method0(osgText::Text::AlignmentType, getAlignment);
	Method1(void, setAxisAlignment, IN, osgText::Text::AxisAlignment, axis);
	Method1(void, setRotation, IN, const osg::Quat &, quat);
	Method0(const osg::Quat &, getRotation);
	Method1(void, setAutoRotateToScreen, IN, bool, autoRotateToScreen);
	Method0(bool, getAutoRotateToScreen);
	Method1(void, setLayout, IN, osgText::Text::Layout, layout);
	Method0(osgText::Text::Layout, getLayout);
	Method1(void, setColor, IN, const osg::Vec4 &, color);
	Method0(const osg::Vec4 &, getColor);
	Method1(void, setDrawMode, IN, unsigned int, mode);
	Method0(unsigned int, getDrawMode);
	Method1(void, setKerningType, IN, KerningType, kerningType);
	Method0(KerningType, getKerningType);
	Method1(void, drawImplementation, IN, osg::State &, state);
	Method1(bool, supports, IN, const osg::Drawable::AttributeFunctor &, x);
	Method1(bool, supports, IN, const osg::Drawable::ConstAttributeFunctor &, x);
	Method1(void, accept, IN, osg::Drawable::ConstAttributeFunctor &, af);
	Method1(bool, supports, IN, const osg::PrimitiveFunctor &, x);
	Method1(void, accept, IN, osg::PrimitiveFunctor &, pf);
	MethodWithDefaults1(void, releaseGLObjects, IN, osg::State *, state, 0);
	Method1(const osgText::Text::GlyphQuads *, getGlyphQuads, IN, osg::StateSet *, stateSet);
	Method0(const osgText::Text::TextureGlyphQuadMap &, getTextureGlyphQuadMap);
	Property(osgText::Text::AlignmentType, Alignment);
	Property(bool, AutoRotateToScreen);
	WriteOnlyProperty(osgText::Text::AxisAlignment, AxisAlignment);
	ReadOnlyProperty(float, CharacterAspectRatio);
	ReadOnlyProperty(float, CharacterHeight);
	Property(osgText::Text::CharacterSizeMode, CharacterSizeMode);
	Property(const osg::Vec4 &, Color);
	Property(unsigned int, DrawMode);
	WriteOnlyProperty(osgText::Font *, Font);
	ReadOnlyProperty(unsigned int, FontHeight);
	ReadOnlyProperty(unsigned int, FontWidth);
	Property(KerningType, KerningType);
	Property(osgText::Text::Layout, Layout);
	Property(float, MaximumHeight);
	Property(float, MaximumWidth);
	Property(const osg::Vec3 &, Position);
	Property(const osg::Quat &, Rotation);
	Property(const osgText::String &, Text);
	ReadOnlyProperty(const osgText::Text::TextureGlyphQuadMap &, TextureGlyphQuadMap);
END_REFLECTOR

TYPE_NAME_ALIAS(std::vector< osgText::Font::Glyph * >, osgText::Text::GlyphQuads::Glyphs);

TYPE_NAME_ALIAS(std::vector< unsigned int >, osgText::Text::GlyphQuads::LineNumbers);

TYPE_NAME_ALIAS(std::vector< osg::Vec2 >, osgText::Text::GlyphQuads::Coords2);

TYPE_NAME_ALIAS(std::vector< osg::Vec3 >, osgText::Text::GlyphQuads::Coords3);

TYPE_NAME_ALIAS(std::vector< osg::Vec2 >, osgText::Text::GlyphQuads::TexCoords);

BEGIN_VALUE_REFLECTOR(osgText::Text::GlyphQuads)
	Constructor0();
	Method0(osgText::Text::GlyphQuads::Glyphs, getGlyphs);
	Method0(const osgText::Text::GlyphQuads::Glyphs, getGlyphs);
	Method0(osgText::Text::GlyphQuads::Coords2 &, getCoords);
	Method0(const osgText::Text::GlyphQuads::Coords2 &, getCoords);
	Method1(osgText::Text::GlyphQuads::Coords3 &, getTransformedCoords, IN, unsigned int, contexID);
	Method1(const osgText::Text::GlyphQuads::Coords3 &, getTransformedCoords, IN, unsigned int, contexID);
	Method0(osgText::Text::GlyphQuads::TexCoords &, getTexCoords);
	Method0(const osgText::Text::GlyphQuads::TexCoords &, getTexCoords);
	Method0(osgText::Text::GlyphQuads::LineNumbers &, getLineNumbers);
	Method0(const osgText::Text::GlyphQuads::LineNumbers &, getLineNumbers);
	ReadOnlyProperty(osgText::Text::GlyphQuads::Coords2 &, Coords);
	ReadOnlyProperty(osgText::Text::GlyphQuads::Glyphs, Glyphs);
	ReadOnlyProperty(osgText::Text::GlyphQuads::LineNumbers &, LineNumbers);
	ReadOnlyProperty(osgText::Text::GlyphQuads::TexCoords &, TexCoords);
END_REFLECTOR

STD_MAP_REFLECTOR(std::map< osg::ref_ptr< osg::StateSet > COMMA  osgText::Text::GlyphQuads >);

STD_VECTOR_REFLECTOR(std::vector< osg::Vec2 >);

STD_VECTOR_REFLECTOR(std::vector< osgText::Font::Glyph * >);

