/*
Copyright (c) 2018, Fabian Prada and Michael Kazhdan
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer. Redistributions in binary form must reproduce
the above copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the distribution. 

Neither the name of the Johns Hopkins University nor the names of its contributors
may be used to endorse or promote products derived from this software without specific
prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.
*/
#ifndef TEXTURED_MESH_VISUALIZATION_INCLUDED
#define TEXTURED_MESH_VISUALIZATION_INCLUDED

#if 1
#else
// Enabling this removes warnings, however it does something weird to the camera.
#define GLM_FORCE_RADIANS
#endif

#include <GL/glew.h>
#include <GL/glut.h> 
#include <Misha/Visualization.h>
#include <GLSL/GLSLProgram.h>
#include <GLSL/GLSLCamera.h>

#include <Misha/Image.h>
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif // M_PI


enum {
	ONE_REGION_DISPLAY,
	TWO_REGION_DISPLAY,
	THREE_REGION_DISPLAY,
	FOUR_REGION_DISPLAY,
};

class TexturedMeshVisualization : public Visualization {
public:
	TexturedMeshVisualization();

	//For visualization of normal maps
	void PhongShading(GLuint & textureBufferId);
	GLSLProgram * normalProgram;
	vec3 light_ambient;
	vec3 light_diffuse;
	vec3 light_specular;
	vec3 light_direction;
	float specular_fallof;
	GLuint vertexHandle = 0;
	//

	GLuint offscreen_depth_texture = 0;
	GLuint offscreen_color_texture = 0;
	GLuint offscreen_framebuffer_handle = 0;
	int offscreen_frame_width, offscreen_frame_height;
	void SetupOffScreenBuffer();
	void RenderOffScreenBuffer(Image<Point3D<float>> & image);

	std::vector< Point3D<float>> boundaryEdgeVertices;
	bool showBoundaryEdges;
	bool useNearestSampling;

	int displayMode;
	int _screenWidth;
	int _screenHeight;
	void UpdateMainFrameSize();

	Camera camera;
	vec3 center;
	float radius;
	float zoom;
	int oldX, oldY, newX, newY;

	std::vector< Point3D<float>> colors;
	std::vector< Point3D<float>> normals;
	std::vector< Point3D<float>> vertices;
	std::vector< TriangleIndex > triangles;
	std::vector< Point2D<float> > textureCoordinates;
	Image<Point3D<float>> textureImage;

	GLfloat lightAmbient[4], lightDiffuse[4], lightSpecular[4], lightPosition[4], shapeDiffuse[4], shapeAmbient[4], shapeSpecular[4], shapeSpecularShininess;
	bool showEdges;
	bool showMesh;
	bool rotating, scaling, panning;

	//Line drawing parameters
	double polygonOffsetFactor = 1.0;
	double polygonOffsetUnits = 1.0;
	double lineWidth = 1.0;

	//double nearPlane;
	//double farPlane;

	GLuint vertexBuffer = 0;
	GLuint normalBuffer = 0;
	GLuint colorBuffer = 0;
	GLuint faceBuffer = 0;
	GLuint coordinateBuffer = 0;
	GLuint textureBuffer = 0;

	void UpdateVertexBuffer();
	void UpdateFaceBuffer();
	void UpdateTextureBuffer();

	GLuint vbo;
	GLuint ebo;

	void keyboardFunc(unsigned char key, int x, int y);
	void display(void);
	void mouseFunc(int button, int state, int x, int y);
	void motionFunc(int x, int y);
	static void WriteSceneConfigurationCallBack(Visualization* v, const char* prompt);
	static void ShowEdgesCallBack(Visualization* v, const char*) {
		TexturedMeshVisualization* av = (TexturedMeshVisualization*)v;
		av->showEdges = !av->showEdges;
	}
	static void ToggleVisualizationMode(Visualization* v, const char*) {
		TexturedMeshVisualization* av = (TexturedMeshVisualization*)v;
		av->showMesh = !av->showMesh;
	}
	static void ShowBoundaryEdgesCallBack(Visualization* v, const char*) {
		TexturedMeshVisualization* av = (TexturedMeshVisualization*)v;
		av->showBoundaryEdges = !av->showBoundaryEdges;
	}
	static void NearestSamplingCallBack(Visualization* v, const char*) {
		TexturedMeshVisualization* av = (TexturedMeshVisualization*)v;
		av->useNearestSampling = !av->useNearestSampling;
	}

	static void ReadSceneConfigurationCallBack(Visualization* v, const char* prompt);
	static void ScreenshotCallBack(Visualization* v, const char* prompt);

	Point2D<float> selectImagePos(int x, int y);
	Point< float, 2 > screenToImage(int x, int y);
	bool select(int x, int  y, Point3D< float >& out);


	void SetLightingData();
	void SetTextureCamera();
	void SetGeometryCamera();
	void DrawTexture(GLuint & textureBufferId);
	void DrawGeometry(GLuint & textureBufferId, bool phongShading = false, bool modulateLight = false);
	void DrawRegion(bool drawGeometry, GLuint & textureBufferId, bool phongShading = false, bool modulateLight = false);

	// Texture stuff
	struct ImageTransform
	{
		float zoom;
		float offset[2];
		ImageTransform(void) { offset[0] = offset[1] = 0.f, zoom = 1.f; }
	};

	ImageTransform xForm;
	float imageToScreenScale(void) const;
	Point< float, 2 > imageToScreen(float px, float py) const;
};

#include "TexturedMeshVisualization.inl"
#endif//TEXTURED_MESH_VISUALIZATION_INCLUDED
