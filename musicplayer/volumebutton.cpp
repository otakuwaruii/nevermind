#include "volumebutton.h"

#include <QtWidgets>
#include <QtWinExtras>

VolumeButton::VolumeButton(QWidget *parent) :
    QToolButton(parent)//构造函数
{
    setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    setPopupMode(QToolButton::InstantPopup);

    QWidget *popup = new QWidget(this);

    slider = new QSlider(Qt::Horizontal, popup);
    slider->setRange(0, 100);
    connect(slider, &QAbstractSlider::valueChanged, this, &VolumeButton::volumeChanged);

    label = new QLabel(popup);
    label->setAlignment(Qt::AlignCenter);
    label->setNum(100);
    label->setMinimumWidth(label->sizeHint().width());

    connect(slider, &QAbstractSlider::valueChanged, label, QOverload<int>::of(&QLabel::setNum));

    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setMargin(2);
    popupLayout->addWidget(slider);
    popupLayout->addWidget(label);

    auto *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);


}

void VolumeButton::increaseVolume()//增加音量
{
    slider->triggerAction(QSlider::SliderPageStepAdd);
}

void VolumeButton::descreaseVolume()//减小音量
{
    slider->triggerAction(QSlider::SliderPageStepSub);
}

int VolumeButton::volume() const//返回当前音量值
{
    return slider->value();
}

void VolumeButton::setVolume(int volume)//设置音量值
{
    slider->setValue(volume);
}




