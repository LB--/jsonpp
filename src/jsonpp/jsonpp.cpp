#include "jsonpp.hpp"
#include <json.h>
#include <stdexcept>

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
	Environment::Environment(std::string const &json)
	: Environment()
	{
		char error[256];
		json_settings s;
		json_value *jpp = nullptr;
		if(!(jpp = json_parse_ex(&s, json.c_str(), json.size(), error)))
		{
			throw std::runtime_error(error);
		}
		//...
	}
	Environment::~Environment() = default;
}
