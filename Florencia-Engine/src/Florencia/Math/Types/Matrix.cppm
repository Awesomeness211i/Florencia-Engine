module;
#include <stdexcept>
export module Matrix;
import Vector;

export namespace FloMath {

	template<typename T, size_t Rows, size_t Columns = Rows>
	class Matrix {
	public:
		template<typename... Args>
		Matrix(Args... args) : data{args...} {}

		Vector<T, Rows> operator[](unsigned index) {
			return data[index];
		}

		Vector<T, Rows> at(unsigned index) {
			if (index < Columns)
				return data[index];
			throw std::runtime_error("Memory Access Violation");
		}

		Vector<T, Rows> operator[](unsigned index) const {
			return data[index];
		}

		Vector<T, Rows> at(unsigned index) const {
			if (index < Columns)
				return data[index];
			throw std::runtime_error("Memory Access Violation");
		}

	private:
		Vector<T, Rows> data[Columns];
	};

}