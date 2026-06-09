#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

inline namespace saso {
	class String {
	public:

		String(const char* str) : len(strlen(str)) {
			std::cout << "Constructor used\n\n";
			s = new char[len + 1];
			memcpy(s, str, len + 1);
		}

		String(const String& other) : len(other.len) {
			std::cout << "Copy constructor used\n\n";
			s = new char[other.len + 1];
			memcpy(s, other.s, len + 1);
		}

		String(String&& other) noexcept : len(other.len), s(other.s) {
			std::cout << "Move constructor used\n\n";
			other.s = nullptr;
			other.len = 0;
		}

		String& operator=(const String& other) noexcept {
			std::cout << "Copy assignment operator is used\n\n";
			if (this != &other) {
				len = other.len;
				
				delete[] s;
				s = new char[len + 1];
				memcpy(s, other.s, len + 1);
			}
			return *this;
		}

		String& operator=(String&& other) noexcept {
			std::cout << "Move assignment operator is used\n\n";
			
			if (this != &other) {
				len = other.len;
				other.len = 0;

				delete s;
				s = other.s;
				other.s = nullptr;
			}
			return *this;
		}

		~String(){
			delete[] s;
		}

		bool contains(const char& c) const {
			for (size_t i = 0; i < len; ++i) {
				if (s[i] == c)
					return true;
					
			}
			return false;
		}

		bool contains(const std::string& c) const {
			int k = c.length();

			if (k > len)
				return false;
			if (c == "")
				return true;
			for (int i = 0; i <= len - k; ++i)
			{
				bool match = true;

				for (int j = 0; j < k; ++j)
				{
					if (s[i + j] != c[j])
					{
						match = false;
						break;
					}
				}

				if (match)
					return true;
			}

			return false;
		}

		friend std::istream& operator>>(std::istream& is, String& str);
		friend std::ostream& operator<<(std::ostream& os, const String& str);

	private:
		char* s;
		int len;
	};

	std::istream& operator>>(std::istream& is, String& str) {
		char buffer[512];
		is >> buffer;
		str.s = buffer;
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const String& str) {
		return std::cout << str.s;
	}

	template <typename T>
	class Tarolo {
	public:
		
		explicit Tarolo(int n) :size(n) {
			elem = new T[size];
		}
		
		Tarolo(std::initializer_list<T> e) :size(e.size()) {
			elem = new T[size];
			std::copy(e.begin(), e.end(), elem);
		}

		void add(const T& item)
		{
			T* newElem = new T[size + 1];

			for (std::size_t i = 0; i < size; ++i)
			{
				newElem[i] = elem[i];
			}

			newElem[size] = item;

			delete[] elem;

			elem = newElem;
			++size;
		}
		bool remove_element(const T& item) {
			T* newElem = new T[size - 1];
			bool found = false;
			for (size_t i = 0, j = 0; i < size && j < size - 1; ++i)
			{
				if (elem[i] == item)
				{
					found = true;
					continue;
				}

				newElem[i] = elem[i];
				++j;
			}
			return found;
		}
		void remove_at(unsigned item) {
			if (item >= size)
				return;

			T* newElem = new T[size - 1];
			for (size_t originalIdx = 0, newIdx = 0; originalIdx < size && newIdx < size - 1; ++originalIdx) {
				if (originalIdx == item)
					continue;

				newElem[newIdx] = elem[originalIdx];
				++newIdx;
			}
			delete[] elem;
			elem = newElem;
			--size;
		}

		~Tarolo() {
			delete[] elem;
		}
	private:
		T* elem;
		int size;
	};
}

int main(int argc, char** argv) {
	saso::String a{"aaaab"};
	saso::String b("moga");
	saso::String c = "asdf";

	std::cout << std::boolalpha << a.contains('e') << '\n';
	std::cout << std::boolalpha << a.contains("aaab") << '\n';
	std::cout << sizeof(saso::String);

	Tarolo<int> tarolo = { 1,2,3,4,5,6 };
	if (tarolo.remove_element(3))
		std::cout << "element was removed sucessfully";
	return 0;
}
