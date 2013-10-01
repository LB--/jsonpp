#include "jsonpp.hpp"
#include <json.h>

template<>
struct util::PImpl<jsonpp::Environment>::Impl
{
};

namespace jsonpp
{
	Environment::~Environment() = default;
}
