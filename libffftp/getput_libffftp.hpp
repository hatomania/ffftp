int LoadZoneID() {
	return FFFTP_SUCCESS;
}

void FreeZoneID() {
}

int IsZoneIDLoaded() noexcept {
	return YES;
}

bool MarkFileAsDownloadedFromInternet(fs::path const& path) {
  (void)path;
  return true;
}
