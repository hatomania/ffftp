//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_DIALOG_Dialog
template <class PARAM>
static inline auto Dialog(HINSTANCE instance, int resourceId, HWND parent, PARAM&& param) noexcept {
  using T = std::remove_reference_t<PARAM>;
  return static_cast<typename T::result_t>(dialogBox(resourceId, static_cast<void*>(&param)));
}

static inline auto Dialog(HINSTANCE instance, int resourceId, HWND parent) noexcept {
  struct Data {
    using result_t = int;
  };
  return Dialog(instance, resourceId, parent, Data{});
}
#endif  // LIBFFFTP_INCLUDE_DIALOG_Dialog
