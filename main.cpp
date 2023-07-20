#include <QApplication>
#include "dialog.h"
#include <QTimer>
#include "workerthread.h" // Include the custom WorkerThread header

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog d;
    d.show();

    // Create the WorkerThread instance and pass the Dialog object to it
    WorkerThread workerThread(&d);

    // Start the worker thread
    workerThread.start();

    // Start the main event loop of the GUI thread
    int exitCode = a.exec();

    // Properly exit the worker thread
    workerThread.quit();
    workerThread.wait();

    return exitCode;
}
