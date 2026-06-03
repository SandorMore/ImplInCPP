#include <iostream>
#include <vector>

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

		//friend std::istream& operator>>(std::istream& is, const String& str);
		friend std::ostream& operator<<(std::ostream& os, const String& str);

	private:
		char* s;
		int len;
	};

	//std::istream& operator>>(std::istream& is, const String& str) {
	//	//return std::cin >> str.s;
	//}

	std::ostream& operator<<(std::ostream& os, const String& str) {
		return std::cout << str.s;
	}
}

int main(int argc, char** argv) {
	saso::String a{"aaaab"};
	saso::String b("moga");
	saso::String c = "asdf";

	std::cout << std::boolalpha << a.contains('e') << '\n';
	std::cout << std::boolalpha << a.contains("aaab") << '\n';
	return 0;
}