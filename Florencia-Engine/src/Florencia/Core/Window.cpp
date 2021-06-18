module;
#include <Florencia/Core/PlatformDetection.h>
module Window;
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
import Wwindow;
#elif defined(FLO_PLATFORM_LINUX)
import LinuxWindow;
#elif defined(FLO_PLATFORM_MACOS)
import MacWindow;
#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
import IPhoneWindow;
#elif defined(FLO_PLATFORM_ANDROID)
import AndroidWindow;
#endif

namespace Florencia {

	Window* Window::Create(const WindowProps& props) {
		switch (s_Platform) {
			case Window::Platform::None: return nullptr;
			#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
			case Window::Platform::Windows: return new Wwindow(props);
			#elif defined(FLO_PLATFORM_MACOS)
			case Window::Platform::MacOS: return new MacWindow(props);
			#elif defined(FLO_PLATFORM_LINUX)
			case Window::Platform::Linux: return new LinuxWindow(props);
			#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
			case Window::Platform::IPhone: return new IPhoneWindow(props);
			#elif defined(FLO_PLATFORM_ANDROID)
			case Window::Platform::Android: return new AndroidWindow(props);
			#endif
		}
		return nullptr;
	}
}