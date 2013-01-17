#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include "libstage/stage.hh"

namespace Stg
{
    class Thread : public QThread
    {
        Q_OBJECT
    public:
        Thread();
        void stop();
    protected:
        void run();
    private:
        QMutex mutex;
    };
}
#endif // THREAD_H

