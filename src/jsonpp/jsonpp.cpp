#include "jsonpp.hpp"
#include <json.h>

template<>
struct util::PImpl<jsonpp::Environment>::Impl
{
};

namespace jsonpp
{
	Environment::Environment()
	: AutoPImpl<Environment>(std::/*make_unique*/unique_ptr<Impl>(new Impl))
	{
	}
	Environment::~Environment() = default;
}
