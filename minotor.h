#ifndef MINOTOR_H
#define MINOTOR_H

#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>

#include "ledmatrix.h"
#include "midi.h"
#include "midimapping.h"

#include "minomaster.h"
#include "mipromatrix.h"
#include "minoclocksource.h"

#include "minoanimationfactory.h"

class MinoAnimation;
typedef QList<MinoAnimation*> MinoAnimationList;

class Minotor : public QObject
{
    Q_OBJECT
public:
    explicit Minotor(QObject *parent = 0);
    ~Minotor();

    // Scene accessor
    QGraphicsScene *scene() { return &_scene; }

    // Channel accessors
    MinoMaster *master() { return _master; }
//    MinoCue *cue() { return _cue; }

    // LedMatrix
    LedMatrix *ledMatrix() { return _ledMatrix; }

    // MIDI
    // TODO Support more than one interface
    Midi *midi() { return _midiInterfaces.at(0); }

    // MIDI mapping
    MidiMapping *midiMapping() { return &_midiMapping; }

    // Clock source
    MinoClockSource *clockSource() { return _clockSource; }

    // Display rect
    const QRect displayRect() { return _ledMatrix->rect(); }

    // Singleton accessor
    static Minotor *minotor() { static Minotor minotor; return &minotor; }

    // Program
    void addProgram(MinoProgram *program);
    QList<MinoProgram*> programs() { return _programs; }

signals:
    void controlChanged(const int interface, const quint8 channel, const quint8 control, const quint8 value);
    void beatToggled(bool active);
public slots:
    // Clock handler
    void dispatchClock(const unsigned int uppqn, const unsigned int gppqn, const unsigned int ppqn, const unsigned int qn);

    // Midi messages handlers
    void handleMidiInterfaceControlChange(quint8 channel, quint8 control, quint8 value);
    void handleMidiInterfaceProgramChange(quint8 channel, quint8 program);

private:
    // Scene
    QGraphicsScene _scene;

    // Master
    MinoMaster *_master;

    // External connections
    LedMatrix *_ledMatrix;

    // Midi interfaces
    MidiInterfaceList _midiInterfaces;

    // Midi mapping
    MidiMapping _midiMapping;

    // Clock source (internal generator and Midi)
    MinoClockSource *_clockSource;

    // Programs
    QList<MinoProgram*> _programs;
};

#endif // MINOTOR_H
