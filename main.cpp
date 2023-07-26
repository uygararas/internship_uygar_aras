#include <QApplication>
#include "dialog.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog d;

    // Create a new thread and move the Dialog instance to that thread
    QThread* workerThread = new QThread;
    d.moveToThread(workerThread);

    // Start the worker thread
    workerThread->start();

    // Show the dialog after moving it to the worker thread
    d.show();

    // Create a QTimer to repeatedly emit the changeStatusOfAllSignal
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&d]() {
        // Emit the signal to trigger the changeStatusOfAll method in the new thread
        emit d.changeStatusOfAllSignal();
    });

    // Set the interval for the QTimer (e.g., 1000 milliseconds = 1 second)
    int interval = 100;
    timer.start(interval);

    return a.exec();
}
