#include "jsonpp.hpp"
#include <json.h>
#include <stdexcept>
#include <vector>
#include <map>
#include <memory>
#include "util/ordered_set.hpp"

template<>
struct util::PImpl<jsonpp::Environment>::Impl
{
	struct Value : public std::enable_shared_from_this<Value>
	{
		virtual ~Value() = 0;
		bool operator==(Value const &);
	};
	struct BoolValue : public Value
	{
		BoolValue(bool);
	};
	using Value_t = std::shared_ptr<Value>;
	using Overloads_t = std::pair<std::string, util::ordered_set<std::string>>;
	using Params_t = std::map<std::string, Value_t>;
	using Funcs_t = std::map<Overloads_t, std::function<Value_t (Params_t &)>>;
	Funcs_t Funcs
	{
		{{"==", {"..."}}, [](Params_t &p) -> Value_t
			{
				bool r = false;
				for(auto it = p.begin(); it != p.end(); )
				{
					auto const &a = it->second;
					++it;
					auto const &b = it->second;
					r = (r && *a == *b);
				}
				return Value_t{new BoolValue{r}};
			}
		}
		//
	};
};
util::PImpl<jsonpp::Environment>::Impl::Value::~Value() = default;

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
