#include "jsonpp.hpp"
#include <json.h>
#include <stdexcept>
#include <vector>
#include <map>
#include <memory>
#include <typeinfo>
#include "util/ordered_set.hpp"

template<>
struct util::PImpl<jsonpp::Environment>::Impl
{
	struct Value : public std::enable_shared_from_this<Value>
	{
		virtual ~Value() = 0;

		virtual bool operator==(Value const &) const = 0;
		virtual bool operator!=(Value const &) const = 0;
		virtual bool operator< (Value const &) const = 0;
		virtual bool operator<=(Value const &) const = 0;
		virtual bool operator> (Value const &) const = 0;
		virtual bool operator>=(Value const &) const = 0;
	};
	struct NullValue : public Value
	{
		NullValue() = default;
		virtual ~NullValue() = default;

		virtual bool operator==(Value const &b) const override { return false; }
		virtual bool operator!=(Value const &b) const override { return false; }
		virtual bool operator< (Value const &b) const override { return false; }
		virtual bool operator<=(Value const &b) const override { return false; }
		virtual bool operator> (Value const &b) const override { return false; }
		virtual bool operator>=(Value const &b) const override { return false; }
	};
	struct BoolValue : public Value
	{
		bool v;
		BoolValue(bool v)
		: v(v)
		{
		}
		virtual ~BoolValue() = default;

		virtual bool operator==(Value const &b) const override { return typeid(b) == typeid(*this) && v == dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator!=(Value const &b) const override { return typeid(b) == typeid(*this) && v != dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator< (Value const &b) const override { return false; }
		virtual bool operator<=(Value const &b) const override { return false; }
		virtual bool operator> (Value const &b) const override { return false; }
		virtual bool operator>=(Value const &b) const override { return false; }
	};
	struct IntValue : public Value
	{
		long long v;
		IntValue(long long v)
		: v(v)
		{
		}
		virtual ~IntValue() = default;

		virtual bool operator==(Value const &b) const override { return typeid(b) == typeid(*this) && v == dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator!=(Value const &b) const override { return typeid(b) == typeid(*this) && v != dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator< (Value const &b) const override { return typeid(b) == typeid(*this) && v <  dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator<=(Value const &b) const override { return typeid(b) == typeid(*this) && v <= dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator> (Value const &b) const override { return typeid(b) == typeid(*this) && v >  dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator>=(Value const &b) const override { return typeid(b) == typeid(*this) && v >= dynamic_cast<decltype(*this)>(b).v; }
	};
	struct FloatValue : public Value
	{
		long double v;
		FloatValue(long double v)
		: v(v)
		{
		}
		virtual ~FloatValue() = default;

		virtual bool operator==(Value const &b) const override { return false; }
		virtual bool operator!=(Value const &b) const override { return true; }
		virtual bool operator< (Value const &b) const override { return typeid(b) == typeid(*this) && v <  dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator<=(Value const &b) const override { return typeid(b) == typeid(*this) && v <= dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator> (Value const &b) const override { return typeid(b) == typeid(*this) && v >  dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator>=(Value const &b) const override { return typeid(b) == typeid(*this) && v >= dynamic_cast<decltype(*this)>(b).v; }
	};
	struct StringValue : public Value
	{
		std::string v;
		StringValue(std::string const &v)
		: v(v)
		{
		}
		virtual ~StringValue() = default;

		virtual bool operator==(Value const &b) const override { return typeid(b) == typeid(*this) && v == dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator!=(Value const &b) const override { return typeid(b) == typeid(*this) && v != dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator< (Value const &b) const override { return typeid(b) == typeid(*this) && v <  dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator<=(Value const &b) const override { return typeid(b) == typeid(*this) && v <= dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator> (Value const &b) const override { return typeid(b) == typeid(*this) && v >  dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator>=(Value const &b) const override { return typeid(b) == typeid(*this) && v >= dynamic_cast<decltype(*this)>(b).v; }
	};
	using Value_t = std::shared_ptr<Value>;
	struct ArrayValue : public Value
	{
		std::vector<Value_t> v;
		ArrayValue() = default;
		virtual ~ArrayValue() = default;

		virtual bool operator==(Value const &b) const override { return typeid(b) == typeid(*this) && v == dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator!=(Value const &b) const override { return typeid(b) == typeid(*this) && v != dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator< (Value const &b) const override { return false; }
		virtual bool operator<=(Value const &b) const override { return false; }
		virtual bool operator> (Value const &b) const override { return false; }
		virtual bool operator>=(Value const &b) const override { return false; }
	};
	struct ObjectValue : public Value
	{
		std::map<std::string, Value_t> v;
		ObjectValue() = default;
		virtual ~ObjectValue() = default;

		virtual bool operator==(Value const &b) const override { return typeid(b) == typeid(*this) && v == dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator!=(Value const &b) const override { return typeid(b) == typeid(*this) && v != dynamic_cast<decltype(*this)>(b).v; }
		virtual bool operator< (Value const &b) const override { return false; }
		virtual bool operator<=(Value const &b) const override { return false; }
		virtual bool operator> (Value const &b) const override { return false; }
		virtual bool operator>=(Value const &b) const override { return false; }
	};
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
		},
		{{"!=", {"*", "*"}}, [](Params_t &p) -> Value_t
			{
				auto it = p.begin();
				auto const &a = it->second;
				++it;
				auto const &b = it->second;
				return Value_t{new BoolValue{*a != *b}};
			}
		}
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
