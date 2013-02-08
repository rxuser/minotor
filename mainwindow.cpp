#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>

#include <QtCore/QList>
#include <QtCore/QDebug>

#include <QToolBar>
#include <QToolButton>
#include <QLCDNumber>
#include <QSplitter>
#include <QDoubleSpinBox>

#include "uidial.h"
#include "uianimationdescription.h"
#include "uianimationpicker.h"
#include "uianimationproperty.h"
#include "uiprogrambank.h"

#include "minoanimation.h"
#include "minoproperty.h"
#include "minoprogram.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _minotor = Minotor::minotor();

    ui->gvGlobal->setScene(_minotor->scene());

    _actionMidiCapture = new QAction("Assign MIDI control", this);
    connect(_actionMidiCapture, SIGNAL(triggered()), this, SLOT(midiCaptureTrigged()));

    ui->dwDebug->hide();

    // Configuration dialog box
    _configDialog = new ConfigDialog(this);

    QVBoxLayout *lCentralWidget = new QVBoxLayout(ui->centralWidget);
    lCentralWidget->setSpacing(10);
    lCentralWidget->setMargin(0);
    lCentralWidget->setContentsMargins(10,5,5,5);

    //Toolbar
    QToolBar *_tToolBar = new QToolBar("Transport",this);
    this->addToolBar(Qt::TopToolBarArea,_tToolBar);

    QWidget *_wToolBar = new QWidget(_tToolBar);
    _tToolBar->addWidget(_wToolBar);
    QHBoxLayout *lToolBar = new QHBoxLayout(_wToolBar);

    QWidget *wToolContainer = new QWidget(this);
    lToolBar->addWidget(wToolContainer);
    QHBoxLayout *lToolContainer = new QHBoxLayout(wToolContainer);
    lToolContainer->setObjectName("scrollcontainer");
    lToolContainer->setSpacing(0);
    lToolContainer->setMargin(0);
    lToolContainer->setContentsMargins(1,1,1,1);

    QWidget *wBackground = new QWidget(_tToolBar);
    lToolContainer->addWidget(wBackground);
    wBackground->setObjectName("panel");
    QHBoxLayout *lBackground = new QHBoxLayout(wBackground);
    lBackground->setSpacing(10);
    lBackground->setMargin(0);
    lBackground->setContentsMargins(5,2,5,2);
    QButtonGroup *_bgTransport = new QButtonGroup(_tToolBar);
    //Transport
    QWidget *wTransportButtons = new QWidget(_tToolBar);
    lBackground->addWidget(wTransportButtons);
    QHBoxLayout *lTransportButtons = new QHBoxLayout(wTransportButtons);
    lTransportButtons->setSpacing(5);
    lTransportButtons->setMargin(0);
    lTransportButtons->setContentsMargins(0,0,0,0);
    QPushButton *pbStart = new QPushButton(_tToolBar);
    lTransportButtons->addWidget(pbStart);
    _bgTransport->addButton(pbStart);
    pbStart->setCheckable(true);
    pbStart->setIcon(QIcon(":/pictos/play.png"));
    pbStart->setIconSize(QSize(16,16));
    pbStart->setMinimumSize(28,28);
    pbStart->setMaximumSize(28,28);
    connect(pbStart,SIGNAL(clicked(bool)),_minotor->clockSource(),SLOT(uiStart()));
    QPushButton *pbStop = new QPushButton(_tToolBar);
    lTransportButtons->addWidget(pbStop);
    _bgTransport->addButton(pbStop);
    pbStop->setCheckable(true);
    pbStop->setIcon(QIcon(":/pictos/stop.png"));
    pbStop->setIconSize(QSize(16,16));
    pbStop->setMinimumSize(28,28);
    pbStop->setMaximumSize(28,28);

    connect(pbStop,SIGNAL(clicked(bool)),_minotor->clockSource(),SLOT(uiStop()));
    QPushButton *pbSync = new QPushButton(_tToolBar);
    lTransportButtons->addWidget(pbSync);
    pbSync->setIcon(QIcon(":/pictos/sync.png"));
    pbSync->setIconSize(QSize(16,16));
    pbSync->setMinimumSize(28,28);
    pbSync->setMaximumSize(28,28);
    connect(pbSync,SIGNAL(clicked(bool)),_minotor->clockSource(),SLOT(uiSync()));


    QWidget *wTempoButtons = new QWidget(_tToolBar);
    lBackground->addWidget(wTempoButtons);
    QHBoxLayout *lTempoButtons = new QHBoxLayout(wTempoButtons);
    lTempoButtons->setSpacing(5);
    lTempoButtons->setMargin(0);
    lTempoButtons->setContentsMargins(0,0,0,0);
    //BPM
    QDoubleSpinBox *_sbBPM = new QDoubleSpinBox(_tToolBar);
    _sbBPM->setMinimum(20);
    _sbBPM->setMaximum(300);
    _sbBPM->setSingleStep(0.1);
    _sbBPM->setDecimals(1);
    _sbBPM->setFocusPolicy(Qt::NoFocus);

    lTempoButtons->addWidget(_sbBPM);
    _sbBPM->setValue(_minotor->clockSource()->bpm());
    connect(_minotor->clockSource(), SIGNAL(bpmChanged(double)), _sbBPM, SLOT(setValue(double)));
    connect(_sbBPM,SIGNAL(valueChanged(double)),_minotor->clockSource(),SLOT(setBPM(double)));

    //Tap
    QPushButton *pbTap = new QPushButton(_tToolBar);
    lTempoButtons->addWidget(pbTap);
    pbTap->setIcon(QIcon(":/pictos/tap.png"));
    pbTap->setIconSize(QSize(20,20));
    pbTap->setMinimumSize(28,28);
    pbTap->setMaximumSize(28,28);
    connect(pbTap,SIGNAL(clicked(bool)),_minotor->clockSource(),SLOT(uiTapOn()));
    //_tToolBar->addSeparator();

    QWidget *wMidiButtons = new QWidget(_tToolBar);
    lBackground->addWidget(wMidiButtons);
    QHBoxLayout *lMidiButtons = new QHBoxLayout(wMidiButtons);
    lMidiButtons->setSpacing(5);
    lMidiButtons->setMargin(0);
    lMidiButtons->setContentsMargins(0,0,0,0);
    // MIDI toolbar
    QPushButton *pbMidiLearn = new QPushButton(_tToolBar);
    connect(pbMidiLearn,SIGNAL(toggled(bool)),this,SLOT(tbMidiLearnToggled(bool)));
    pbMidiLearn->setText("MIDI learn");
    pbMidiLearn->setCheckable(true);
    lMidiButtons->addWidget(pbMidiLearn);
    lBackground->addStretch();
    // Fullscreen
    QPushButton *pbFullscreen = new QPushButton(_tToolBar);
    lBackground->addWidget(pbFullscreen);
    pbFullscreen->setIcon(QIcon(":/pictos/fullscreen.png"));
    pbFullscreen->setIconSize(QSize(20,20));
    pbFullscreen->setMinimumSize(28,28);
    pbFullscreen->setMaximumSize(28,28);
    pbFullscreen->setCheckable(true);
    connect(pbFullscreen,SIGNAL(toggled(bool)),this,SLOT(tbFullScreenToggled(bool)));

    //UiMaster
    _uiMaster = new UiMaster(_minotor->master(), ui->centralWidget);
    lCentralWidget->addWidget(_uiMaster);

    // Programs bank
    UiProgramBank *uiProgramBank = new UiProgramBank(_minotor, ui->centralWidget);
    lCentralWidget->addWidget(uiProgramBank);
    // Default MIDI menu
    _menu.addAction(_actionMidiCapture);

    connect(_uiMaster, SIGNAL(midiLearnToggled(bool)), this, SLOT(tbMidiLearnToggled(bool)));

    QToolBar *_tAnimationToolBar = new QToolBar("Animations",this);
    this->addToolBar(Qt::BottomToolBarArea,_tAnimationToolBar);
    QWidget *_wAnimations = new QWidget(_tAnimationToolBar);
    _tAnimationToolBar->addWidget(_wAnimations);
    QHBoxLayout *lAnimations = new QHBoxLayout(_wAnimations);

    QWidget *wContainer = new QWidget(this);
    lAnimations->addWidget(wContainer);
    wContainer->setObjectName("scrollcontainer");
    QVBoxLayout *lContainer = new QVBoxLayout(wContainer);
    lContainer->setSpacing(0);
    lContainer->setMargin(0);
    lContainer->setContentsMargins(5,5,5,5);
    // Populate animation scrollarea
    QScrollArea *sa =  new QScrollArea();
    sa->setFrameShadow(QFrame::Plain);
    sa->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    sa->setFocusPolicy(Qt::NoFocus);
    sa->setWidgetResizable(true);
    UiAnimationPicker *ap = new UiAnimationPicker(sa);

    sa->setWidget(ap);
    lContainer->addWidget(sa);
}

MainWindow::~MainWindow()
{
    delete _actionMidiCapture;
    delete _configDialog;
    delete ui;
}

void MainWindow::on_action_Configuration_triggered()
{
    _configDialog->show();
}

void MainWindow::midiCaptureTrigged()
{
    qDebug() << "here:" << QObject::sender()->metaObject()->className();

    if (QString(QObject::sender()->metaObject()->className()) == QString("QAction"))
    {
        QAction *action = ((QAction*)QObject::sender());
        qDebug() << "there:" << action->parent()->metaObject()->className();
        if (QString(action->parent()->metaObject()->className()) == QString("UiDial"))
        {
            UiDial *dial = ((UiDial*)action->parent());
            qDebug() << "midiCapture trigged for:" << dial->property()->objectName();
            _minotor->midiMapping()->assignCapturedControlTo(dial->property());
        }
    }
}

void MainWindow::customContextMenuRequested(const QPoint &pos)
{
    (void)pos;
    _actionMidiCapture->setParent(qApp->widgetAt(QCursor::pos()));
    _menu.exec(QCursor::pos());
}

void MainWindow::on_sPpqn_valueChanged(int value)
{
    static unsigned int uppqn = 0;
    const unsigned int ppqn = value%24;
    const unsigned int qn = value/24;
    _minotor->dispatchClock(uppqn, value, ppqn, qn);
    uppqn++;
}

void MainWindow::tbMidiLearnToggled(bool checked)
{
    QList<UiMidiProperty*> midiProperties = findChildren<UiMidiProperty*>();
    foreach(UiMidiProperty *midiProperty, midiProperties)
    {
        midiProperty->setMidiLearnMode(checked);
        midiProperty->update();
    }
}

void MainWindow::tbFullScreenToggled(bool on)
{
    if(isFullScreen()) {
         this->setWindowState(Qt::WindowMaximized);
      } else {
         this->setWindowState(Qt::WindowFullScreen);
      }
}

void MainWindow::on_pbShot_clicked()
{
    static int id = 0;
    QString shotname = "master_";
    shotname.append(QString::number(id++));
    shotname.append(QString(".png"));

    qDebug() << "shotname:" << shotname;
    UiProgramView *masterMonitor = findChild<UiProgramView*>("masterMonitor");
    if(masterMonitor)
    {
        QPixmap p = QPixmap::grabWidget(masterMonitor);
        qDebug() << "saved:" << p.save(shotname);
    }
}

void MainWindow::on_pbScene_clicked()
{
    QList<QGraphicsItem*> items = Minotor::minotor()->scene()->items();
    foreach(QGraphicsItem *item, items)
    {
        qDebug() << item;
    }
}
