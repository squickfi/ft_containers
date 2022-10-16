#pragma once

namespace ft {

	/**********
	** equal **
	**********/

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {

		for ( ; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2)
				return false;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred) {

		for ( ; first1 != last1; ++first1, ++first2) {
			if (!pred(*first1, *first2))
				return false;
		}
		return true;
	}

	/****************************
	** lexicographical_compare **
	****************************/

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
            if (*first1 < *first2)
                return (true);
            if (*first2 < *first1)
                return (false);
        }
        return ((first1 == last1) && (first2 != last2));
    }
    template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
            if (comp(*first1, *first2))
                return (true);
            if (comp(*first2, *first1))
                return (false);
        }
        return ((first1 == last1) && (first2 != last2));
    }
}
