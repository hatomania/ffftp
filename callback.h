#ifndef CALLBACK_3AF973B3_4656_4FCD_8CE4_256E332D5D0C_H_
#define CALLBACK_3AF973B3_4656_4FCD_8CE4_256E332D5D0C_H_

// libffftpのコールバック関数定義のためのヘルパー定義
#define LIBFFFTP_DECLARE_CALLBACK(ret, fname, args) extern void set##fname##Callback(ret (*func)##args##);
#define LIBFFFTP_IMPLEMENT_CALLBACK(ret, fname, args, src) static ret fname##args##src \
	typedef ret (*fname##Func) args;\
	static fname##Func fname##_func = fname;\
	namespace libffftp {\
	void set##fname##Callback(ret (*func)##args##) {\
		fname##_func = func;\
	}\
	}
#define LIBFFFTP_CALLBACK_SETTER(fname) libffftp::set##fname##Callback(func);

namespace libffftp {
// main.cpp
LIBFFFTP_DECLARE_CALLBACK(bool, AskMasterPassword, (const wchar_t** passwd))
LIBFFFTP_DECLARE_CALLBACK(bool, AskMasterPassword2nd, (const wchar_t** passwd))
LIBFFFTP_DECLARE_CALLBACK(bool, AskRetryMasterPassword, ())
}

#endif // CALLBACK_3AF973B3_4656_4FCD_8CE4_256E332D5D0C_H_
