#ifndef JavaScriptObjectNotationPlusPlus_HeaderPlusPlus
#define JavaScriptObjectNotationPlusPlus_HeaderPlusPlus
#include <string>
#include "util/PImpl.hpp"

namespace jsonpp
{
	struct Environment final : private util::AutoPImpl<Environment>
	{
		Environment();
		Environment(std::string const &json);
		~Environment();

		Environment &merge(Environment const &other);

	private:
		using typename util::PImpl<Environment>::Impl;
	};
}

#endif
