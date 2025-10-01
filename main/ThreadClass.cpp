#include "ThreadClass.h"

ThreadClass::ThreadClass(LPTHREAD_START_ROUTINE func, LPVOID lpParam, const std::string& name) {
	this->name = name;

	hThread = CreateThread(NULL, 0, func, lpParam, 0, NULL);
	if (hThread == NULL) {
		throw std::runtime_error("������: �� ������� ������� ����� " + name);
	}
}

void ThreadClass::wait() {
	if (WaitForSingleObject(hThread, INFINITE) != WAIT_OBJECT_0) {
		throw std::runtime_error("������ ��� �������� ���������� ������ " + name);
	}
}

ThreadClass::~ThreadClass() {
	if (hThread) {
		CloseHandle(hThread);
		hThread = NULL;
	}
}