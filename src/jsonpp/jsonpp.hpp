#ifndef JavaScriptObjectNotationPlusPlus_HeaderPlusPlus
#define JavaScriptObjectNotationPlusPlus_HeaderPlusPlus
#include <memory>

namespace jsonpp
{
	namespace _ //private
	{
		template<typename D>
		struct PImpl { struct Impl; };
	}
	struct Environment
	: private                 _::PImpl<Environment>
	, private std::unique_ptr<_::PImpl<Environment>::Impl>
	{
		//
	};
}

#endif
