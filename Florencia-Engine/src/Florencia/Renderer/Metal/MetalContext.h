#pragma once
#include <Florencia/Renderer/GraphicsContext.h>

namespace Florencia {

	class MetalContext : public GraphicsContext {
	public:
		MetalContext(void* windowHandle, bool vsync);
		
		void Init() override;
		void SwapBuffers() override;
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
	private:

	};

}