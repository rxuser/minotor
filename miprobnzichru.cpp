#include "miprobnzichru.h"

#include "minatext.h"

MiproBnzIchRU::MiproBnzIchRU(MinoProgramBank *bank) : MinoProgram(bank)
{
    this->setLabel("BNZ - Ich R U");
    MinoAnimationGroup *atBadg = new MinoAnimationGroup(this);
    MinaText *atBad = new MinaText(atBadg);
    atBad->setColor(QColor::fromHslF(0.08, 1.0, 0.5));
    atBad->setLoopSize("1/4");
    atBad->setDuration("1/2");
    atBad->setGeneratorStyle("P:F T:R");
    atBad->setText("BAD");
    atBadg->addAnimation(atBad);
    this->addAnimationGroup(atBadg);

    MinoAnimationGroup *atUg = new MinoAnimationGroup(this);
    MinaText *atU = new MinaText(atUg);
    atU->setLoopSize("1/4");
    atU->setDuration("1");
    atU->setGeneratorStyle("P:F T:R");
    atU->setColor(QColor::fromHslF(0.02, 1.0, 0.5));
    atU->setText("U");
    atUg->addAnimation(atU);
    this->addAnimationGroup(atUg);

    MinoAnimationGroup *atXg = new MinoAnimationGroup(this);
    MinaText *atX = new MinaText(atXg);
    atX->setLoopSize("1/4");
    atX->setDuration("1");
    atX->setGeneratorStyle("P:F T:R");
    atX->setColor(QColor::fromHslF(0.2, 1.0, 0.5));
    atX->setText("X");
    atXg->addAnimation(atX);
    this->addAnimationGroup(atXg);

    MinoAnimationGroup *atRg = new MinoAnimationGroup(this);
    MinaText *atR = new MinaText(atRg);
    atR->setLoopSize("1/4");
    atR->setDuration("1");
    atR->setGeneratorStyle("P:F T:R");
    atR->setColor(QColor::fromHslF(0.14, 1.0, 0.5));
    atR->setText("R");
    atRg->addAnimation(atR);
    this->addAnimationGroup(atRg);
}
