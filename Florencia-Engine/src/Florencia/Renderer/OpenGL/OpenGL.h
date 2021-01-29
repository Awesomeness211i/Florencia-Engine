#pragma once
#include <Renderer/Renderer.h>

namespace Florencia {

	class OpenGL : public Renderer {
	public:
		OpenGL(API api);

		void Init(void* window) override;

		void Clear() override;
		void SetClearColor(float r, float g, float b, float a) override;
	private:

	};

}