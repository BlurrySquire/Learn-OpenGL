#ifndef RENDERER_HPP
#define RENDERER_HPP

#ifdef _DEBUG
#define GL_CALL(function) \
		Renderer::GL_ClearErrors(); \
		function; \
		Renderer::GL_LogError(#function, __FILE__, __LINE__);
#else
#define GL_CALL(function) function
#endif

namespace Renderer {
	void GL_ClearErrors();
	void GL_LogError(const char* function, const char* file, const int line);
}

#endif