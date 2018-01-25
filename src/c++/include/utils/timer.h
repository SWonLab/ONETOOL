#pragma once
#ifndef __WISARD_TIMER_H__
#define __WISARD_TIMER_H__

#include <time.h>
#ifdef _WIN32
#	include <WinSock.h>
#endif
#include "global/common.h"

namespace ONETOOL {

class cTimer
{
	char		S_buf[256];
	timeval		X_tiStart, X_tiEnd;
	wsReal		D_tiElapsed;
public:
	cTimer(int B_start=0) { if (B_start) start(); }
	void		start();				/* Ÿ�̸Ӹ� �����Ѵ� */
	wsReal		get();					/* ���� �������κ��� ����� �ʸ� ��ȯ */
	const char*	getReadable();
	static const char*
				fmt(wsReal R_val);
};

} // End namespace ONETOOL

#endif

