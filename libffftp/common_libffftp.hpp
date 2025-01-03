//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_COMMON
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QString>
#include <QTimeZone>
#include "ffftp_common.h"

extern void initSettings();
#endif  // LIBFFFTP_INCLUDE_COMMON


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_COMMON_DefaultTimeZone
    static inline int DefaultTimeZone{static_cast<int>(-(QTimeZone::systemTimeZone().offsetFromUtc(QDateTime()) / 60))};
#endif  // LIBFFFTP_INCLUDE_COMMON_DefaultTimeZone


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_COMMON_Sound_Play
class SoundPlayer {
public:
  enum class Type {
    Connected,
    Transferred,
    Error,
  };
  inline explicit SoundPlayer()
      : player_{std::make_unique<QMediaPlayer>()},
        audioo_{std::make_unique<QAudioOutput>()},
        urls_{
          {Type::Connected,   QUrl::fromLocalFile("C:/Users/takayuki/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/platform/accessibilitySignal/browser/media/success.mp3")},
          {Type::Transferred, QUrl::fromLocalFile("C:/Users/takayuki/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/platform/accessibilitySignal/browser/media/quickFixes.mp3")},
          {Type::Error,       QUrl::fromLocalFile("C:/Users/takayuki/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/platform/accessibilitySignal/browser/media/foldedAreas.mp3")}, } {
    player_->setAudioOutput(audioo_.get());
  };
  inline void play(const Type playtype) {
    player_->setSource(urls_.value(playtype));
  }
private:
  std::unique_ptr<QMediaPlayer> player_;
  std::unique_ptr<QAudioOutput> audioo_;
  const QMap<Type, QUrl> urls_;
};
void Play() noexcept {
  static SoundPlayer player{};
  QMap<QString, SoundPlayer::Type> sm{
    {"FFFTP_Connected",   SoundPlayer::Type::Connected},
    {"FFFTP_Transferred", SoundPlayer::Type::Transferred},
    {"FFFTP_Error",       SoundPlayer::Type::Error},
  };
  player.play(sm.value(QString(keyName)));
}
#endif  // LIBFFFTP_INCLUDE_COMMON_Sound_Play


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_COMMON_Message
template<int captionId = IDS_APP>
static inline auto Message(HWND owner, int textId, DWORD style) noexcept {
  return messageBox(textId, captionId);
}
#endif  // LIBFFFTP_INCLUDE_COMMON_Message


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_COMMON_InputDialog
static inline auto InputDialog(int dialogId, HWND parent, UINT titleId, std::wstring& text, size_t maxlength = 0, int* flag = nullptr, int helpTopicId = IDH_HELP_TOPIC_0000001) noexcept {
  struct Data {
    using result_t = int;
    UINT titleId;
    std::wstring& text;
    size_t maxlength;
    int* flag;
    int helpTopicId;
  };
  return Dialog(nullptr, dialogId, nullptr, Data{ titleId, text, maxlength, flag, helpTopicId });
}
#endif  // LIBFFFTP_INCLUDE_COMMON_InputDialog


//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_OTHER
#ifndef LIBFFFTP_USE_WIN32API

#define SOCKET_PROXY_ERROR (SOCKET_ERROR - 1)

namespace std {
  template<>
  struct default_delete<addrinfo> {
    void operator()(addrinfo* ai) const noexcept {
      freeaddrinfo(ai);
    }
  };
}

inline const std::tuple<std::string, uint16_t> sockaddr2AddressPort(const sockaddr_storage* addr) {
  std::tuple<std::string, uint16_t> ret{};
  if (addr->ss_family == AF_INET6) {
    auto sin6{reinterpret_cast<const sockaddr_in6*>(addr)};
    char tmp[INET6_ADDRSTRLEN];
    std::get<0>(ret) = inet_ntop(AF_INET6, reinterpret_cast<const void*>(&sin6->sin6_addr), tmp, sizeof tmp);
    std::get<1>(ret) = ntohs(sin6->sin6_port);
  } else {
    auto sin{reinterpret_cast<const sockaddr_in*>(addr)};
    char tmp[INET_ADDRSTRLEN];
    std::get<0>(ret) = inet_ntop(AF_INET, reinterpret_cast<const void*>(&sin->sin_addr), tmp, sizeof tmp);
    std::get<1>(ret) = ntohs(sin->sin_port);
  }
  return ret;
}

#endif  // LIBFFFTP_USE_WIN32API
#endif  // LIBFFFTP_OTHER
