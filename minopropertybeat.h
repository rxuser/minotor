#ifndef MINOPROPERTYBEAT_H
#define MINOPROPERTYBEAT_H

#include "minoproperty.h"
#include "midicontrollablelist.h"

class MinoPropertyBeat : public MinoProperty
{
    Q_OBJECT
    Q_PROPERTY (QString loop_size READ loopSize WRITE setLoopSize STORED true)

public:
    explicit MinoPropertyBeat(QObject *parent = 0);

    void setPreferred(bool on = true) { _mcl->setPreferred(on); }
    
    void setLoopSize(const QString& loopSize) { _mcl->setCurrentItem(loopSize); }
    QString loopSize() const { return _mcl->currentItem()->name(); }
    qreal loopSizeInPpqn() const { return _mcl->currentItem()->real(); }

signals:
    void loopSizeChanged(const QString& loopSize);

private:
    MidiControllableList *_mcl;
};

#endif // MINOPROPERTYBEAT_H
