#include "include/nativeobject.h"
#include <QDebug>

NativeObject::NativeObject(QObject *parent) : QObject(parent)
{
    m_text = tr("Hello CuteKeys!");
}

void NativeObject::setText(QString &text)
{
    qDebug() << "New text from qml: " << text;
    m_text = text;
}
