#ifndef AutomagicPrivateImplementation_Utility_HeaderPlusPlus
#define AutomagicPrivateImplementation_Utility_HeaderPlusPlus
#include <type_traits>
#include <memory>

namespace util
{
	template<typename Derived>
	struct PImpl
	{
		PImpl()
		{
			static_assert(std::is_base_of<PImpl, Derived>::value,
			              "Template parameter must be deriving class");
		}
//	protected:
		struct Impl;
	};
	template<typename Derived>
	struct AutoPImpl
	: protected PImpl<Derived>
	, protected std::unique_ptr<typename PImpl<Derived>::Impl>
	{
	protected:
		using typename PImpl<Derived>::Impl;
	public:
		AutoPImpl(std::unique_ptr<Impl> &&p)
		: std::unique_ptr<Impl>(std::move(p))
		{
			static_assert(std::is_base_of<AutoPImpl, Derived>::value,
			              "Template parameter must be deriving class");
		}
	};
}

#endif
