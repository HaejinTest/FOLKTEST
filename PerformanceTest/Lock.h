#pragma once
#include "pch.h"

// ���
// 4�ھ� CPU, �����۽����� x 
// 8�����忡�� 100�� ���� ����
// ����� ��忡�� Interlocked�� �� 20���� ���� �� ����
// ������ ��忡�� �ݴ�� SRWLock�� �� 20���� ���� �� ����
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