export module WindowsConsole;
import <stdint.h>;
import Console;

export namespace Florencia {

	class WindowsConsole final : public Console {
	public:
		WindowsConsole(int16_t minLength = 1024);
		~WindowsConsole();

		bool AllocateConsole() override;
		bool ReleaseConsole() override;

	private:
		void AdjustConsoleBuffer();
		bool AttachParentConsole();
		bool RedirectConsoleIO();

		int16_t m_MinLength;
	};
}

module: private;
#define WIN32_LEAN_AND_MEAN
import <Windows.h>;
import <stdexcept>;
import <iostream>;

namespace Florencia {

	WindowsConsole::WindowsConsole(int16_t minLength) : m_MinLength(minLength) { AllocateConsole(); }

	WindowsConsole::~WindowsConsole() { ReleaseConsole(); }

	bool WindowsConsole::AllocateConsole() {
		bool result = false;
		// Release any current console and redirect IO to NUL
		if(!ReleaseConsole()) {
			throw std::runtime_error("Failed to Allocate Console");
		}

		// Attempt to create new console
		if(AllocConsole()) {
			AdjustConsoleBuffer();
			result = RedirectConsoleIO();
		}

		return result;
	}

	bool WindowsConsole::ReleaseConsole() {
		bool result = true;
		FILE* fp;
		// Just to be safe, redirect standard IO to NUL before releasing.

		// Redirect STDIN to NUL
		if(freopen_s(&fp, "NUL:", "r", stdin) != 0) { result = false; }
		else { setvbuf(stdin, NULL, _IONBF, 0); }

		// Redirect STDOUT to NUL
		if(freopen_s(&fp, "NUL:", "w", stdout) != 0) { result = false; }
		else { setvbuf(stdout, NULL, _IONBF, 0); }

		// Redirect STDERR to NUL
		if(freopen_s(&fp, "NUL:", "w", stderr) != 0) { result = false; }
		else { setvbuf(stderr, NULL, _IONBF, 0); }

		// Detach from console
		if(!FreeConsole()) { result = false; }

		return result;
	}

	void WindowsConsole::AdjustConsoleBuffer() {
		// Set the screen buffer to be big enough to scroll some text
		CONSOLE_SCREEN_BUFFER_INFO conInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
		if(conInfo.dwSize.Y < m_MinLength) { conInfo.dwSize.Y = m_MinLength; }
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
	}

	bool WindowsConsole::AttachParentConsole() {
		bool result = false;

		// Release any current console and redirect IO to NUL
		if(!ReleaseConsole()) {
			throw std::runtime_error("Failed to Release Console");
		}

		// Attempt to attach to parent process's console
		if(AttachConsole(ATTACH_PARENT_PROCESS)) {
			AdjustConsoleBuffer();
			result = RedirectConsoleIO();
		}

		return result;
	}

	bool WindowsConsole::RedirectConsoleIO() {
		bool result = true;
		FILE* fp;

		// Redirect STDIN if the console has an input handle
		if(GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE) {
			if(freopen_s(&fp, "CONIN$", "r", stdin) != 0) {
				result = false;
			}
			else {
				setvbuf(stdin, NULL, _IONBF, 0);
			}
		}

		// Redirect STDOUT if the console has an output handle
		if(GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE) {
			if(freopen_s(&fp, "CONOUT$", "w", stdout) != 0) {
				result = false;
			}
			else {
				setvbuf(stdout, NULL, _IONBF, 0);
			}
		}

		// Redirect STDERR if the console has an error handle
		if(GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE) {
			if(freopen_s(&fp, "CONOUT$", "w", stderr) != 0) {
				result = false;
			}
			else {
				setvbuf(stderr, NULL, _IONBF, 0);
			}
		}

		// Make C++ standard streams point to console as well.
		std::ios::sync_with_stdio(true);

		// Clear the error state for each of the C++ standard streams.
		std::wcout.clear();
		std::cout.clear();
		std::wcerr.clear();
		std::cerr.clear();
		std::wcin.clear();
		std::cin.clear();

		return result;
	}

}