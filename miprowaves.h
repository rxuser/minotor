#ifndef MIPROWAVES_H
#define MIPROWAVES_H
#include "minoprogram.h"

class MiproWaves : public MinoProgram
{
    Q_OBJECT
public:
    explicit MiproWaves(Minotor *minotor);
    QString name() { return QString("Waves"); }
signals:
    
public slots:
    
};

#endif // MIPROWAVES_H