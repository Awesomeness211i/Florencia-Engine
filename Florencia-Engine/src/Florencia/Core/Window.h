#pragma once
#include <functional>
#include <Math/FloMath.h>

namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, Uint32 width, Uint32 height, bool vsync)
			: VSync(vsync), Title(title), Width(width), Height(height) {}
		bool VSync = true;
		std::string Title = "";
		Uint32 Width = 0, Height = 0;
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual bool OnUpdate() = 0;

		virtual Uint32 GetWidth() const = 0;
		virtual Uint32 GetHeight() const = 0;

		//Window Attributes
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SetWidth(Uint32 width) = 0;
		virtual void SetHeight(Uint32 height) = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProps& props);
	};
}
