#include "interfaceWindow.h"
#include "libstage/stage.hh"
#include <QtGui>

using namespace Stg;
/*
static struct option longopts[] = {
    { "gui",  optional_argument,   NULL,  'g' },
    { "clock",  optional_argument,   NULL,  'c' },
    { "help",  optional_argument,   NULL,  'h' },
    { "args",  required_argument,   NULL,  'a' },
    { NULL, 0, NULL, 0 }
};
*/
interfaceWindow::interfaceWindow()
{
    QWidget *widget = new QWidget;
    QLabel *label = new QLabel("Choise the world:");
    QPushButton *startWorldButton = createButton(tr("&Start world"), SLOT(startWorld()));
    QPushButton *editWorldButton = createButton(tr("&Edit..."), SLOT(editWorld()));

    setCentralWidget(widget);

    filesComboBox = new QComboBox();

    QGridLayout *layout = new QGridLayout;

    find();

    if(filesComboBox)
        layout->addWidget(label, 0, 0);
        layout->addWidget(filesComboBox, 0, 1);
        layout->addWidget(editWorldButton, 0, 2);
        layout->addWidget(startWorldButton, 3, 0, 1, 3);

    widget->setLayout(layout);


    QObject::connect(filesComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(loadDefaultWorld(QString)));

    setWindowTitle(tr("WorldBuilder"));
    setMinimumSize(160, 160);
    resize(480, 320);

    /*
        QComboBox *combo = new QComboBox();

        foreach(QByteArray format, QText)

        combo->addItem("simple");

        QObject::connect(combo, SIGNAL(currentIndexChanged(QString)),
                label, SLOT(setText(QString)));

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
//! [0]

//! [1]
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

#ifdef Q_OS_SYMBIAN
    infoLabel = new QLabel(tr("<i>Choose a menu option</i>"));
#else
    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
#endif
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    layout->addWidget(label);
    layout->addWidget(combo);
    widget->setLayout(layout);
//! [1]

//! [2]
    createActions();
    createMenus();

#ifndef Q_OS_SYMBIAN
    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);
#endif

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);
    */
}

void interfaceWindow::find()
{
    QString fileName = "*.world";
    QString path = QDir::currentPath()+"/world";

    currentDir = QDir(path);
    QStringList files;

    files = currentDir.entryList(QStringList(fileName), QDir::Files | QDir::NoSymLinks);

    fillWorldsCombobox(files);

}

void interfaceWindow::fillWorldsCombobox(const QStringList &files)
{
    filesComboBox->addItem("");

    for (int i = 0; i < files.size(); ++i) {
        filesComboBox->addItem(files[i]);
    }
}

QPushButton *interfaceWindow::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void interfaceWindow::startWorld()
{
    if( ! world->paused )
       world->Start();

    world->Run();
}

void interfaceWindow::editWorld()
{
QMainWindow *editWindow = new QMainWindow;
QWidget *q = new QWidget;

const std::map<std::string, Model*> modelsWithNames = world->GetAllModelsByName();
const std::set<Model*> models =  world->GetAllModels();

QComboBox *modls = new QComboBox();

std::set<Model*>::const_iterator it;
it = models.begin();
for(; it != models.end(); it++) {
    //Model *m = it->second;
    Model *m = *it;
    QString name(((std::string)(m->GetModelType())).c_str());
    //if(((std::string)m->GetModelType()) ==  "position"){

        //modls->addItem(name+"("+((std::string)m->GetModelType()).c_str()+")");
    modls->addItem("("+name+")");
    //}
}

   //(*it)->GetModelType()
QGridLayout *layout = new QGridLayout;
layout->addWidget(modls, 0, 0);

q->setLayout(layout);
editWindow->setCentralWidget(q);

/*
world->models_by_name;
world->models_by_wfentity;
world->models_with_fiducials_byx;
world->models_with_fiducials_byy;
*/
editWindow->show();
}

void interfaceWindow::loadDefaultWorld(const QString character)
{
   world = new WorldGui( 400, 300, character.toStdString().c_str() );
   world->Load( character.toStdString() );




//std::cout<<"entered to load\n";
 //printf( "\n[Load worldfile: done]" );
   //world->ShowClock( showclock );

 /*
    World::Run();
*/
    /*
      printf( "%s %s ", "", "" );

      int ch=0, optindex=0;
      bool usegui = true;
      bool showclock = false;

      while ((ch = getopt_long(argc, argv, "cgh?", longopts, &optindex)) != -1)
         {
            switch( ch )
              {
              case 0: // long option given
                 printf( "option %s given\n", longopts[optindex].name );
                 break;
              case 'a':
                 World::ctrlargs = std::string(optarg);
                 break;
              case 'c':
                 showclock = true;
                 printf( "[Clock enabled]" );
                 break;
              case 'g':
                 usegui = false;
                 printf( "[GUI disabled]" );
                 break;

              default:
                             printf("unhandled option %c\n", ch );
                 //exit(0);
              }
         }

      puts("");// end the first start-up line

      // arguments at index [optindex] and later are not options, so they
      // must be world file names

      optindex = optind; //points to first non-option
      while( optindex < argc )
         {
            if( optindex > 0 )
              {
                 const char* worldfilename = argv[optindex];
                 World* world = ( usegui ?
                                new WorldGui( 400, 300, worldfilename ) :
                                new World( worldfilename ) );
                             world->Load( worldfilename );
                             printf( "\n[Load worldfile: done]" );
                             //world->ShowClock( showclock );

                             if( ! world->paused )
                                world->Start();

              }
            optindex++;
         }

      World::Run();
      printf( "\n[Stage: done]" );
    */
}
/*
QStringList interfaceWindow::findFiles(const QStringList &files)
{
    QProgressDialog progressDialog(this);
    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Find Files"));


    QStringList foundFiles;

    for (int i = 0; i < files.size(); ++i) {
        progressDialog.setValue(i);
        progressDialog.setLabelText(tr("Searching file number %1 of %2...")
                                    .arg(i).arg(files.size()));
        qApp->processEvents();

        if (progressDialog.wasCanceled())
            break;


        QFile file(currentDir.absoluteFilePath(files[i]));

        if (file.open(QIODevice::ReadOnly)) {
            QString line;
            QTextStream in(&file);
            while (!in.atEnd()) {
                if (progressDialog.wasCanceled())
                    break;
                line = in.readLine();
                if (line.contains(text)) {
                    foundFiles << files[i];
                    break;
                }
            }
        }
    }
    return foundFiles;
}
*/


void interfaceWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
//! [3]

void interfaceWindow::newFile()
{
    infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void interfaceWindow::open()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void interfaceWindow::save()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void interfaceWindow::print()
{
    infoLabel->setText(tr("Invoked <b>File|Print</b>"));
}

void interfaceWindow::undo()
{
    infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void interfaceWindow::redo()
{
    infoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void interfaceWindow::cut()
{
    infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void interfaceWindow::copy()
{
    infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void interfaceWindow::paste()
{
    infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void interfaceWindow::bold()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void interfaceWindow::italic()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void interfaceWindow::leftAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void interfaceWindow::rightAlign()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void interfaceWindow::justify()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Justify</b>"));
}

void interfaceWindow::center()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));
}

void interfaceWindow::setLineSpacing()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}

void interfaceWindow::setParagraphSpacing()
{
    infoLabel->setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
}

void interfaceWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("The <b>Menu</b> example shows how to create "
               "menu-bar menus and context menus."));
}

void interfaceWindow::aboutQt()
{
    infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

//! [4]
void interfaceWindow::createActions()
{
//! [5]
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
//! [4]

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
//! [5]

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(QKeySequence::Bold);
    boldAct->setStatusTip(tr("Make the text bold"));
    connect(boldAct, SIGNAL(triggered()), this, SLOT(bold()));

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    italicAct->setStatusTip(tr("Make the text italic"));
    connect(italicAct, SIGNAL(triggered()), this, SLOT(italic()));

    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
                                       "paragraph"));
    connect(setLineSpacingAct, SIGNAL(triggered()), this, SLOT(setLineSpacing()));

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
    connect(setParagraphSpacingAct, SIGNAL(triggered()),
            this, SLOT(setParagraphSpacing()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    connect(leftAlignAct, SIGNAL(triggered()), this, SLOT(leftAlign()));

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    connect(rightAlignAct, SIGNAL(triggered()), this, SLOT(rightAlign()));

    justifyAct = new QAction(tr("&Justify"), this);
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    justifyAct->setStatusTip(tr("Justify the selected text"));
    connect(justifyAct, SIGNAL(triggered()), this, SLOT(justify()));

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    connect(centerAct, SIGNAL(triggered()), this, SLOT(center()));

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);

}
void interfaceWindow::createMenus()
{

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);

    fileMenu->addAction(openAct);

    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);

    fileMenu->addSeparator();

    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);
}

