// ***************************************************************************
//
//   Generated automatically by genwrapper.
//   Please DO NOT EDIT this file!
//
// ***************************************************************************

#include <osgIntrospection/ReflectionMacros>
#include <osgIntrospection/TypedMethodInfo>
#include <osgIntrospection/Attributes>

#include <osg/AnimationPath>
#include <osg/ApplicationUsage>
#include <osg/ArgumentParser>
#include <osg/Node>
#include <osg/NodeVisitor>
#include <osg/Quat>
#include <osg/RefNodePath>
#include <osg/Vec3>
#include <osgGA/EventVisitor>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/MatrixManipulator>
#include <osgProducer/KeyboardMouseCallback>
#include <osgProducer/Viewer>
#include <osgUtil/IntersectVisitor>

TYPE_NAME_ALIAS(std::list< osg::ref_ptr< osgGA::GUIEventHandler > >, osgProducer::Viewer::EventHandlerList);

BEGIN_ENUM_REFLECTOR(osgProducer::Viewer::ViewerOptions)
	EnumLabel(osgProducer::Viewer::NO_EVENT_HANDLERS);
	EnumLabel(osgProducer::Viewer::TRACKBALL_MANIPULATOR);
	EnumLabel(osgProducer::Viewer::DRIVE_MANIPULATOR);
	EnumLabel(osgProducer::Viewer::FLIGHT_MANIPULATOR);
	EnumLabel(osgProducer::Viewer::TERRAIN_MANIPULATOR);
	EnumLabel(osgProducer::Viewer::UFO_MANIPULATOR);
	EnumLabel(osgProducer::Viewer::STATE_MANIPULATOR);
	EnumLabel(osgProducer::Viewer::HEAD_LIGHT_SOURCE);
	EnumLabel(osgProducer::Viewer::SKY_LIGHT_SOURCE);
	EnumLabel(osgProducer::Viewer::STATS_MANIPULATOR);
	EnumLabel(osgProducer::Viewer::VIEWER_MANIPULATOR);
	EnumLabel(osgProducer::Viewer::ESCAPE_SETS_DONE);
	EnumLabel(osgProducer::Viewer::STANDARD_SETTINGS);
END_REFLECTOR

BEGIN_VALUE_REFLECTOR(osgProducer::Viewer)
	BaseType(osgProducer::OsgCameraGroup);
	BaseType(osgGA::GUIActionAdapter);
	Constructor0();
	Constructor1(IN, Producer::CameraConfig *, cfg);
	Constructor1(IN, const std::string &, configFile);
	Constructor1(IN, osg::ArgumentParser &, arguments);
	MethodWithDefaults1(void, setUpViewer, IN, unsigned int, options, osgProducer::Viewer::STANDARD_SETTINGS);
	Method1(void, setDoneAtElapsedTime, IN, double, elapsedTime);
	Method0(double, getDoneAtElapsedTime);
	Method1(void, setDoneAtElapsedTimeEnabled, IN, bool, enabled);
	Method0(bool, getDoneAtElapsedTimeEnabled);
	Method1(void, setDoneAtFrameNumber, IN, unsigned int, frameNumber);
	Method0(unsigned int, getDoneAtFrameNumber);
	Method1(void, setDoneAtFrameNumberEnabled, IN, bool, enabled);
	Method0(bool, getDoneAtFrameNumberEnabled);
	Method1(void, setDone, IN, bool, done);
	Method0(bool, getDone);
	Method0(bool, done);
	Method1(void, setWriteImageWhenDone, IN, bool, enabled);
	Method0(bool, getWriteImageWhenDone);
	Method1(void, setWriteImageFileName, IN, const std::string &, filename);
	Method0(const std::string &, getWriteImageFileName);
	Method1(void, setViewByMatrix, IN, const Producer::Matrix &, pm);
	Method1(bool, realize, IN, ThreadingModel, thread_model);
	Method0(bool, realize);
	Method0(void, update);
	Method1(void, setUpdateVisitor, IN, osg::NodeVisitor *, nv);
	Method0(osg::NodeVisitor *, getUpdateVisitor);
	Method0(const osg::NodeVisitor *, getUpdateVisitor);
	Method1(void, setEventVisitor, IN, osgGA::EventVisitor *, nv);
	Method0(osgGA::EventVisitor *, getEventVisitor);
	Method0(const osgGA::EventVisitor *, getEventVisitor);
	Method0(void, computeActiveCoordindateSystemNodePath);
	Method1(void, setCoordindateSystemNodePath, IN, const osg::RefNodePath &, nodePath);
	Method1(void, setCoordindateSystemNodePath, IN, const osg::NodePath &, nodePath);
	Method0(const osg::RefNodePath &, getCoordindateSystemNodePath);
	Method0(void, frame);
	Method0(void, requestRedraw);
	Method1(void, requestContinuousUpdate, IN, bool, x);
	Method2(void, requestWarpPointer, IN, float, x, IN, float, y);
	Method5(bool, computePixelCoords, IN, float, x, IN, float, y, IN, unsigned int, cameraNum, IN, float &, pixel_x, IN, float &, pixel_y);
	Method5(bool, computeNearFarPoints, IN, float, x, IN, float, y, IN, unsigned int, cameraNum, IN, osg::Vec3 &, near, IN, osg::Vec3 &, far);
	MethodWithDefaults6(bool, computeIntersections, IN, float, x, , IN, float, y, , IN, unsigned int, cameraNum, , IN, osg::Node *, node, , IN, osgUtil::IntersectVisitor::HitList &, hits, , IN, osg::Node::NodeMask, traversalMask, 0xffffffff);
	MethodWithDefaults5(bool, computeIntersections, IN, float, x, , IN, float, y, , IN, unsigned int, cameraNum, , IN, osgUtil::IntersectVisitor::HitList &, hits, , IN, osg::Node::NodeMask, traversalMask, 0xffffffff);
	MethodWithDefaults5(bool, computeIntersections, IN, float, x, , IN, float, y, , IN, osg::Node *, node, , IN, osgUtil::IntersectVisitor::HitList &, hits, , IN, osg::Node::NodeMask, traversalMask, 0xffffffff);
	MethodWithDefaults4(bool, computeIntersections, IN, float, x, , IN, float, y, , IN, osgUtil::IntersectVisitor::HitList &, hits, , IN, osg::Node::NodeMask, traversalMask, 0xffffffff);
	Method1(void, setKeyboardMouse, IN, Producer::KeyboardMouse *, kbm);
	Method0(Producer::KeyboardMouse *, getKeyboardMouse);
	Method0(const Producer::KeyboardMouse *, getKeyboardMouse);
	Method1(void, setKeyboardMouseCallback, IN, osgProducer::KeyboardMouseCallback *, kbmcb);
	Method0(osgProducer::KeyboardMouseCallback *, getKeyboardMouseCallback);
	Method0(const osgProducer::KeyboardMouseCallback *, getKeyboardMouseCallback);
	Method0(osgProducer::Viewer::EventHandlerList &, getEventHandlerList);
	Method0(const osgProducer::Viewer::EventHandlerList &, getEventHandlerList);
	Method0(osgGA::KeySwitchMatrixManipulator *, getKeySwitchMatrixManipulator);
	Method0(const osgGA::KeySwitchMatrixManipulator *, getKeySwitchMatrixManipulator);
	Method1(unsigned int, addCameraManipulator, IN, osgGA::MatrixManipulator *, cm);
	Method1(void, selectCameraManipulator, IN, unsigned int, no);
	Method1(void, getCameraManipulatorNameList, IN, std::list< std::string > &, nameList);
	Method1(bool, selectCameraManipulatorByName, IN, const std::string &, name);
	Method1(osgGA::MatrixManipulator *, getCameraManipulatorByName, IN, const std::string &, name);
	Method1(void, setRecordingAnimationPath, IN, bool, on);
	Method0(bool, getRecordingAnimationPath);
	Method1(void, setAnimationPath, IN, osg::AnimationPath *, path);
	Method0(osg::AnimationPath *, getAnimationPath);
	Method0(const osg::AnimationPath *, getAnimationPath);
	Method0(const double *, getPosition);
	Method0(double, getSpeed);
	Method0(osg::Quat, getOrientation);
	Method1(void, getUsage, IN, osg::ApplicationUsage &, usage);
	Method0(void, updatedSceneData);
	Property(osg::AnimationPath *, AnimationPath);
	Property(const osg::RefNodePath &, CoordindateSystemNodePath);
	Property(bool, Done);
	Property(double, DoneAtElapsedTime);
	Property(bool, DoneAtElapsedTimeEnabled);
	Property(unsigned int, DoneAtFrameNumber);
	Property(bool, DoneAtFrameNumberEnabled);
	ReadOnlyProperty(osgProducer::Viewer::EventHandlerList &, EventHandlerList);
	Property(osgGA::EventVisitor *, EventVisitor);
	ReadOnlyProperty(osgGA::KeySwitchMatrixManipulator *, KeySwitchMatrixManipulator);
	Property(Producer::KeyboardMouse *, KeyboardMouse);
	Property(osgProducer::KeyboardMouseCallback *, KeyboardMouseCallback);
	ReadOnlyProperty(osg::Quat, Orientation);
	ReadOnlyProperty(const double *, Position);
	Property(bool, RecordingAnimationPath);
	ReadOnlyProperty(double, Speed);
	WriteOnlyProperty(unsigned int, UpViewer);
	Property(osg::NodeVisitor *, UpdateVisitor);
	WriteOnlyProperty(const Producer::Matrix &, ViewByMatrix);
	Property(const std::string &, WriteImageFileName);
	Property(bool, WriteImageWhenDone);
END_REFLECTOR

STD_LIST_REFLECTOR(std::list< osg::ref_ptr< osgGA::GUIEventHandler > >);

STD_LIST_REFLECTOR(std::list< std::string > &);

