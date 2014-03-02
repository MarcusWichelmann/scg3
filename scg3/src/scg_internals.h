/**
 * \file scg_internals.h
 * \brief Internal definitions required by most classes.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */


#ifndef SCG_INTERNALS_H_
#define SCG_INTERNALS_H_

#include <memory>
#include <string>
#include <utility>
#include "scg_glew.h"

namespace scg {


/*
 * Ensure that required C++11 extensions are supported by compiler.
 * Currently used C++11 features:
 *   auto-typed variables
 *   rvalue references
 *   strongly-typed enums (if available, workaround provided)
 *   nullptr keyword (if available, workaround provided)
 *   range-based for (if available, workaround provided)
 *   initializer lists (optional, only in application)
 *   lambda functions (optional, only in application)
 *   library functional: function objects, bind
 *   library memory: smart pointers
 *   library random
 */


#if defined __clang__
// --- Clang ---

#if __has_feature(cxx_generalized_initializers)
#define SCG_CPP11_INITIALIZER_LISTS
#endif

#if __has_feature(cxx_lambdas)
#define SCG_CPP11_LAMBDA_FUNCTIONS
#endif

#if __has_feature(cxx_nullptr)
#define SCG_CPP11_NULLPTR
#endif

#if __has_feature(cxx_range_for)
#define SCG_CPP11_RANGE_BASED_FOR
#endif

#if __has_feature(cxx_strong_enums)
#define SCG_CPP11_STRONGLY_TYPED_ENUMS
#endif

#else
#if defined __GNUC__
// --- GCC ---

// ensure GCC version 4.4 or higher is used
#define SCG_GCC_VERSION (100 * __GNUC__ + __GNUC_MINOR__)
#if SCG_GCC_VERSION < 404   // GCC < 4.4
#error GCC 4.4 or higher is required.
#endif

// check which C++11 features are available
#if SCG_GCC_VERSION >= 404  // GCC >= 4.4
#define SCG_CPP11_STRONGLY_TYPED_ENUMS
#endif

#if SCG_GCC_VERSION >= 405  // GCC >= 4.5
#define SCG_CPP11_LAMBDA_FUNCTIONS
#endif

#if SCG_GCC_VERSION >= 406  // GCC >= 4.6
#define SCG_CPP11_NULLPTR
#define SCG_CPP11_RANGE_BASED_FOR
#define SCG_CPP11_INITIALIZER_LISTS
#endif

#else
#if defined _MSC_VER
// --- Visual C++ ---

// ensure Visual C++ compiler version 16.00 (Visual Studio 2010) or higher is used
#if _MSC_VER < 1600   // Visual C++ compiler < 16.00
#error Visual C++ compiler version 16.00 (Visual Studio 2010) or higher is required.
#endif

// check which C++11 features are available
#if _MSC_VER >= 1600   // Visual C++ compiler >= 16.00 (Visual Studio 2010)
#define SCG_CPP11_LAMBDA_FUNCTIONS
#define SCG_CPP11_NULLPTR
#endif

#if _MSC_VER >= 1700   // Visual C++ compiler >= 17.00 (Visual Studio 2012)
#define SCG_CPP11_STRONGLY_TYPED_ENUMS
#define SCG_CPP11_RANGE_BASED_FOR
#endif

// SCG_CPP11_INITIALIZER_LISTS is not yet supported by Visual C++

#else
// --- neither GCC nor Visual C++ ---

#error Unknown compiler: only Clang, GCC, and Visual C++ are supported.

#endif      // _MSC_VER

#endif      // __GNUC__

#endif      // __clang__

// define C++11 nullptr keyword if not supported
#ifndef SCG_CPP11_NULLPTR
#define nullptr 0  // quick-and-dirty solution
#endif


/**
 * Forward declaration of classes with shared and unique pointers.\n
 *   Class\n
 *   ClassSP - shared_pointer<Class>\n
 *   classUP - unique_pointer<Class>
 */
#define SCG_DECLARE_CLASS(TypeName) \
    class TypeName; \
    typedef std::shared_ptr<TypeName> TypeName##SP; \
    typedef std::unique_ptr<TypeName> TypeName##UP;

SCG_DECLARE_CLASS(Animation);
SCG_DECLARE_CLASS(BumpMapCore);
SCG_DECLARE_CLASS(Camera);
SCG_DECLARE_CLASS(CameraController);
SCG_DECLARE_CLASS(Composite);
SCG_DECLARE_CLASS(Controller);
SCG_DECLARE_CLASS(ColorCore);
SCG_DECLARE_CLASS(Core);
SCG_DECLARE_CLASS(CubeMapCore);
SCG_DECLARE_CLASS(GeometryCore);
SCG_DECLARE_CLASS(GeometryCoreFactory);
SCG_DECLARE_CLASS(Group);
SCG_DECLARE_CLASS(InfoTraverser);
SCG_DECLARE_CLASS(KeyboardController);
SCG_DECLARE_CLASS(Leaf);
SCG_DECLARE_CLASS(Light);
SCG_DECLARE_CLASS(LightPosition);
SCG_DECLARE_CLASS(MaterialCore);
SCG_DECLARE_CLASS(MouseController);
SCG_DECLARE_CLASS(Node);
SCG_DECLARE_CLASS(OrthographicCamera);
SCG_DECLARE_CLASS(PerspectiveCamera);
SCG_DECLARE_CLASS(PreTraverser);
SCG_DECLARE_CLASS(Renderer);
SCG_DECLARE_CLASS(RenderState);
SCG_DECLARE_CLASS(RenderTraverser);
SCG_DECLARE_CLASS(ShaderCore);
SCG_DECLARE_CLASS(ShaderCoreFactory);
SCG_DECLARE_CLASS(Shape);
SCG_DECLARE_CLASS(StandardRenderer);
SCG_DECLARE_CLASS(TextureCore);
SCG_DECLARE_CLASS(Texture2DCore);
SCG_DECLARE_CLASS(TransformAnimation);
SCG_DECLARE_CLASS(Transformation);
SCG_DECLARE_CLASS(Traverser);
SCG_DECLARE_CLASS(Viewer);
SCG_DECLARE_CLASS(ViewState);


/**
 * Macros causing compiler errors for obsolete classes and functions.
 */
#define CameraTransformation Error_scg3_CameraTransformation_is_obsolete_Use_Camera_instead


/**
 * A macro to disallow the copy constructor and operator= functions.
 * This should be used in the private: declarations for a class.
 * Source: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 */
#define SCG_DISALLOW_COPY_AND_ASSIGN(TypeName)  \
    TypeName(const TypeName&);                  \
    void operator=(const TypeName&);


/**
 * \brief Attribute name and location.
 */
struct OGLAttrib {
  const GLchar* name;
  GLuint location;
};


/**
 * \brief Fragment data name and location.
 */
struct OGLFragData {
  const GLchar* name;
  GLuint location;
};


/**
 * \brief Uniform block name and index.
 */
struct OGLUniformBlock {
  const GLchar* name;
  GLuint bindingPoint;
};


/**
 * \brief Sampler name and texture unit.
 */
struct OGLSampler {
  const GLchar* name;
  GLuint texUnit;
};


/**
 * \brief OpenGL attribute names and locations, uniform names, etc.,
 * to be used by ShaderCore, ShaderCoreFactory, and GeometryCore.
 */
class OGLConstants {

public:

  /**
   * Bind standard attribute and fragment data locations defined above,
   * to be called by ShaderCoreFactory.
   */
  static void bindAttribFragDataLocations(GLuint program);

  /**
   * Bind uniform block indices defined above,
   * to be called by ShaderCoreFactory.
   */
  static void bindUniformBlocks(GLuint program);

  /**
   * Bind uniform sampler texture units defined above,
   * to be called by ShaderCoreFactory.
   */
  static void bindSamplers(GLuint program);

public:

  // attribute names and locations, defined in internals.cpp
  static const OGLAttrib VERTEX;
  static const OGLAttrib COLOR;
  static const OGLAttrib NORMAL;
  static const OGLAttrib TEX_COORD_0;
  static const OGLAttrib TEX_COORD_1;
  static const OGLAttrib TANGENT;
  static const OGLAttrib BINORMAL;

  // fragment data names and locations, defined in internals.cpp
  static const OGLFragData FRAG_COLOR;

  // uniform block names and indices, defined in internals.cpp
  static const OGLUniformBlock LIGHT;
  static const OGLUniformBlock MATERIAL;

  // uniform names
  static const char* MODEL_VIEW_MATRIX;
  static const char* PROJECTION_MATRIX;
  static const char* MVP_MATRIX;
  static const char* NORMAL_MATRIX;
  static const char* TEXTURE_MATRIX;
  static const char* COLOR_MATRIX;
  static const char* N_LIGHTS;
  static const char* GLOBAL_AMBIENT_LIGHT;
  static const char* TIME;

  // sampler names and texture units
  static const OGLSampler TEXTURE0;
  static const OGLSampler TEXTURE1;

  // parameters
  static const int MAX_NUMBER_OF_LIGHTS = 10;

};

} /* namespace scg */


#endif /* SCG_INTERNALS_H_ */