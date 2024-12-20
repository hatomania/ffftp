#ifdef LIBFFFTP_OTHER


#else

#include "libffftp_common.hpp"

namespace libffftp {

#ifndef LIBFFFTP_DECL
namespace {

void dialupEntryList(std::vector<std::wstring>& entries) {
	// ほぼSetRasEntryToComboBox関数のコピー
	entries.clear();
	if (DWORD size = 0, count = 0, result = RasEnumEntriesW(nullptr, nullptr, nullptr, &size, &count); result == ERROR_BUFFER_TOO_SMALL) {
		std::vector<RASENTRYNAMEW> entries_{ size / sizeof(RASENTRYNAMEW) };
		for (auto& e : entries_) e = { .dwSize = sizeof(RASENTRYNAMEW), .dwFlags = REN_User };
		size = sizeof(RASENTRYNAMEW) * size_as<DWORD>(entries_);
		if (result = RasEnumEntriesW(nullptr, nullptr, data(entries_), &size, &count); result == ERROR_SUCCESS) {
			for (DWORD i = 0; i < count; i++)
				entries.push_back(entries_[i].szEntryName);
		}
	}
}

}  // namespace
#endif

LIBFFFTP_FUNCTION(const std::vector<std::wstring>& dialupEntries())
#ifndef LIBFFFTP_DECL
{
  static std::vector<std::wstring> entries;
  dialupEntryList(entries);
  return entries;
}
#endif

}  // namespace libffftp

#endif
