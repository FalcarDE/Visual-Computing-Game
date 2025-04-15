
#pragma once

#include <string>

namespace Core
{
namespace Logger
{
	void Log(const std::string& _rMessage);
	void Log(const char* _pFormat, ...);
} // namespace Logger
} // namespace Core

#define CORE_LOG(Format, Text)	Core::Logger::Log(Format, Text)
#define CORE_LOGM(Text)			Core::Logger::Log(Text)