module;
#include <iostream>
export module EditorLayer;
import Florencia;

export namespace Florencia {

	class EditorLayer : public Layer {
	public:
		EditorLayer() {

		}

		~EditorLayer() = default;

		void OnAdd() override {

		}

		void OnRemove() override {

		}

		void Render() override {

		}

		void Update(Timestep ts) override {
			std::cout << ts << "\n";
		}

		void OnEvent(Event& e) override {
			EventHandler.Dispatch<KeyPressedEvent>(e, [this](KeyPressedEvent& e) -> bool { return this->EditorLayer::OnKeyPressed(e); });
			EventHandler.Dispatch<KeyReleasedEvent>(e, [this](KeyReleasedEvent& e) -> bool { return this->EditorLayer::OnKeyReleased(e); });

			EventHandler.Dispatch<MouseMovedEvent>(e, [this](MouseMovedEvent& e) -> bool { return this->EditorLayer::OnMouseMoved(e); });
			EventHandler.Dispatch<MouseScrolledEvent>(e, [this](MouseScrolledEvent& e) -> bool { return this->EditorLayer::OnMouseScrolled(e); });
			EventHandler.Dispatch<MouseButtonPressedEvent>(e, [this](MouseButtonPressedEvent& e) -> bool { return this->EditorLayer::OnMousePressed(e); });
			EventHandler.Dispatch<MouseButtonReleasedEvent>(e, [this](MouseButtonReleasedEvent& e) -> bool { return this->EditorLayer::OnMouseReleased(e); });
		}

		bool OnKeyPressed(KeyPressedEvent& e) {
			return true;
		}

		bool OnKeyReleased(KeyReleasedEvent& e) {
			return true;
		}

		bool OnMousePressed(MouseButtonPressedEvent& e) {
			return true;
		}

		bool OnMouseReleased(MouseButtonReleasedEvent& e) {
			return true;
		}

		bool OnMouseMoved(MouseMovedEvent& e) {
			return true;
		}

		bool OnMouseScrolled(MouseScrolledEvent& e) {
			return true;
		}

		const char* GetName() const { return "EditorLayer"; }
	};

}