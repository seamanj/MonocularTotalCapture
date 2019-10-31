#pragma once
#include "VisualizedData.h"
#include <string>
#include <opencv2/opencv.hpp>

// using namespace adam
// {
class Renderer
{
public:
	Renderer(int* argc, char** argv);
    ~Renderer()
    {
        free( buffer );
        OSMesaDestroyContext( ctx );
    }
	void RenderHand(VisualizedData& g_visData);
	void RenderHandSimple(VisualizedData& g_visData);
	void RenderDepthMap(VisualizedData& g_visData);
	void RenderProjection(VisualizedData& g_visData);
	// static void IdleSaveImage();
    void RenderAndRead();
	static void RenderAndReadDepthMap();
	static void RenderAndReadProjection();
	void Display();
	static VisualizationOptions options;
	void NormalMode(uint position=0u, int width=600, int height=600);
	void CameraMode(uint position=0u, int width=1920, int height=1080, double* calibK=NULL);
	void OrthoMode(float scale, uint position=0u);
	static bool use_color_fbo;
    GLubyte *buffer;
private:
	//initialization functions
	void simpleInit(); // my simple way of initialization
	void InitGraphics();
	static const std::string SHADER_ROOT;
    static GLuint g_shaderProgramID[9];
    enum draw_mode {MODE_DRAW_DEFUALT=0, MODE_DRAW_SELECTION_PTCLOUD=1, MODE_DRAW_DEPTH_RENDER=2, MODE_DRAW_NORMALMAP=3,
                    MODE_DRAW_PTCLOUD=4, MODE_DRAW_MESH=5, MODE_DRAW_MESH_TEXTURE=6, MODE_DRAW_PROJECTION=7,
                    MODE_DRAW_REDTRI=8};
	void SetShader(const std::string shaderName, GLuint& programId);
	GLuint LoadShaderFiles(const char* vertex_file_path, const char* fragment_file_path, bool verbose=false);

	//global variables
	static int g_drawMode;
	static GLuint g_vao;		//Vertex Array: only need one, before starting opengl window
	static GLuint g_vertexBuffer, g_uvBuffer, g_normalBuffer, g_indexBuffer;	//Vertex Buffer. 
	static GLuint g_fbo_color, g_fbo_depth, g_fbo_rgbfloat;		//frame buffer object
	static GLuint g_colorTexture, g_depthTexture, g_rgbfloatTexture, g_imageTexture;
	static GLuint g_depth_renderbuffer;
	static int g_depthRenderViewPortW, g_depthRenderViewPortH;
	static int g_colorTextureBufferWidth, g_colorTextureBufferHeight;
	static GLint window_id;

	//pointer to data
	static VisualizedData* pData;

    // tj : pointer to buffer

    static OSMesaContext ctx;


	//Call back functions
	static void reshape(int w, int h);
	// static void CameraModeReshape(int w, int h);
	static void SimpleRenderer();
	static void MeshRender();
	static void DepthMapRenderer();
	static void DrawSkeleton(double* joints, uint vis_type, std::vector<int> connMat);
	static void SpecialKeys(const int key, const int x, const int y);
	static void IdleReadBuffer();
	static void ProjectionRenderer();
};
// }
