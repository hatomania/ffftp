//--------------------------------------------------------------------------------------------------
#ifdef LIBFFFTP_INCLUDE_HISTORY_AddHistoryToHistory
// ヒストリをヒストリリストの先頭に追加する
void AddHistoryToHistory(HISTORYDATA const& history) {
  histories.insert(begin(histories), history);
  if (FileHist < size_as<int>(histories)) { histories.resize(FileHist); }
  historyUpdated(histories);
}
#endif  // LIBFFFTP_INCLUDE_HISTORY_AddHistoryToHistory
