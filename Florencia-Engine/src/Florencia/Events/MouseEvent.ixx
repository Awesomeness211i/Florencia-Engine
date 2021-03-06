export module MouseEvent;
export import Event;
import MouseCodes;

import <stdint.h>;
import <sstream>;

export namespace Florencia {

	class MouseButtonEvent : public Event {
	public:
		MouseButton GetMouseButton() const { return m_Button; }
		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput | (int)EventCategory::EventCategoryMouseButton; }
	protected:
		MouseButtonEvent(const MouseButton button) : m_Button(button) {}
		MouseButton m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(const MouseButton button) : MouseButtonEvent(button) {}

		const char* GetName() const override { return "MouseButtonPressed"; }
		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		EventType GetEventType() const override { return GetStaticType(); }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << (uint16_t)m_Button;
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(const MouseButton button) : MouseButtonEvent(button) {}

		const char* GetName() const override { return "MouseButtonReleased"; }
		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		EventType GetEventType() const override { return GetStaticType(); }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << (uint16_t)m_Button;
			return ss.str();
		}
	};

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(const float x, const float y) : m_X(x), m_Y(y) {}

		float GetX() const { return m_X; }
		float GetY() const { return m_Y; }

		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput; }

		const char* GetName() const override { return "MouseMoved"; }
		static EventType GetStaticType() { return EventType::MouseMoved; }
		EventType GetEventType() const override { return GetStaticType(); }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_X << ", " << m_Y;
			return ss.str();
		}
	private:
		float m_X, m_Y;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		int GetCategoryFlags() const override { return (int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput; }

		const char* GetName() const override { return "MouseScrolled"; }
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		EventType GetEventType() const override { return GetStaticType(); }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}
	private:
		float m_XOffset, m_YOffset;
	};

}