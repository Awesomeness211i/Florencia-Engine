module;
#include <stdint.h>
export module LinuxWindow;
import Window;

export namespace Florencia {

	class LinuxWindow : public Window {
	public:
		LinuxWindow(const WindowProps& props) {

		}

		~LinuxWindow() {

		}

		void Update() override {

		}

		uint32_t GetWidth() const override { return 0; }
		uint32_t GetHeight() const override { return 0; }

		//Window Attributes
		void SetWidth(uint32_t width) override {}
		void SetHeight(uint32_t height) override {}

		void* GetWindowHandle() override { return nullptr; }
	private:

	};

}