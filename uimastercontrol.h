#ifndef UIMASTERCONTROL_H
#define UIMASTERCONTROL_H

#include <QWidget>

#include <QDragEnterEvent>
#include <QDropEvent>

#include "minomaster.h"

class UiMasterControl : public QWidget
{
    Q_OBJECT
public:
    explicit UiMasterControl(MinoMaster *master, QWidget *parent);
    ~UiMasterControl();

protected:
    QWidget *_wContent;

    void addAnimationGroup(MinoAnimationGroup *group);
signals:
    
public slots:
    void updateProgram();
private slots:
    void animationMoved(int srcProgramId, int srcGroupId , int srcAnimationId, int destProgramId, int destGroupId , int destAnimationId);

private:
    MinoMaster *_master;
};

#endif // UIMASTERCONTROL_H
