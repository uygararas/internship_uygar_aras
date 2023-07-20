// workerthread.h
#include <QThread>
#include "dialog.h"

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(Dialog* dialog, QObject *parent = nullptr);
    void run() override;

private:
    Dialog* dialog;
};
