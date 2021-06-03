#pragma once
#include <Florencia/Core/Window.h>
#include <Florencia/Renderer/Renderer.h>

#include <Florencia/Core/Layer.h>
#include <Florencia/Core/LayerStack.h>

namespace Florencia {

	/*struct ApplicationProps {
		ApplicationProps(const std::string& title, Uint32 width = 1080, Uint32 height = 720, bool vsync = true)
			: VSync(vsync), Title(title), Width(width), Height(height) {}
		bool VSync;
		std::string Title;
		Uint32 Width, Height;
	};*/

	class Application {
	public:
		Application(const WindowProps& props);
		virtual ~Application();

		void Run();

		void AddLayer(Layer* layer);
		void AddOverlay(Layer* layer);
		void RemoveLayer(Layer* layer);
		void RemoveOverlay(Layer* layer);

		Window* GetWindow() { return m_Window; }
		
	private:
		Window* m_Window;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		bool m_Running = true, m_Minimized = false;
	};

	Application* CreateApplication();
}