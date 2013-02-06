#include "uiprogramview.h"

#include <QPainter>
#include <QLine>
#include <QDebug>

UiProgramView::UiProgramView(MinoProgram *program, QWidget *parent) :
    QWidget(parent),
    _program(program)
{
    // Optimize widget's repaint
    setAttribute(Qt::WA_OpaquePaintEvent);

    connect(_program, SIGNAL(animated()), this, SLOT(update()));
}

// This function produce draw the widget content
//   It draw the render content (scaled to fit to widget size) and decorates it using some vertical and horizotal black lines
void UiProgramView::paintEvent(QPaintEvent *event)
{
    // event is not used
    (void)event;

    // Make your code cleaner: store variables from renderer as local const
    const QImage *rendering = _program->rendering();

    // Construct a painter to draw into this widget
    QPainter painter(this);

    painter.drawImage(rect(), *rendering, rendering->rect());

    qreal stepX = (qreal)width() / rendering->width();
    qreal stepY = (qreal)height() / rendering->height();

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    const int nbLines = (rendering->width()-1) + (rendering->height()-1);
    QLine lines[nbLines];
    int currentLine = 0;
    for (int x = 1; x < rendering->width(); x++)
    {
        int pos = x * stepX;
        lines[currentLine] = QLine(pos,0,pos,height());
        currentLine++;
    }
    for (int y = 1; y < rendering->height(); y++)
    {
        int pos = y * stepY;
        lines[currentLine] = QLine(0,pos,width(),pos);
        currentLine++;
    }
    painter.drawLines(lines,nbLines);
}

int UiProgramView::heightForWidth( int width ) const
{
    return (_program->heightForWidth(width));
}