#ifdef LIBFFFTP_INCLUDE_DIALOG_DeletedDialog
template <class PARAM>
static inline int Dialog(int resourceId, PARAM&& param) noexcept {
  return LIBFFFTP_WINDOWS::dialogBox(resourceId, static_cast<void*>(&param));
}

static inline int Dialog(int resourceId) noexcept {
  struct Data {};
  return Dialog(resourceId, Data{});
}
#endif  // LIBFFFTP_INCLUDE_DIALOG_DeletedDialog
