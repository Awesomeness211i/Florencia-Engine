module;
#include <iostream>
#include <unordered_map>
export module EditorLayer;
import Florencia;

export namespace Florencia {

	class EditorLayer : public Layer {
	public:
		EditorLayer() = default;
		~EditorLayer() = default;

		void OnAdd() override {

		}

		void OnRemove() override {

		}

		void Update(Timestep ts) override {

		}

		void Render() override {

		}

		bool OpenConsole() {
			m_Console = Console::Create();
			if (m_Console) [[likely]] {
				m_Console->CreateNewConsole();
				ConsoleOpen = true;
			}
			return true;
		}

		bool CloseConsole() {
			if (m_Console) [[likely]] {
				m_Console->ReleaseConsole();
				delete m_Console;
				m_Console = nullptr;
				ConsoleOpen = false;
			}
			return true;
		}

		void OnEvent(Event& e) override {
			EventHandler.Dispatch<KeyPressedEvent>(e, [this](KeyPressedEvent& e) -> bool { return this->EditorLayer::OnKeyPressed(e); });
			EventHandler.Dispatch<KeyReleasedEvent>(e, [this](KeyReleasedEvent& e) -> bool { return this->EditorLayer::OnKeyReleased(e); });
			EventHandler.Dispatch<CharacterTypedEvent>(e, [this](CharacterTypedEvent& e) -> bool { return this->EditorLayer::OnCharacterTyped(e); });

			EventHandler.Dispatch<MouseMovedEvent>(e, [this](MouseMovedEvent& e) -> bool { return this->EditorLayer::OnMouseMoved(e); });
			EventHandler.Dispatch<MouseScrolledEvent>(e, [this](MouseScrolledEvent& e) -> bool { return this->EditorLayer::OnMouseScrolled(e); });
			EventHandler.Dispatch<MouseButtonPressedEvent>(e, [this](MouseButtonPressedEvent& e) -> bool { return this->EditorLayer::OnMousePressed(e); });
			EventHandler.Dispatch<MouseButtonReleasedEvent>(e, [this](MouseButtonReleasedEvent& e) -> bool { return this->EditorLayer::OnMouseReleased(e); });
		}

		bool OnCharacterTyped(CharacterTypedEvent& e) {
			return true;
		}

		bool OnKeyPressed(KeyPressedEvent& e) {
			m_KeyPressed[e.GetKeyCode()] = true;
			m_KeyReleased[e.GetKeyCode()] = false;
			return true;
		}

		bool OnKeyReleased(KeyReleasedEvent& e) {
			m_KeyPressed[e.GetKeyCode()] = false;
			m_KeyReleased[e.GetKeyCode()] = true;
			return true;
		}

		bool OnMousePressed(MouseButtonPressedEvent& e) {
			return true;
		}

		bool OnMouseReleased(MouseButtonReleasedEvent& e) {
			return true;
		}

		bool OnMouseMoved(MouseMovedEvent& e) {
			std::cout << e << "\n";
			return true;
		}

		bool OnMouseScrolled(MouseScrolledEvent& e) {
			return true;
		}

		const char* GetName() const { return "EditorLayer"; }

	private:
		Console* m_Console;
		bool ConsoleOpen = false;
		std::unordered_map<Key, bool> m_KeyPressed;
		std::unordered_map<Key, bool> m_KeyReleased;
	};

}