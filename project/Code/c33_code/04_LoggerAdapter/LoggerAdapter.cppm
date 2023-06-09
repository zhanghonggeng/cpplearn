export module logger;

import <string>;
import <string_view>;

export class Logger
{
public:
	enum class LogLevel {
		Error,
		Info,
		Debug
	};

	Logger();
	virtual ~Logger() = default;  // Always a virtual destructor!

	void log(LogLevel level, const std::string& message);

private:
	// Converts a log level to a human readable string.
	std::string_view getLogLevelString(LogLevel level) const;
};



export class INewLoggerInterface
{
public:
	virtual ~INewLoggerInterface() = default;  // Always a virtual destructor!
	virtual void log(std::string_view message) = 0;
};



export class NewLoggerAdapter : public INewLoggerInterface
{
public:
	NewLoggerAdapter();
	void log(std::string_view message) override;

private:
	Logger m_logger;
};
