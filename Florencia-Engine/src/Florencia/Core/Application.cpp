module Application;

namespace Florencia {

	Application::Application(const WindowProps& props) {
		m_Window = Window::Create(props);
		if (m_Window) [[likely]] {
			m_Window->SetEventCallback([this](Event& e) -> void { return this->Application::OnEvent(e); });
			m_Context = GraphicsContext::Create(m_Window);
			if (m_Context) [[likely]] { m_Context->Init(); }
		}

		Renderer::Init();
	}

	Application::~Application() {
		if (m_Context) [[likely]] { delete m_Context; }
		if (m_Window) [[likely]] { delete m_Window; }
	}

	void Application::Run() {
		while (m_Running) {
			//time is in seconds
			m_LastTick = Time();
			if (!m_Minimized) [[likely]] {
				if (m_Window) [[likely]] { m_Window->OnUpdate(); }
				Time nextTime = Time();
				Timestep ts(m_LastTick, nextTime);
				m_LastTick = nextTime;
				for (auto layer : m_LayerStack) {
					layer->Update(ts);
					layer->Render();
				}
				if (m_Context) [[likely]] { m_Context->SwapBuffers(); }
			}
		}
	}

	void Application::OnEvent(Event& e) {
		EventHandler.Dispatch<WindowCloseEvent>(e, [this](WindowCloseEvent& e) -> bool { return this->Application::OnWindowClose(e); });
		EventHandler.Dispatch<WindowResizeEvent>(e, [this](WindowResizeEvent& e) -> bool { return this->Application::OnWindowResize(e); });

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (e.Handled) break;
			(*it)->OnEvent(e);
		}
	}

	void Application::AddLayer(Layer* layer) {
		m_LayerStack.AddLayer(layer);
		layer->OnAdd();
	}

	void Application::AddOverlay(Layer* layer) {
		m_LayerStack.AddOverlay(layer);
		layer->OnAdd();
	}

	void Application::RemoveLayer(Layer* layer) {
		m_LayerStack.RemoveLayer(layer);
		layer->OnRemove();
	}

	void Application::RemoveOverlay(Layer* layer) {
		m_LayerStack.RemoveOverlay(layer);
		layer->OnRemove();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) [[unlikely]] { m_Minimized = true; }
		else [[likely]] { m_Minimized = false; Renderer::OnWindowResize(e.GetWidth(), e.GetHeight()); }
		return false;
	}

}