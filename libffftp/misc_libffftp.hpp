#ifdef LIBFFFTP_INCLUDE_MISC_SelectFile
#include "libffftp_common.hpp"

fs::path SelectFile(bool open, [[maybe_unused]] HWND hWnd, UINT titleId, const wchar_t* initialFileName, [[maybe_unused]] const wchar_t* extension, std::initializer_list<FileType> fileTypes) {
  fs::path ret{};

  // param1: 出力
  // param2: デフォルトのファイルパス
  // param3: ファイルフィルタ
  // param4: キャプション
  ffftp_procparam param{
    nullptr,
    const_cast<void*>(reinterpret_cast<const void*>(initialFileName)),
    reinterpret_cast<void*>(std::accumulate(begin(fileTypes), end(fileTypes), static_cast<uint64_t>(0), [](auto const& result, auto fileType) {
      static std::map<FileType, ffftp_filetype> table{
        { FileType::All, ffftp_filetype::ALL },
        { FileType::Executable, ffftp_filetype::EXECUTABLE },
        { FileType::Reg, ffftp_filetype::REG },
        { FileType::Ini, ffftp_filetype::INI },
        { FileType::Xml, ffftp_filetype::XML },
      };
      return result + table.at(fileType);
    })),
    reinterpret_cast<void*>(static_cast<uint64_t>(titleId)),
  };
  auto result = ffftp_proc(open ? ffftp_procmsg::GIVE_A_OPENFILEPATH : ffftp_procmsg::GIVE_A_SAVEFILEPATH, &param);
  if (result) {
    ret = reinterpret_cast<const wchar_t*>(param.param1);
  }
  return ret;
}
#endif  // LIBFFFTP_INCLUDE_MISC_SelectFile
