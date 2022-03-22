#pragma once
#include <memory>

namespace ft {

	template < class T, class Allocator = std::allocator<T> >
	class vector {

		public:

			typedef T			value_type;
   			typedef Allocator	allocator_type;

			typedef std::size_t	size_type;
	};

}