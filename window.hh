
#include <QWidget>
#include <QMainWindow>
#include "libstage/stage.hh"

#include <QGLWidget>
QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE
//! [0]
class GLWidget;

namespace Stg
{
class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(int x);
    Worldfile *wf;
    ~Window();

protected:
    void keyPressEvent(QKeyEvent *event);
/*
private slots:
    void newFile();
*/
private:
    QSlider *createSlider();

    GLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;

    QWidget* q;

    //void createActions();
    QMenu *fileMenu;
    QAction *newAction;
    void createMenus();
};
//! [0]
}
