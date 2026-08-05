#ifndef ARRAY_TPP
# define ARRAY_TPP

template <typename T>
Array<T>::Array(void) : _data(0), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int size) : _data(new T[size]()), _size(size)
{
}

template <typename T>
Array<T>::Array(const Array<T> &other) : _data(0), _size(0)
{
	*this = other;
}

template <typename T>
Array<T>::~Array(void)
{
	delete [] _data;
}

template <typename T>
Array<T>	&Array<T>::operator=(const Array<T> &other)
{
	T	*copy;

	if (this == &other)
		return (*this);
	copy = 0;
	if (other._size > 0)
	{
		copy = new T[other._size]();
		for (unsigned int i = 0; i < other._size; ++i)
			copy[i] = other._data[i];
	}
	delete [] _data;
	_data = copy;
	_size = other._size;
	return (*this);
}

template <typename T>
T	&Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw Array<T>::OutOfBoundsException();
	return (_data[index]);
}

template <typename T>
const T	&Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw Array<T>::OutOfBoundsException();
	return (_data[index]);
}

template <typename T>
unsigned int	Array<T>::size(void) const
{
	return (_size);
}

template <typename T>
const char	*Array<T>::OutOfBoundsException::what(void) const throw()
{
	return ("array index out of bounds");
}

#endif
