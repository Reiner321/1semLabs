#pragma once

#include<iostream>

template <typename ItemType>
class Array
{
public:
	template < typename IT, typename AT>
	class TemplateIterator;
	using Iterator = TemplateIterator<ItemType, Array>;
	using ConstIterator = TemplateIterator <const ItemType, const Array>;
public:
	Array(const int size = 10, const ItemType% value = ItemType());
	Array(const Array% other);
	Array(Array %%other);
	~Array();

	Iterator begin();
	Iterator end();

	ConstIterator begin() const;
	ConstIterator end() const;

	int size() const;
	void print() const;
	void swap(Array% other);
	void resize(int size);

	Array& operator=(const Array& other);
	Array& operator=(Array&& other);
	const ItemType& operator[](const int index) const;
	ItemType& operator[](const int index);

	Array operator+(const Array& other) const;
	Array& operator +=(const Array& other);
private:
	ItemType* m_array = nullptr;
	int m_size = 0;
};


template <typename ItemType>
template <typename IT, typename AT>
class Array<ItemType>::TemplateIterator
{
public:
	TemplateIterator(AT* array = nullptr, const int pos = 0);

	IT& operator*();
	IT& operator[](const int offset);

	TemplateIterator& operator++();
	TemplateIterator& operator--();
	TemplateIterator operator++(int);
	TemplateIterator operator--(int);

	bool operator==(const TemplateIterator& other) const;
	bool operator!=(const TemplateIterator& other) const;

private:
	AT* m_array;
	int m_pos = -1;
};

template <typename ItemType>
Array<ItemType>::Array(const int size, const ItemType& value)
{
	if (size < 0) {
		std::cerr << "Array<T>::Array: size is negative, invert...\n";
		m_size = -size;
	}
	else {
		m_size = size;
	}

	m_array = new int[m_size];

	for (int i = 0; i < m_size; ++i) {
		m_array[i] = value;
	}
}

template <typename ItemType>
Array<ItemType>::Array(const Array& other)
	: m_size(other.m_size)
{
	m_array = new int[m_size];

	for (int i = 0; i < m_size; ++i) {
		m_array[i] = other.m_array[i];
	}
}

template <typename ItemType>
Array<ItemType>::Array(Array&& other)
{
	swap(other);
}

template <typename ItemType>
Array<ItemType>::~Array()
{
	delete[] m_array;
}

template <typename ItemType> typename
Array<ItemType>::Iterator Array<ItemType>::begin()
{
	return Iterator(this, 0);
}

template <typename ItemType> typename
Array<ItemType>::Iterator Array<ItemType>::end()
{
	return Iterator(this, m_size);
}

template <typename ItemType> typename
Array<ItemType>::ConstIterator Array<ItemType>::begin() const
{
	return ConstIterator(this, 0);
}

template <typename ItemType> typename
Array<ItemType>::ConstIterator Array<ItemType>::end() const
{
	return ConstIterator(this, m_size);
}

template <typename ItemType>
int Array<ItemType>::size() const
{
	return m_size;
}

template <typename ItemType>
void Array<ItemType>::print() const
{
	std::cout << *this;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array& other)
{
	if (this == &other) {
		return *this;
	}

	if (m_size != other.m_size) {
		m_size = other.m_size;
		delete[] m_array;
		m_array = new int[m_size];
	}

	for (int i = 0; i < m_size; ++i) {
		m_array[i] = other.m_array[i];
	}

	return *this;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(Array&& other)
{
	swap(other);
	return *this;
}

template <typename ItemType>
const ItemType& Array<ItemType>::operator[](const int index) const
{
	assert(index >= 0 && index < m_size);
	return m_array[index];
}

template <typename ItemType>
ItemType& Array<ItemType>::operator[](const int index)
{
	assert(index >= 0 && index < m_size);
	return m_array[index];
}

template <typename ItemType>
void Array<ItemType>::swap(Array& other)
{
	std::swap(m_array, other.m_array);
	std::swap(m_size, other.m_size);
}

template <typename ItemType>
void Array<ItemType>::resize(int size)
{
	if (size < 0) {
		std::cerr << "Array::resize: size is negative, invert...\n";
		size = -size;
	}

	Array res(size);

	int count = std::min(m_size, size);
	for (int i = 0; i < count; ++i) {
		res.m_array[i] = m_array[i];
	}

	res.swap(*this);
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const Array& other) const
{
	Array res(m_size + other.m_size);
	for (int i = 0, j = 0; i < res.m_size; i++) {
		if (i < m_size) {
			res[i] = m_array[i];
		}
		else {
			res[i] = other.m_array[j];
			j++;
		}
	}
	return res;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const Array& other)
{
	Array tmp = *this + other;
	swap(tmp);
	return *this;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>::TemplateIterator(AT* array, const int pos)
	: m_array(array)
	, m_pos(pos)
{}

template <typename ItemType>
template <typename IT, typename AT>
IT& Array<ItemType>::TemplateIterator<IT, AT>::operator*()
{
	return m_array->operator[](m_pos);
}

template <typename ItemType>
template <typename IT, typename AT>
IT& Array<ItemType>::TemplateIterator<IT, AT>::operator[](const int offset)
{
	return *(operator+(offset));
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>& Array<ItemType>::TemplateIterator<IT, AT>::operator++()
{
	++m_pos;
	return *this;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>& Array<ItemType>::TemplateIterator<IT, AT>::operator--()
{
	--m_pos;
	return *this;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator++(int)
{
	Array<ItemType>::TemplateIterator<IT, AT> old(*this);
	++m_pos;
	return old;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator--(int)
{
	Array<ItemType>::TemplateIterator<IT, AT> old(*this);
	--m_pos;
	return old;
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::operator==(const TemplateIterator& other) const
{
	assert(m_array == other.m_array);
	return (m_array == other.m_array && m_pos == other.m_pos);
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::operator!=(const TemplateIterator& other) const
{
	return !operator==(other);
}

template <typename ItemType>
std::ostream& operator<<(std::ostream& stream, const Array<ItemType>& arr)
{
	stream << '[';
	for (int i = 0; i < arr.size() - 1; ++i) {
		stream << arr[i] << ", ";
	}
	stream << arr[arr.size() - 1] << "]\n";
	return stream;
}

template <typename ItemType>
std::istream& operator>>(std::istream& stream, Array<ItemType>& arr)
{
	for (int i = 0; i < arr.size(); ++i) {
		stream >> arr[i];
	}
	return stream;
}