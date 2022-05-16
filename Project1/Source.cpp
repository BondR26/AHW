#include<iostream>
#include<exception>
#include<string>

namespace estd
{

	class OutOfRange: public std::out_of_range
	{
	public:
		OutOfRange(std::string msg):out_of_range(msg)
		{}
	};

	template<typename T>
	class Array
	{
	public:
		explicit Array(uint32_t size = 0) :m_size(size)
		{
			m_arr = new T[size];
		}
		
		Array(uint32_t size, T value):Array(size)
		{
			for (int i=0; i<m_size; i++)
			{
				m_arr[i] = value;
			}
		}

		T* begin()
		{
			return &m_arr[0];
		}

		T* end()
		{
			return &(m_arr[m_size - 1])+1;
		}

		T& operator[](uint32_t index)
		{
			if (index<0 || index > m_size)
			{
				throw OutOfRange("Out of range");
			}

			return m_arr[index];
		}

		uint32_t size()
		{
			return m_size;
		}

		~Array()
		{
			delete[] m_arr;
		}

	private:

		T* m_arr;
		uint32_t m_size;
	};


	template<typename V>
	class Iterator
	{
	public:
		explicit Iterator(Array<V>* current = nullptr) :m_current(current->begin()), m_count(0), m_size(current->size())
		{
			
		}

		V* operator++()
		{
			if (m_count < m_size)
			{
				m_count++;
				return (m_current++);
			}
			else
				throw OutOfRange("You outta range");
		}

		V* operator--()
		{
			if (m_count > 0)
			{
				m_count--;
				return (m_current--);
			}
			else
				throw OutOfRange("You outta range");
		}

		V& operator*()
		{
			return *m_current;
		}

		bool operator==(V val)
		{
			return *m_current == val;
		}

		bool operator !=(V val)
		{
			return !(*this == val);
		}

		bool operator>(V val)
		{
			return *m_current > val;
		}

		bool operator<(V val)
		{
			return *m_current < val;
		}

		~Iterator()
		{

		}

	private:
		V* m_current;
		uint32_t m_count;
		uint32_t m_size;
	};
}



int main()
{
	estd::Array<int> arr(10);
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i] = i;
	}

	estd::Iterator<int> it(&arr);

	for (int i = 0; i < 10; i++)
	{
		std::cout << *it;
		++it;
	}

	return EXIT_SUCCESS;
}
