#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <concepts>
#include <memory>
#include <cassert>
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

				delete[] s;
				s = other.s;
				other.s = nullptr;
			}
			return *this;
		}

		~String() {
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
		return os << str.s;
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

		Tarolo(const Tarolo& other) :size(other.size) {
			std::cout << "Tarolo copy constructor invoked\n\n";
			elem = new T[size];
			std::copy(other.elem, other.elem + size, elem);
		}

		Tarolo(Tarolo&& other) : size(other.size) {
			other.size = 0;
			elem = other.elem;
			other.elem = nullptr;
		}

		Tarolo& operator=(const Tarolo& other) noexcept {
			std::cout << "Copy assignment operator is used\n\n";
			if (this != &other) {
				size = other.size;

				delete[] elem;
				elem = new T[size];
				std::copy(other.elem, other.elem + size, elem);
			}
			return *this;
		}

		Tarolo& operator=(Tarolo&& other) noexcept {
			std::cout << "Move assignment operator is used\n\n";
			if (this != &other) {
				size = other.size;

				delete[] elem;
				elem = new T[size];
				std::copy(other.elem, other.elem + size, elem);
				other.size = 0;
				other.elem = nullptr;
			}
			return *this;
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

	class Buffer {
	public:
		explicit Buffer(int v) :size(v) {
			data = new char[size];
		}
		const char& operator[](int i) const {
			assert(i < size);
			return data[i];
		}
		char& operator[](int i) {
			return const_cast<char&>(static_cast<const Buffer&>(*this)[i]);
		}

	private:
		char* data;
		unsigned int size;
	};

	template<typename T>
	class CirularBuffer {
	public:
		CirularBuffer(int v) : capacity(v) {
			buffer = new T[capacity];
		}
		~CirularBuffer() {
			delete[] buffer;
		}
		void push(T item) {
			buffer[tail] = item;
			tail = (tail + 1) % capacity;
			if (check_for_overflow()) {
				head = (head + 1) % capacity;
			}
		}
		T pop() {
			T val = buffer[head];
			head = (head + 1) % capacity;
			return val;
		}
	private:
		inline int check_for_overflow() const noexcept {
			return (tail == head) ? 1 : 0;
		}
		int capacity;
		T* buffer;
		size_t head = 0, tail = 0;
	};

	template <typename T>	class LinkedList {
	public:
		struct Node {
			T data;
			Node* next = nullptr;
			Node(T t) : data(t) {}
		};

		LinkedList() = default;

		LinkedList(T t) {
			head = new Node(t);
		}

		void add(T t) {
			Node* newNode = new Node(t);

			if (head == nullptr) {  
				head = newNode;
				return;
			}

			Node* curr = head;            
			while (curr->next != nullptr)
				curr = curr->next;

			curr->next = newNode;       
		}

		~LinkedList() {                   
			Node* curr = head;
			while (curr != nullptr) {
				Node* next = curr->next;
				delete curr;
				curr = next;
			}
		}

	private:
		Node* head = nullptr;
	};

	
	template <typename T>
	class shared_pointer {
	public:

		~shared_pointer() {
			--reCount;
		}
	private:
		T* data;
		static int refCount;
	};
	class Logger 
	{
	public:
		void Log(const std::string message) const;
	private:
		class Impl;

		Logger();
		~Logger();
		
		std::unique_ptr<Impl>impl;
	};
	class Logger::Impl {
	public:
		Impl() 
		{

		}

	private:
	};
	Logger::Logger() :impl(std::make_unique<Impl>()) {

	}
}

void print_stuff(char* msg) {
	printf("\n%s\n", msg);
}


int main(int argc, char** argv) {
	saso::String a{"aaaab"};
	saso::String b("moga");
	saso::String c = "asdf";

	std::cout << std::boolalpha << a.contains('e') << '\n';
	std::cout << std::boolalpha << a.contains("aaab") << '\n';

	Tarolo<int> tarolo = { 1,2,3,4,5,6 };
	Tarolo tarolo2{ tarolo };
	if (tarolo.remove_element(3))
		std::cout << "element was removed sucessfully\n\n";

	const char* szo = "asdfggg";
	print_stuff(const_cast<char*>(szo));

	//assert
	Buffer basdf(10000000);
	//printf("%s", basdf[9999999999]);
	//ub
	const int i = 10;
	*(const_cast<int*>(&i)) = 120;  
	std::cout << i;
	return 0;
}

// 1 2 3 4 5
//   t
//	 h