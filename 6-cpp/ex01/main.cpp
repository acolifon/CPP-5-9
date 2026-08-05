#include "Serializer.hpp"
#include <iostream>

int	main(void)
{
	Data	data;
	Data	*copy;
	uintptr_t	raw;

	data.id = 42;
	data.name = "marvin";
	data.value = 21.21;

	raw = Serializer::serialize(&data);
	copy = Serializer::deserialize(raw);

	std::cout << "original: " << &data << std::endl;
	std::cout << "raw: " << raw << std::endl;
	std::cout << "copy: " << copy << std::endl;
	std::cout << "same pointer: ";
	if (copy == &data)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
	std::cout << copy->id << " " << copy->name << " " << copy->value << std::endl;
	return (0);
}
