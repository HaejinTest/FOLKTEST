#pragma once
#include "pch.h"

// 결과
// 4코어 CPU, 하이퍼스레딩 x 
// 8스레드에서 100만 번씩 더함
// 디버그 모드에선 Interlocked가 한 20프로 정도 더 빠름
// 릴리즈 모드에선 반대로 SRWLock이 한 20프로 정도 더 빠름
namespace locktest
{
	long gSum;
	constexpr int ADD_COUNT_MAX = 1000000;
	SRWLOCK gLock;

	void StartInterlockedAdd(int numberOfThreads);
	void StartSRWLock(int numberOfThreads);
	unsigned int InterlockedAdder(void* arguments);
	unsigned int SRWLockAdder(void* arguments);

	void StartInterlockedAdd(int numberOfThreads)
	{
		HANDLE* threadHandle = new HANDLE[numberOfThreads];
		gSum = 0;

		for (int count = 0; count < numberOfThreads; count++)
		{
			threadHandle[count] = (HANDLE)(_beginthreadex(nullptr, 0, InterlockedAdder, nullptr, 0, nullptr));
		}

		auto start = __rdtsc();
		WaitForMultipleObjects(numberOfThreads, threadHandle, true, INFINITE);
		auto end = __rdtsc();

		std::cout << std::setw(20) <<"InterlockedIncrement" << std::setw(20) <<end - start << "Clocks" << " Sum : "<< gSum << std::endl;
		delete[] threadHandle;
	}

	void StartSRWLock(int numberOfThreads)
	{
		HANDLE* threadHandle = new HANDLE[numberOfThreads];
		gSum = 0;
		InitializeSRWLock(&gLock);

		for (int count = 0; count < numberOfThreads; count++)
		{
			threadHandle[count] = (HANDLE)(_beginthreadex(nullptr, 0, SRWLockAdder, nullptr, 0, nullptr));
		}

		auto start = __rdtsc();
		WaitForMultipleObjects(numberOfThreads, threadHandle, true, INFINITE);
		auto end = __rdtsc();

		std::cout << std::setw(20) <<"SRWLockIncrement" << std::setw(20) << end - start << "Clocks" << " Sum : " << gSum << std::endl;
		delete[] threadHandle;
	}

	unsigned int InterlockedAdder(void* arguments)
	{
		for (int count = 0; count < ADD_COUNT_MAX; count++)
		{
			InterlockedIncrement(&gSum);
		}

		return 0;
	}

	unsigned int SRWLockAdder(void * arguments)
	{
		for (int count = 0; count < ADD_COUNT_MAX; count++)
		{
			AcquireSRWLockExclusive(&gLock);

			gSum++;

			ReleaseSRWLockExclusive(&gLock);
		}

		return 0;
	}
}