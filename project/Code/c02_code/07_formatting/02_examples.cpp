import <iostream>;
import <string>;
import <string_view>;
import <format>;

using namespace std;

class KeyValue {
public:
	KeyValue(string_view key, int value) :m_key{ key }, m_value{ value } {}

	const string& getKey() const {return m_key;}
	int getValue() const { return m_value; }

private:
	string m_key;
	int m_value;
};

template<>
class formatter < KeyValue > {
public:
	// parse()方法负责解析范围[context.begin(),context.end()) 内的格式说明符
	constexpr auto parse(auto& context) {
		// 初始化迭代器
		auto iter{ context.begin()};
		const auto end{ context.end() };

		if (iter == end || *iter == '}') {
			m_outputType = OutputType::KeyAndValue;
			return iter;
		}

		switch (*iter) {
		case 'a': //{:a} 
			m_outputType = OutputType::KeyOnly;
			break;
		case 'b': //{:b}
			m_outputType = OutputType::ValueOnly;
			break;
		case 'c': //{:c}
			m_outputType = OutputType::KeyAndValue;
			break;
		default:
			throw format_error{ "Invalid KeyValue format specifier." };
		}

		++iter;
		if (iter != end && *iter != '}') {
			throw format_error{"Invalid KeyValue format specifier."};
		}
		return iter;
	}

	auto format(const KeyValue& kv, auto& context) {
		switch (m_outputType){
			using enum OutputType;

		case KeyOnly:
			return format_to(context.out(), "{}", kv.getKey());
		case ValueOnly:
			return format_to(context.out(), "{}", kv.getKey());
		default:
			return format_to(context.out(), "{}-{}", kv.getKey(),kv.getValue());
		}
	}
private:
	// 自定义格式说明符
	enum class OutputType {
		KeyOnly,
		ValueOnly,
		KeyAndValue
	};
	OutputType m_outputType{ OutputType::KeyAndValue };  //默认初始化为KeyAndValue
};

int main()
{
	KeyValue keyValue{ "Key1", 11 };
	cout << format("{}", keyValue) << endl;
	cout << format("{:a}", keyValue) << endl;
	cout << format("{:b}", keyValue) << endl;
	cout << format("{:c}", keyValue) << endl;

	try {
		cout << format("{:cd}", keyValue) << endl;
	}
	catch (const format_error& caught_exception) {
		cout << caught_exception.what() << endl;
	}
}


