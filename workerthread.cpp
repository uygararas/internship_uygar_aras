// workerthread.cpp
#include "workerthread.h"

WorkerThread::WorkerThread(Dialog* dialog, QObject *parent)
    : QThread(parent), dialog(dialog)
{
}

void WorkerThread::run()
{
    dialog->changeStatusOfAll();
}
