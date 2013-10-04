#ifndef OrderedSetWithSTLInterface_HeaderPlusPlus
#define OrderedSetWithSTLInterface_HeaderPlusPlus
#include <vector>
#include <set>

namespace util
{
	template<typename T, typename... R>
	struct ordered_set : private std::vector<T, R...>
	{
	private:
		using base = std::vector<T, R...>;
		using set = std::set<T, R...>;
	public:
		using typename base::value_type;
		using typename base::allocator_type;
		using typename base::size_type;
		using typename base::difference_type;
		using typename base::reference;
		using typename base::const_reference;
		using typename base::pointer;
		using typename base::const_pointer;
		using typename base::iterator;
		using typename base::const_iterator;
		using typename base::reverse_iterator;
		using typename base::const_reverse_iterator;

		using base::get_allocator;
		using base::at;
		using base::operator[];
		using base::front;
		using base::back;
		using base::data;
		using base::begin;
		using base::cbegin;
		using base::end;
		using base::cend;
		using base::rbegin;
		using base::crbegin;
		using base::rend;
		using base::crend;
		using base::empty;
		using base::size;

		explicit ordered_set(typename base::allocator_type const &alloc = typename base::allocator_type())
		: base(alloc)
		{
		}
		template<typename Iter>
		ordered_set(Iter first, Iter last, typename base::allocator_type const &alloc = typename base::allocator_type())
		: base(alloc)
		{
			for(set s; first != last; ++first)
			{
				if(s.insert(*first).second)
				{
					base::push_back(*first);
				}
			}
		}
		ordered_set(std::initializer_list<T> init, typename base::allocator_type const &alloc = typename base::allocator_type())
		: ordered_set(init.begin(), init.end(), alloc)
		{
		}

		friend bool operator==(ordered_set const &a, ordered_set const &b){ return static_cast<base>(a) == static_cast<base>(b); }
		friend bool operator!=(ordered_set const &a, ordered_set const &b){ return static_cast<base>(a) != static_cast<base>(b); }
		friend bool operator< (ordered_set const &a, ordered_set const &b){ return static_cast<base>(a) <  static_cast<base>(b); }
		friend bool operator<=(ordered_set const &a, ordered_set const &b){ return static_cast<base>(a) <= static_cast<base>(b); }
		friend bool operator> (ordered_set const &a, ordered_set const &b){ return static_cast<base>(a) >  static_cast<base>(b); }
		friend bool operator>=(ordered_set const &a, ordered_set const &b){ return static_cast<base>(a) >= static_cast<base>(b); }
	};
}

#endif
