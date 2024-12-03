#ifndef FFFTP_HOSTDATA_D848290B_D2A5_447A_8897_5A261BC047AC_H_
#define FFFTP_HOSTDATA_D848290B_D2A5_447A_8897_5A261BC047AC_H_

#ifndef __cplusplus
#include <wchar.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct hostdata_basic {
	/* Basic tab */
	const wchar_t* host_name;
	const wchar_t* host_addr;
	const wchar_t* user_name;
	const wchar_t* password;
	bool is_anonymous;
	const wchar_t* initdir_local;
	const wchar_t* initdir_remote;
	const wchar_t* initdir_remotenow;
	bool enabled_nowdir;
	bool use_lastdir;
};

struct hostdata_expansion {
	/* Expansion tab */
};

struct hostdata {
	hostdata_basic basic;
	hostdata_expansion expansion;
};

#ifdef __cplusplus
}
#endif

#endif /* FFFTP_HOSTDATA_D848290B_D2A5_447A_8897_5A261BC047AC_H_ */
