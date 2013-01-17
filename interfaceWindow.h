#ifndef INTERFACEWINDOW_H
#define INTERFACEWINDOW_H

#include "libstage/stage.hh"

#include <QMainWindow>
#include <QDir>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QComboBox;
class QPushButton;
QT_END_NAMESPACE

namespace Stg{

class interfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    interfaceWindow();


protected:
    void contextMenuEvent(QContextMenuEvent *event);
//! [0]

//! [1]
private slots:
    void loadDefaultWorld(const QString);
    void startWorld();
    void editWorld();
    void newFile();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();
    void aboutQt();
//! [1]

//! [2]
private:
    void createActions();
    void createMenus();

    void find();
    void fillWorldsCombobox(const QStringList &files);
    QStringList findFiles(const QStringList &files);

    QPushButton *createButton(const QString &text, const char *member);

    QDir currentDir;

    World* world;

    QComboBox *filesComboBox;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;

    QActionGroup *alignmentGroup;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QLabel *infoLabel;
};
}
#endif // INTERFACEWINDOW_H
