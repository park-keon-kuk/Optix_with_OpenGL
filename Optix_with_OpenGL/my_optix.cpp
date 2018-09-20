#include <gl/glew.h>
#include "my_optix.h"
#include "gui.h"
#include <string>
#include <fstream>
#include <sstream>

// 함수 선언
/**********************************************************************/
std::string load_file(const char* filepath);


// 메소드 구현
/**********************************************************************/

MyOptix::~MyOptix()
{
	// 종료
	/**********************************************************************/
	rtBufferDestroy(m_buffer);
	rtProgramDestroy(m_program);
	rtContextDestroy(m_context);

	glDeleteTextures(1, &m_opengl_texture_id);
}

bool MyOptix::initialize(int width, int height)
{
	m_width = width;
	m_height = height;

	// Optix
	/************************************************************************/
	unsigned int result = 0;

	// Context
	result += rtContextCreate(&m_context);
	result += rtContextSetRayTypeCount(m_context, 1);
	result += rtContextSetEntryPointCount(m_context, 1);

	// Buffer
	result += rtBufferCreate(m_context, RT_BUFFER_OUTPUT, &m_buffer);
	result += rtBufferSetFormat(m_buffer, RT_FORMAT_FLOAT4);
	result += rtBufferSetSize2D(m_buffer, m_width, m_height);
	result += rtContextDeclareVariable(m_context, "result_buffer", &m_result_buffer);
	result += rtVariableSetObject(m_result_buffer, m_buffer);

	// Program
	std::string ptx = load_file("./cuda/test.ptx");
	result += rtProgramCreateFromPTXString(m_context, ptx.c_str(), "draw_solid_color", &m_program);
	result += rtProgramDeclareVariable(m_program, "draw_color", &m_draw_color);
	result += rtVariableSet3f(m_draw_color, 1.f, 0.f, 0.f);
	result += rtContextSetRayGenerationProgram(m_context, 0, m_program);

	result += rtContextValidate(m_context);

	// GL
	/************************************************************************/
	
	// Texture
	glGenTextures(1, &m_opengl_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_opengl_texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	return (result == 0) && (m_opengl_texture_id != 0);
}

void MyOptix::launch()
{
	RTresult result;
	result = rtContextLaunch2D(m_context, 0 /* entry point */, m_width, m_width);
}

void MyOptix::update_opengl_texture()
{
	if (!m_context)
		return;

	// Take
	optix::Buffer buffer = optix::Buffer::take(m_buffer);

	// Query
	RTsize buffer_width_rts, buffer_height_rts;
	buffer->getSize(buffer_width_rts, buffer_height_rts);
	uint32_t width = static_cast<int>(buffer_width_rts);
	uint32_t height = static_cast<int>(buffer_height_rts);
	RTformat buffer_format = buffer->getFormat();

	// Bind
	glBindTexture(GL_TEXTURE_2D, m_opengl_texture_id);

	// Load
	const unsigned pboId = buffer->getGLBOId();
	GLvoid* imageData = 0;
	if (pboId)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboId);
	else
		imageData = buffer->map(0, RT_BUFFER_MAP_READ);

	RTsize elmt_size = buffer->getElementSize();
	if (elmt_size % 8 == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
	else if (elmt_size % 4 == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	else if (elmt_size % 2 == 0) glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
	else                          glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Update
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, imageData);

	// Release
	if (pboId)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	else
		buffer->unmap();

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
}

void MyOptix::render()
{
	glViewport(0, 0, g_width, g_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_opengl_texture_id);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}


// 함수 구현
/**********************************************************************/
std::string load_file(const char * filepath)
{
	std::ifstream in(filepath);

	if (!in) {
		printf("%s 파일이 없습니다.", filepath);
		return std::string("");
	}

	std::stringstream stream;
	stream << in.rdbuf();

	return stream.str();
}
