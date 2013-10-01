#ifndef JavaScriptObjectNotationPlusPlus_HeaderPlusPlus
#define JavaScriptObjectNotationPlusPlus_HeaderPlusPlus

#include "util/PImpl.hpp"

namespace jsonpp
{
	struct Environment : private util::AutoPImpl<Environment>
	{
		~Environment();
	};
}

#endif
