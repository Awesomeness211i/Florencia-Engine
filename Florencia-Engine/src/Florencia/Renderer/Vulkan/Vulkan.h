#pragma once
#include <Renderer/RenderAPI.h>

namespace Florencia {

	class Vulkan : public RenderAPI {
	public:
		void Init(void* window) override;
		void Clear() override;
		void SetClearColor(float r, float g, float b, float a) override;
	private:

	};

}